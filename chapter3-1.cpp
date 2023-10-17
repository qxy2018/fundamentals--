#include <iostream>
#include <string>
#include <vector>
using namespace std;
    int flag=1;
// 函数用于提取左因子
void GETLeftFactor(string production) {
    vector<string> productions; // 用于存储提取后的产生式

    size_t arrowPos = production.find("->"); // 查找产生式中的 "->" 符号的位置
    
    string nonTerminal = production.substr(0, arrowPos); // 提取非终结符
    string rightSide = production.substr(arrowPos + 2); // 提取产生式右侧部分

    // 将右侧部分按 "|" 符号分割
    size_t startPos = 0;
    size_t pipePos = rightSide.find("|");
    while (pipePos != string::npos) {
        string productionPart = rightSide.substr(startPos, pipePos - startPos); // 提取一个产生式部分
        productions.push_back(productionPart);
        startPos = pipePos + 1;
        pipePos = rightSide.find("|", startPos);
    }

    string lastProductionPart = rightSide.substr(startPos); // 提取最后一个产生式部分
    productions.push_back(lastProductionPart);

    // 提取左因子
    string commonPrefix = "";
    for (int i = 0; i < productions.size(); ++i) {
        if (i == 0) {
            commonPrefix = productions[i];
        } else {
            size_t j = 0;
            while (j < commonPrefix.length() && j < productions[i].length() && commonPrefix[j] == productions[i][j]) {
                ++j;
            }
            commonPrefix = commonPrefix.substr(0, j); // 更新左因子
        }
    }

    // 输出左因子
    if(flag==1){
		 cout << nonTerminal << "->" << commonPrefix << "X" << endl;
		 cout << "X->"; 
		 flag++;
	}else{
		cout << nonTerminal << "->" << commonPrefix << "Y" << endl;
		cout << "Y->"; 
	}
   
    // 输出提取后的产生式
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
