#pragma once

#ifdef _WIN32
#define PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#endif

using PluginNameFn = const char* (*)();
using PluginArityFn = int (*)();
using PluginEvalFn = double (*)(const double* args, int argc);

PLUGIN_EXPORT const char* plugin_name();
PLUGIN_EXPORT int plugin_arity();
PLUGIN_EXPORT double plugin_eval(const double* args, int argc);