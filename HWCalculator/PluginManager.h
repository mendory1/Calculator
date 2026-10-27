#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

struct PluginFn {
    std::string name;
    int arity = 0;
    std::function<double(const std::vector<double>&)> eval;
    std::string path;
};

class PluginManager {
public:
    void loadAll(const std::string& dir);
    const PluginFn* find(const std::string& name) const;
    size_t size() const { return plugins_.size(); }
    ~PluginManager();
private:
    struct Loaded {
        void* handle = nullptr;
        std::unique_ptr<PluginFn> fn;
    };
    std::vector<Loaded> loaded_;
    std::vector<PluginFn*> plugins_;
};