#pragma once
#include "PluginManager.h"
#include "Operations.h"
#include <string>
#include <stdexcept>
#include <vector>

class EvalError : public std::runtime_error {
public:
    explicit EvalError(const std::string& m) : std::runtime_error(m) {}
};

class Calculator {
public:
    Calculator(const std::string& expr, const PluginManager& pm);
    double parse();
private:
    Operations lexer;
    const PluginManager& pm;
    int cur = 0;
    double curNum = 0;
    std::string curText;
    size_t curPos = 0;

    void next();
    void expect(int t, const char* what);
    double expr();
    double term();
    double power();
    double unary();
    double primary();
};