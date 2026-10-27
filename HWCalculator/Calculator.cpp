#include "Calculator.h"
#include "Operations.h"
#include <cmath>
#include <iostream>
#include <cctype>

Calculator::Calculator(const std::string& expr, const PluginManager& pm) : lexer(expr), pm(pm) {
    next();
}
void Calculator::next() {
    Token t = lexer.nextToken();
    curPos = t.pos;

    switch (t.type) {
    case TokType::Number: cur = 1; curNum = t.num; break;
    case TokType::Ident: cur = 2; curText = t.text; break;
    case TokType::Op: cur = 3; curText = t.text; break;
    case TokType::LParen: cur = 4; break;
    case TokType::RParen: cur = 5; break;
    default: cur = 0; break;
    }
}

void Calculator::expect(int t, const char* what) {
    if (cur != t) throw EvalError(std::string("Ожидалось ") + what);
    next();
}

double Calculator::parse() {
    double v = expr();
    if (cur != 0) throw EvalError("Лишние символы");
    return v;
}

double Calculator::expr() {
    double v = term();
    while (cur == 3 && (curText == "+" || curText == "-")) {
        std::string op = curText; next();
        double r = term();
        v = (op == "+") ? v + r : v - r;
    }
    return v;
}

double Calculator::term() {
    double v = power();
    while (cur == 3 && (curText == "*" || curText == "/")) {
        std::string op = curText; next();
        double r = power();
        if (op == "/") {
            if (r == 0) throw EvalError("Деление на ноль");
            v /= r;
        }
        else v *= r;
    }
    return v;
}

double Calculator::power() {
    double base = unary();
    if (cur == 3 && curText == "^") {
        next();
        double exp = power();

        const PluginFn* fn = pm.find("pow");
        if (!fn) {
            throw EvalError("Функция возведения в степень ('pow') не найдена");
        }

        if (fn->arity != 2) {
            throw EvalError("Плагин 'pow' должен принимать 2 аргумента");
        }

        try {
            std::vector<double> args = { base, exp };
            double r = fn->eval(args);
            if (std::isnan(r)) throw EvalError("Результат возведения в степень не определён ");
            return r;
        }
        catch (const EvalError&) {
            throw;
        }
        catch (const std::exception& e) {
            throw EvalError("Ошибка в плагине 'pow': " + std::string(e.what()));
        }
        catch (...) {
            throw EvalError("Неизвестная ошибка в плагине 'pow'");
        }
    }
    return base;
}

double Calculator::unary() {
    if (cur == 3 && curText == "-") { next(); return -unary(); }
    if (cur == 3 && curText == "+") { next(); return  unary(); }
    return primary();
}

double Calculator::primary() {
    if (cur == 1) { double v = curNum; next(); return v; }
    if (cur == 4) {
        next();
        double v = expr();
        expect(5, "')'");
        return v;
    }
    if (cur == 2) {
        std::string name = curText;
        next();
        if (cur != 4) throw EvalError("После имени функции '" + name + "' ожидалась '('");
        next();
        std::vector<double> args;
        if (cur != 5) {
            args.push_back(expr());
            while (cur == 3 && curText == ",") { next(); args.push_back(expr()); }
        }
        expect(5, "')'");

        const PluginFn* fn = pm.find(name);
        if (!fn) throw EvalError("Функция '" + name + "' не найдена");
        if ((int)args.size() != fn->arity)
            throw EvalError("Функция '" + name + "' ожидает " + std::to_string(fn->arity) + " аргум., получено " + std::to_string(args.size()));
        try {
            double r = fn->eval(args);
            if (std::isnan(r)) throw EvalError("Функция '" + name + "' вернула NaN");
            return r;
        }
        catch (const EvalError&) { throw; }
        catch (const std::exception& e) {
            throw EvalError("Функция '" + name + "' бросила исключение: " + e.what());
        }
        catch (...) {
            throw EvalError("Функция '" + name + "' бросила неизвестное исключение");
        }
    }
    throw EvalError("Неожиданный токен в позиции " + std::to_string(curPos));
}