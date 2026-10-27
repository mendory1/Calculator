#include "PluginManager.h"
#include "Calculator.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::setlocale(LC_ALL, "Russian");
    std::string expr;
    if (argc >= 2) {
        for (int i = 1; i < argc; ++i) { if (i > 1) expr += ' '; expr += argv[i]; }
    }
    else {
        std::getline(std::cin, expr);
    }

    PluginManager pm;
    pm.loadAll("./plugins");

    try {
        Calculator p(expr, pm);
        double r = p.parse();
        std::cout << r << "\n";
        return 0;
    }
    catch (const EvalError& e) {
        std::cerr << "Îøèáêà: " << e.what() << "\n";
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << "Îøèáêà: " << e.what() << "\n";
        return 3;
    }
}