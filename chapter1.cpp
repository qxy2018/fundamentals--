#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 定义词法单元的类型
enum TokenType {
    HASH = 0,//#
    FOR = 1,//for
    IF = 2,
    THEN = 3,
    ELSE = 4,
    WHILE = 5,
    DO = 6,
    LETTER = 10,//标识符 
    DIGIT = 11,//数字 
    PLUS = 13,//+
    MINUS = 14,//-
    TIMES = 15,//*
    DIVIDE = 16,//  '/'
    COLON = 17,// :
    ASSIGNMENT = 18, // 添加 :=
    LESS = 20,//<
    NOT_EQUAL = 21,//<>
    LESS_EQUAL = 22,//<=
    GREATER = 23,//>
    GREATER_EQUAL = 24,//>=
    EQUAL = 25,//=
    SEMI = 26,//;
    LPAREN = 27,//(
    RPAREN = 28,//)
    UNTIL = 29,
    INT = 30,
    INPUT = 31,
    OUTPUT = 32,
   
   
};

// 定义词法单元的结构
struct Token {
    TokenType type;
    string value;
};

// 定义哈希表来映射关键字和对应的Token类型
unordered_map<string, TokenType> keywordMap = {
    {"#", HASH},
    {"for", FOR},
    {"if", IF},
    {"then", THEN},
    {"else", ELSE},
    {"while", WHILE},
    {"do", DO},
    {"int", INT},
    {"input", INPUT},
    {"output", OUTPUT},
    {"<", LESS},
    {"<>", NOT_EQUAL},
    {"<=", LESS_EQUAL},
    {">", GREATER},
    {">=", GREATER_EQUAL},
    {"=", EQUAL},
    {";", SEMI},
    {"(", LPAREN},
    {")", RPAREN},
    {":=", ASSIGNMENT}, // 添加 :=
    {"*",TIMES},
    {"+",PLUS},
    {"-",MINUS},
    {"/",DIVIDE},
};

// 词法分析函数
vector<Token> tokenize(string input) {
    vector<Token> tokens;//用于记录每一组词法单元和词法记号 
    size_t pos = 0;

    while (pos < input.length()) {
        if (isdigit(input[pos])) {
            // 处理整数
            string integer;
            while (pos < input.length() && isdigit(input[pos])) {
                integer += input[pos];//将识别到的数字加入字符串，最后会识别到其他字符会结束添加，这样获得一个完整的字符串 
                pos++;
            }
            tokens.push_back({DIGIT, integer});//加入向量 
        } else if (isalpha(input[pos]) || input[pos] == '_') {
            // 检测到一个字母或一个下划线，可能标识符,也可能是关键字
            string identifier;
            while (pos < input.length() && (isalnum(input[pos]) || input[pos] == '_')) {
                identifier += input[pos];//isalnum用于判断一个字符是否为一个字母或数字 
                pos++;
            }
            if (keywordMap.find(identifier) != keywordMap.end()) {//遍历关键词表确定是否为关键字 
                TokenType type = keywordMap[identifier];
                tokens.push_back({type, identifier});
            } else {
                tokens.push_back({LETTER, identifier});
            }
        } else if (isspace(input[pos])) {
            // 跳过空白字符
            pos++;
        } else {
            // 处理其他字符
            string tokenValue;
            tokenValue += input[pos];
            pos++;

            while (pos < input.length() && !isspace(input[pos]) && !isalnum(input[pos]) && input[pos] != '_') {
                tokenValue += input[pos];
                pos++;
            }

            if (keywordMap.find(tokenValue) != keywordMap.end()) {
                TokenType type = keywordMap[tokenValue];
                tokens.push_back({type, tokenValue});
            } else {
                cout << "Error: Invalid token: " << tokenValue << endl;
                return tokens;
            }
        }
    }

    return tokens;
}
 
int main() {
    string input;
   
    getline(cin, input);

    vector<Token> tokens = tokenize(input);

    // 输出词法单元序列
    for (const Token& token : tokens) {
        cout << "(" << token.type << "," << token.value << ") ";
    }

    return 0;
}
