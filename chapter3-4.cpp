#include <iostream>
#include <string>
using namespace std;

string input;
size_t i = 0;  // ��ǰ��ȡ���ַ�λ��

// �����ķ�����
void E();
void EPrime();
void T();
void TPrime();
void F();

// �ķ������ʵ��
void E() {
    cout << "E->TE'" << endl;
    if (input.substr(i, 1) == "(" || input.substr(i, 2) == "id") {
        T();
        EPrime();
    }
    else {
        cout << "����: �������� " << input.substr(i, 1) << "������ ( �� id" << endl;
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
        cout << "����: �������� " << input.substr(i, 1) << "������ ( �� id" << endl;
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
            cout << "����: �����ս�� )��ȱ��ƥ�� (" << endl;
        }
    }
    else if (input.substr(i, 2) == "id") {
        cout << "F->id" << endl;
        cout << "match id" << endl;
        i += 2;
    }
    else {
        cout << "����: �������� " << input.substr(i, 1) << "������ ( �� id" << endl;
        i++;
    }
}

int main() {
    
    cin >> input;
  
    E();  // ��ʼ�﷨����
    if (i == input.size()) {
        cout << "����" << endl;
    } else {
        cout << "����: ���벻����" << endl;
    }
    return 0;
}
