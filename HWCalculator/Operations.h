#pragma once
#include <string>
#include <vector>

enum class TokType { Number, Ident, Op, LParen, RParen, End };

struct Token {
    TokType type;
    double  num = 0;
    std::string text;
    size_t pos = 0;
};

class Operations {
public:
    explicit Operations(const std::string& src);
    Token nextToken();
private:
    std::string src;
    size_t pos = 0;
    void skipWs();
};