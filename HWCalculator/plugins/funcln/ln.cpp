#include "plugin_api.h"
#include <cmath>
#include <stdexcept>
#include <string>

PLUGIN_EXPORT const char* plugin_name() { return "ln"; }
PLUGIN_EXPORT int plugin_arity() { return 1; }

PLUGIN_EXPORT double plugin_eval(const double* a, int n) {
    if (n != 1) throw std::invalid_argument("ln: ожидается 1 аргумент");

    if (a[0] <= 0.0) {
        throw std::domain_error("ln: аргумент должен быть больше нуля, получено " + std::to_string(a[0]));
    }
    return std::log(a[0]);
}