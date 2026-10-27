#include "plugin_api.h"
#include <cmath>
#include <stdexcept>

PLUGIN_EXPORT const char* plugin_name() { return "pow"; }
PLUGIN_EXPORT int plugin_arity() { return 2; }

PLUGIN_EXPORT double plugin_eval(const double* a, int n) {
    if (n != 2) throw std::invalid_argument("pow: ожидается 2 аргумента (основание и степень)");
    return std::pow(a[0], a[1]);
}