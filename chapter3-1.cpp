#include <iostream>
#include <string>
#include <vector>
using namespace std;
    int flag=1;
// ����������ȡ������
void GETLeftFactor(string production) {
    vector<string> productions; // ���ڴ洢��ȡ��Ĳ���ʽ

    size_t arrowPos = production.find("->"); // ���Ҳ���ʽ�е� "->" ���ŵ�λ��
    
    string nonTerminal = production.substr(0, arrowPos); // ��ȡ���ս��
    string rightSide = production.substr(arrowPos + 2); // ��ȡ����ʽ�Ҳಿ��

    // ���Ҳಿ�ְ� "|" ���ŷָ�
    size_t startPos = 0;
    size_t pipePos = rightSide.find("|");
    while (pipePos != string::npos) {
        string productionPart = rightSide.substr(startPos, pipePos - startPos); // ��ȡһ������ʽ����
        productions.push_back(productionPart);
        startPos = pipePos + 1;
        pipePos = rightSide.find("|", startPos);
    }

    string lastProductionPart = rightSide.substr(startPos); // ��ȡ���һ������ʽ����
    productions.push_back(lastProductionPart);

    // ��ȡ������
    string commonPrefix = "";
    for (int i = 0; i < productions.size(); ++i) {
        if (i == 0) {
            commonPrefix = productions[i];
        } else {
            size_t j = 0;
            while (j < commonPrefix.length() && j < productions[i].length() && commonPrefix[j] == productions[i][j]) {
                ++j;
            }
            commonPrefix = commonPrefix.substr(0, j); // ����������
        }
    }

    // ���������
    if(flag==1){
		 cout << nonTerminal << "->" << commonPrefix << "X" << endl;
		 cout << "X->"; 
		 flag++;
	}else{
		cout << nonTerminal << "->" << commonPrefix << "Y" << endl;
		cout << "Y->"; 
	}
   
    // �����ȡ��Ĳ���ʽ
    for (int i = 0; i < productions.size(); ++i) {
        string remainingPart = productions[i].substr(commonPrefix.length());
         cout<< remainingPart;
        if (i < productions.size() - 1) {
            cout << "|";
        }
    }
    cout << endl;
}

int main() {
    string production;
    while (cin >> production) {
    
        GETLeftFactor(production);
    }
  
    return 0;
}
