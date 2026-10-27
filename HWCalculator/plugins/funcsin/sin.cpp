#define _USE_MATH_DEFINES
#include "plugin_api.h"
#include <cmath>
#include <stdexcept>

PLUGIN_EXPORT const char* plugin_name() { return "sin"; }
PLUGIN_EXPORT int plugin_arity() { return 1; }
PLUGIN_EXPORT double plugin_eval(const double* a, int n) {
    if (n != 1) throw std::invalid_argument("sin: ожидается 1 аргумент");
    return std::sin(a[0] * M_PI / 180.0);
}