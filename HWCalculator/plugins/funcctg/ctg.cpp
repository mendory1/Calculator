#define _USE_MATH_DEFINES
#include "plugin_api.h"
#include <cmath>
#include <stdexcept>
#include <string>

PLUGIN_EXPORT const char* plugin_name() { return "ctg"; }
PLUGIN_EXPORT int plugin_arity() { return 1; }

PLUGIN_EXPORT double plugin_eval(const double* a, int n) {
    if (n != 1) throw std::invalid_argument("ctg: ожидается 1 аргумент");
    double angle = std::fmod(a[0], 180.0);

    if (std::abs(angle) < 1e-9) {
        throw std::domain_error("ctg: котангенс не определен для угла " + std::to_string(a[0]));
    }
    return 1.0 / std::tan(a[0] * M_PI / 180.0);
}