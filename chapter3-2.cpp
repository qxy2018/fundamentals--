#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 结构体表示产生式
struct Production {
    char left;
     vector<string>  right;
};

// 消除直接左递归
void eliminateDirectLeftRecursion( Production p, char nonTerminal) {
 
    vector<string> a;
    vector<string> b;
   
       for(size_t i=0;i<p.right.size();i++)
	    if(p.left==p.right[i][0]){
			a.push_back(p.right[i].substr(1));
		}else{
			b.push_back(p.right[i]);
		}
    
    cout<<nonTerminal<<"->";
    for(size_t i=0;i<b.size();i++){
    	if(i==b.size()-1){
			cout<<b[i]<<nonTerminal<<"'"<<endl;
		}else{
		cout<<b[i]<<nonTerminal<<"'|";
		}
	}
    cout<<nonTerminal<<"'->";
    for(size_t i=0;i<a.size();i++){
    	if(i==a.size()-1){
		 cout<<a[i]<<nonTerminal<<"'|#"<<endl;
		}else{
				cout<<a[i]<<nonTerminal<<"'|";
		}
	
	}
    
}
bool upper(vector<string> right)
{
	for(size_t i=0;i<right.size();i++){
		if(isupper(right[i][0])){
			return true;cout<<"1"<<endl;
		}
	}
	return false;
}

bool match(char left,vector<string> right)
{
	for(size_t i=0;i<right.size();i++){
		if(left==right[i][0]){
			return true;
		}
	}
	return false;
}

void Indirect_recursive_processing(vector<Production> productions)
{
	for (size_t i=0;i<productions.size();i++) {
		
		if(upper(productions[i].right)){
		      if(match(productions[i].left,productions[i].right)){
		      	  
				   	eliminateDirectLeftRecursion(productions[i],productions[i].left);
				   }else{
				   	   for(size_t k=0;k<productions.size();k++){
				   	   	
						  	for(size_t m=0;m<productions.size();m++){
							  	
							  	for(size_t n=0;n<productions[m].right.size();n++){
							  		
                   				  if(productions[k].left==productions[m].right[n][0]){
                   				  	if(k==m){
										 	break;
										 }
                   				  	string a=productions[m].right[n].substr(1);
                   				  	productions[m].right.erase(productions[m].right.begin()+n);
                   				  	 vector<string> insertions; // 临时向量用于保存插入的数据
										 
								     for (size_t i = 0; i < productions[k].right.size(); i++) {
								         string b = productions[k].right[i] + a;
								        
								         insertions.push_back(b); // 将插入数据添加到临时向量中
								     }
										productions[m].right.insert(productions[m].right.begin(),insertions.begin(), insertions.end());

									 }
    								  
								  }
							  }
						  }
						  string upper;
						  for(size_t i=0;i<productions.size();i++){
  						  if(productions[i].left=='S'){
								for(size_t j=0;j<productions[i].right.size();j++)
								{
								  						  	
								  for(size_t k=0;k<productions[i].right[j].size();k++){
								  	if(isupper(productions[i].right[j][k])){
									  	upper+=productions[i].right[j][k];
									  }
								  }					  	
								 }
							}
  												 
  						  }
							size_t num =productions.size();
			              
						  for(size_t i=0;i<num;i++){
						  	size_t flag;
						  	flag=upper.find(productions[i].left);
						  
						  	if(flag==string::npos){
						  
							  productions[i].left='!';
					          
							  }
						  }
                             for(size_t i=0;i<productions.size();i++){
                             	if(productions[i].left!='!'){
								 	eliminateDirectLeftRecursion(productions[i],productions[i].left);
								 }
							 	
							 }
     					return;
		
				   }		   
		}else{
			cout<<productions[i].left<<"->";
			for(size_t j=0;j<productions[i].right.size();j++){
				if(j==productions[i].right.size()-1){
						cout<<productions[i].right[j]<<endl;
				}else{
						cout<<productions[i].right[j]<<"|";
				}
			
			}
		}
	       
	    }
}
int main() {
    int numProductions;
    cin >> numProductions;
    vector<Production> productions;

    // 读入产生式
    for (int i = 0; i < numProductions; i++) {
        string productionStr;
        cin >> productionStr;

        char nonTerminal = productionStr[0];
        string right = productionStr.substr(3);
        
        Production p;
        p.left = nonTerminal;
        size_t startPos = 0;
        size_t pipePos = right.find("|");

        while (pipePos != string::npos) {
            string productionPart = right.substr(startPos, pipePos - startPos);
            p.right.push_back(productionPart);
            startPos = pipePos + 1;
            pipePos = right.find("|", startPos);
        }

        string lastProductionPart = right.substr(startPos);
        p.right.push_back(lastProductionPart);

        productions.push_back(p);
    }
   
    Indirect_recursive_processing(productions);
    return 0;
}





