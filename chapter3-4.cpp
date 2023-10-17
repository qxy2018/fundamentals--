#include <iostream>
#include <string>
using namespace std;

string input;
size_t i = 0;  // 当前读取的字符位置

// 定义文法规则
void E();
void EPrime();
void T();
void TPrime();
void F();

// 文法规则的实现
void E() {
    cout << "E->TE'" << endl;
    if (input.substr(i, 1) == "(" || input.substr(i, 2) == "id") {
        T();
        EPrime();
    }
    else {
        cout << "错误: 跳过输入 " << input.substr(i, 1) << "，期望 ( 或 id" << endl;
        i++;
    }
}

void EPrime() {
    if (input.substr(i, 1) == "+") {
        cout << "E'->+TE'" << endl;
        cout << "match +" << endl;
        i++;
        T();
        EPrime();
    }
    else {
        cout << "E'->#" << endl;
    }
}

void T() {
    cout << "T->FT'" << endl;
    if (input.substr(i, 1) == "(" || input.substr(i, 2) == "id") {
        F();
        TPrime();
    }
    else {
        cout << "错误: 跳过输入 " << input.substr(i, 1) << "，期望 ( 或 id" << endl;
        i++;
    }
}

void TPrime() {
    if (input.substr(i, 1) == "*") {
        i++;
        cout << "T'->*FT'" << endl;
        cout << "match *" << endl;
        F();
        TPrime();
    }
    else {
        cout << "T'->#" << endl;
    }
}

void F() {
    if (input.substr(i, 1) == "(") {
        cout << "F->(E)" << endl;
        i++;
        E();
        if (input.substr(i, 1) == ")") {
            cout << "match )" << endl;
            i++;
        }
        else {
            cout << "错误: 弹出终结符 )，缺少匹配 (" << endl;
        }
    }
    else if (input.substr(i, 2) == "id") {
        cout << "F->id" << endl;
        cout << "match id" << endl;
        i += 2;
    }
    else {
        cout << "错误: 跳过输入 " << input.substr(i, 1) << "，期望 ( 或 id" << endl;
        i++;
    }
}

int main() {
    
    cin >> input;
  
    E();  // 开始语法分析
    if (i == input.size()) {
        cout << "接受" << endl;
    } else {
        cout << "错误: 输入不完整" << endl;
    }
    return 0;
}
