#include "Operations.h"
#include <cctype>
#include <stdexcept>

Operations::Operations(const std::string& src) : src(src) {}

void Operations::skipWs() {
    while (pos < src.size() && std::isspace((unsigned char)src[pos])) ++pos;
}

Token Operations::nextToken() {
    skipWs();
    if (pos >= src.size()) return { TokType::End, 0, "", pos };

    char c = src[pos];
    size_t start = pos;

    if (std::isdigit((unsigned char)c) || c == '.') {
        size_t p = pos;
        while (p < src.size() && (std::isdigit((unsigned char)src[p]) || src[p] == '.')) ++p;
        try {
            double val = std::stod(src.substr(pos, p - pos));
            pos = p;
            return { TokType::Number, val, "", start };
        }
        catch (...) {
            throw std::runtime_error("Некорректное число в позиции " + std::to_string(pos));
        }
    }
    else if (std::isalpha((unsigned char)c) || c == '_') {
        size_t p = pos;
        while (p < src.size() && (std::isalnum((unsigned char)src[p]) || src[p] == '_')) ++p;
        std::string text = src.substr(pos, p - pos);
        pos = p;
        return { TokType::Ident, 0, text, start };
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        pos++;
        return { TokType::Op, 0, std::string(1, c), start };
    }
    else if (c == '(') { pos++; return { TokType::LParen, 0, "", start }; }
    else if (c == ')') { pos++; return { TokType::RParen, 0, "", start }; }

    throw std::runtime_error("Неизвестный символ '" + std::string(1, c) + "' в позиции " + std::to_string(pos));
}