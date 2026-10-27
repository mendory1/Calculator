#include "PluginManager.h"
#include "plugin_api.h"
#include <filesystem>
#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace fs = std::filesystem;

namespace {
#ifdef _WIN32
    constexpr const char* kExt = ".dll";
    void* openLib(const std::string& p) { return (void*)LoadLibraryA(p.c_str()); }
    void closeLib(void* h) { if (h) FreeLibrary((HMODULE)h); }
    void* sym(void* h, const char* n) { return (void*)GetProcAddress((HMODULE)h, n); }
#else
    constexpr const char* kExt = ".so";
    void* openLib(const std::string& p) { return dlopen(p.c_str(), RTLD_NOW | RTLD_LOCAL); }
    void closeLib(void* h) { if (h) dlclose(h); }
    void* sym(void* h, const char* n) { return dlsym(h, n); }
#endif
}

PluginManager::~PluginManager() {
    for (auto& l : loaded_) closeLib(l.handle);
}

void PluginManager::loadAll(const std::string& dir) {
    std::error_code ec;
    if (!fs::exists(dir, ec)) {
        std::cerr << "[plugins] Папка '" << dir << "' не найдена. Работают только базовые операции.\n";
        return;
    }
    for (auto& entry : fs::directory_iterator(dir, ec)) {
        if (!entry.is_regular_file()) continue;
        if (entry.path().extension() != kExt) continue;

        const std::string path = entry.path().string();
        void* h = openLib(path);
        if (!h) {
            std::cerr << "[plugins] Не удалось загрузить '" << path << "'";
#ifdef _WIN32
            std::cerr << " (код " << GetLastError() << ")";
#else
            std::cerr << " (" << dlerror() << ")";
#endif
            std::cerr << "\n";
            continue;
        }

        auto* nameFn = (PluginNameFn)sym(h, "plugin_name");
        auto* arityFn = (PluginArityFn)sym(h, "plugin_arity");
        auto* evalFn = (PluginEvalFn)sym(h, "plugin_eval");
        if (!nameFn || !arityFn || !evalFn) {
            std::cerr << "[plugins] '" << path << "' не является корректным плагином.\n";
            closeLib(h);
            continue;
        }

        const char* nm = nullptr;
        int ar = -1;
        try { nm = nameFn(); ar = arityFn(); }
        catch (const std::exception& e) {
            std::cerr << "[plugins] '" << path << "' бросил исключение при инициализации: " << e.what() << "\n";
            closeLib(h); continue;
        }
        if (!nm || !*nm || ar <= 0) {
            std::cerr << "[plugins] '" << path << "' вернул некорректные метаданные.\n";
            closeLib(h); continue;
        }

        auto fn = std::make_unique<PluginFn>();
        fn->name = nm;
        fn->arity = ar;
        fn->path = path;
        fn->eval = [evalFn](const std::vector<double>& a) { return evalFn(a.data(), (int)a.size()); };

        if (find(fn->name)) {
            std::cerr << "[plugins] Дубликат функции '" << fn->name << "' из '" << path << "' — пропущен.\n";
            closeLib(h); continue;
        }

        loaded_.push_back({ h, std::move(fn) });
        plugins_.push_back(loaded_.back().fn.get());
    }

    if (plugins_.empty())
        std::cerr << "[plugins] Не загружено ни одного плагина.\n";
}

const PluginFn* PluginManager::find(const std::string& name) const {
    for (auto* p : plugins_) if (p->name == name) return p;
    return nullptr;
}