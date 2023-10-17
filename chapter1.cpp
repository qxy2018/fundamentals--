#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// ����ʷ���Ԫ������
enum TokenType {
    HASH = 0,//#
    FOR = 1,//for
    IF = 2,
    THEN = 3,
    ELSE = 4,
    WHILE = 5,
    DO = 6,
    LETTER = 10,//��ʶ�� 
    DIGIT = 11,//���� 
    PLUS = 13,//+
    MINUS = 14,//-
    TIMES = 15,//*
    DIVIDE = 16,//  '/'
    COLON = 17,// :
    ASSIGNMENT = 18, // ��� :=
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

// ����ʷ���Ԫ�Ľṹ
struct Token {
    TokenType type;
    string value;
};

// �����ϣ����ӳ��ؼ��ֺͶ�Ӧ��Token����
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
    {":=", ASSIGNMENT}, // ��� :=
    {"*",TIMES},
    {"+",PLUS},
    {"-",MINUS},
    {"/",DIVIDE},
};

// �ʷ���������
vector<Token> tokenize(string input) {
    vector<Token> tokens;//���ڼ�¼ÿһ��ʷ���Ԫ�ʹʷ��Ǻ� 
    size_t pos = 0;

    while (pos < input.length()) {
        if (isdigit(input[pos])) {
            // ��������
            string integer;
            while (pos < input.length() && isdigit(input[pos])) {
                integer += input[pos];//��ʶ�𵽵����ּ����ַ���������ʶ�������ַ��������ӣ��������һ���������ַ��� 
                pos++;
            }
            tokens.push_back({DIGIT, integer});//�������� 
        } else if (isalpha(input[pos]) || input[pos] == '_') {
            // ��⵽һ����ĸ��һ���»��ߣ����ܱ�ʶ��,Ҳ�����ǹؼ���
            string identifier;
            while (pos < input.length() && (isalnum(input[pos]) || input[pos] == '_')) {
                identifier += input[pos];//isalnum�����ж�һ���ַ��Ƿ�Ϊһ����ĸ������ 
                pos++;
            }
            if (keywordMap.find(identifier) != keywordMap.end()) {//�����ؼ��ʱ�ȷ���Ƿ�Ϊ�ؼ��� 
                TokenType type = keywordMap[identifier];
                tokens.push_back({type, identifier});
            } else {
                tokens.push_back({LETTER, identifier});
            }
        } else if (isspace(input[pos])) {
            // �����հ��ַ�
            pos++;
        } else {
            // ���������ַ�
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

    // ����ʷ���Ԫ����
    for (const Token& token : tokens) {
        cout << "(" << token.type << "," << token.value << ") ";
    }

    return 0;
}
