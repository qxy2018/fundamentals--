#include<iostream>
#include<cstring>
#include<map>
#include<stack>
#include<queue>
#include<iomanip> 
#include<stdio.h>
#include<cmath>
using namespace std;
struct item;                   //表项，状态和终结符 
stack<string> sta;             //栈  
queue<string> input;           //用于存放输入串 
map<item,string> Action;       //map类型的Action表。。因为太长了用函数写太麻烦了 
map<item,string> :: iterator it;
 
 
queue<double> NUM; 
stack<double> T;
stack<double> F;
stack<double> E; 
map<item,string> Error;       //map类型的错误分析表 
map<item,string> :: iterator itError;
 
string Goto(string state,string nonter){         //Goto函数 
	if(state=="0"){
		if(nonter == "E")
			return "1";
		if(nonter == "T")
			return "2";
		if(nonter == "F")
			return "3";
	}
	else if(state == "4"){
		if(nonter == "E")
			return "10";
		if(nonter == "T")
			return "2";
		if(nonter == "F")
			return "3";
	}
	else if(state == "6"){
		if(nonter == "T")
			return "11";
		if(nonter == "F")
			return "3";
	}
	else if(state == "7"){
		if(nonter == "T")
			return "12";
		if(nonter == "F")
			return "3";
	}
	else if(state == "8"&& nonter == "F")
		return "13";
	else if(state == "9"&& nonter == "F")
		return "14";
	else 
	return "false";
}
 
struct item{                   //有state和nonterminal（非终结符） 
	string state;
	string nonter;
	item(string s,string n){
		this->state = s;
		this->nonter = n;
	}
	bool operator < (const struct item &i) const{       
		return (this->state<i.state||(this->state==i.state&&this->nonter<i.nonter));
	}
	bool operator == (const struct item &i) const{
		return (i.state==this->state&&i.nonter==this->nonter);
	}
};
 
/*重载一下运算符就不需要这个函数了啊！ 
string find(map<item,string> m,item i){
	map<item,string> :: iterator it;
	for(it = m.begin();it!=m.end();it++)
		if(it->first==i)
			return it->second;
	return "mo";
}*/ 
 
void handle(string in){        //把读入的串放到队列里 
	string cut;
	while(!in.empty()){
		if(in[0]>='0'&&in[0]<='9'){
			int i=1;
			while(in[i]>='0'&&in[0]<='9')
				i++;
			string Stringnum=in.substr(0,i);
			in = in.substr(i);
			int num=0;
			for(int j=0;j<Stringnum.size();j++){
				num+=(Stringnum[j]-48)*pow(10,Stringnum.size()-j-1);
			}
			NUM.push(num);
			cut = "id";
			input.push(cut); 
		}
		else if(in[0]==' ')    //空格，丢掉 
			in = in.substr(1); 
		else{                  //其他的，截一个字符 
			cut = in.substr(0,1);
			in = in.substr(1);
			input.push(cut);
		}
		cut.clear();	
	}
	input.push("$");	
}
 
void show(){
	int i,sizeOfQueue,sizeOfStack;
	string temp1,temp;
	int kongge = 0;
	stack<string> newStack;
	//输出栈中的元素
	kongge += sta.size();
	sizeOfStack = sta.size();
	for(i=0;i<sizeOfStack;i++){
		temp = sta.top();
		sta.pop();
		newStack.push(temp);	
	}
	for(i=0;i<sizeOfStack;i++){
		temp = newStack.top();
	//	cout <<temp << " ";
		kongge+=temp.size();
		newStack.pop();
		sta.push(temp);
	}
	for(int j=0;j<40-kongge;j++)
			//cout <<" ";
	//输出队列中的元素 
	kongge = 0;
	sizeOfQueue = input.size();
	for(i=0;i<sizeOfQueue;i++){
		temp1 = input.front();
		input.pop();
		kongge+=temp1.size();
	//	cout << temp1;  
		input.push(temp1);
	}
//	for(int x=0;x<25-kongge;x++)
//		cout << " ";
} 
  int flag=0;
void analyse_error(string state,string next){
	string error_type; 
	itError = Error.find(item(state,next));
	if(itError==Error.end()){
	//	cout << "未知符号，扔了扔了" << endl;
		input.pop();flag=1;
		return ;	
	}
	error_type = itError->second;
	if(error_type=="e1"){
		//cout << "缺少运算对象" << endl; 
		flag=1;
		cout<<"输入有误！请重新输入"<<endl;
		sta.push("id");
		sta.push("5");
	}
	else if(error_type=="e2"){
		cout << "不匹配的右边括号" << endl;
		input.pop();	flag=1;
	}
	else if(error_type=="e3"){
		cout << "缺少右括号" << endl;
		sta.push(")");
		sta.push("11");	flag=1;
	}
	else if(error_type=="e4"){
		cout << "缺少运算符+" << endl;
		sta.push("+");
		sta.push("6");	flag=1;
	}
	else if(error_type=="e5"){
		cout << "缺少运算符*" << endl;
		sta.push("*");
		sta.push("7");	flag=1;
	}
	return ;
}

void analyse(){
	string state;
	string next;
	string res;
	string left;
	while(true){
		//先看看栈顶的状态 
		state = sta.top();                 //cout << "state = " << state << endl;
		//取下一个输入 
		next = input.front();              //cout << "next = "  << next << endl;
		//查找相应的动作 
		it = Action.end();
		it = Action.find(item(state,next));   
		while(it==Action.end()){//如果出错，就扔了这个符号，接着看下一个 
		//	cout << "error" << endl;
			show();
			//进入错误处理过程
			analyse_error(state,next); 
			//input.pop();
			if(input.empty()){
				cout << "结束" << endl; 
				return ;
			}
			next = input.front();              //cout << "next = "  << next << endl;
			state = sta.top();
			it = Action.find(item(state,next));		
		}
		res = it->second;   //好，现在我们已经找到了相应的动作 
		//移进
		if(res.size()<=2){
			show();
		//	cout << "移进" << endl;	
			state=it->second;     //得到移进后的状态 
			sta.push(next);        
			sta.push(state);
			input.pop(); 
			
		}
		//规约
		else if(res.size()>2&&res!="acc"){
			show();
		//	cout << "按" << res << "规约" << endl; 
			//得到规约后的非终结符，即生成式的左部
			string left; 
			left = res.substr(0,1);
			//下面是计算
			if(res=="F->id"){	
				F.push(NUM.front());
				NUM.pop();
			}
			if(res=="F->(E)"){
				F.push(E.top());
				E.pop();
			}
			if(res=="T->F"){
				T.push(F.top());
				F.pop();
			}
			if(res=="E->T"){
				E.push(T.top());
				T.pop();
			}
			if(res=="E->E+T"){
				int num1 = E.top();
				E.pop();
				int num2 = T.top();
				T.pop();
				E.push(num2+num1);
			}
			if(res=="T->T*F"){
				double num1 = T.top();
				T.pop();
				double num2 = F.top();
				F.pop();
				T.push(num2*num1);
			}
			if(res=="E->E-T"){
				double num1 = E.top();
				E.pop();
				double num2 = T.top();
				T.pop();
				E.push(num1-num2);}
			if(res=="T->T/F"){
				double num1 = T.top();
				T.pop();
				double num2 = F.top();
				F.pop();
				T.push(num1/num2);}
			//首先弹出生成式右部（右部长度*2）
			int length; 
			if(res.size()!=5)//不含id 
				length = 2*(res.size()-3);
			else if(res.size()==5) // 含id 
				length = 2;
			for(int i=0;i<length;i++)
				sta.pop();
				
			//看看栈顶状态 
			state = sta.top();
			//得到规约后的状态(用栈顶的状态和用于规约的生成式的左部)
			state = Goto(state,left);
			sta.push(left);
			sta.push(state); 
		}
		//接受
		else if(res=="acc"){
			show();
		//	cout << "接受" << endl;
			return ; 
		}
	}
} 
 
 
int main(){
Action[item("0","id")] = "5";
Action[item("0","(")] = "4";
 
Action[item("1","$")] = "acc";
Action[item("1","+")] = "6";
Action[item("1","-")] = "7";
 
Action[item("2","*")] = "8";
Action[item("2","/")] = "9";
Action[item("2","+")] = "E->T";
Action[item("2","-")] = "E->T";
Action[item("2",")")] = "E->T"; 
Action[item("2","$")] = "E->T";
 
Action[item("3","+")] = "T->F";
Action[item("3","-")] = "T->F";
Action[item("3","*")] = "T->F";
Action[item("3","/")] = "T->F";
Action[item("3",")")] = "T->F";
Action[item("3","$")] = "T->F";
 
Action[item("4","id")] = "5";
Action[item("4","(")] = "4";
 
Action[item("5","+")] = "F->id";
Action[item("5","-")] = "F->id";
Action[item("5","*")] = "F->id";
Action[item("5","/")] = "F->id";
Action[item("5",")")] = "F->id";
Action[item("5","$")] = "F->id";
 
Action[item("6","id")] = "5";
Action[item("6","(")] = "4";
 
Action[item("7","id")] = "5";
Action[item("7","(")] = "4";
 
Action[item("8","id")] = "5";
Action[item("8","(")] = "4";
 
Action[item("9","id")] = "5";
Action[item("9","(")] = "4";
 
Action[item("10","+")] = "6";
Action[item("10","-")] = "7";
Action[item("10",")")] = "15";
 
Action[item("11","*")] = "8";
Action[item("11","/")] = "9";
Action[item("11","+")] = "E->E+T";
Action[item("11","-")] = "E->E+T";
Action[item("11",")")] = "E->E+T";
Action[item("11","$")] = "E->E+T";
 
Action[item("12","*")] = "8";
Action[item("12","/")] = "9";
Action[item("12","+")] = "E->E-T";
Action[item("12","-")] = "E->E-T";
Action[item("12",")")] = "E->E-T";
Action[item("12","$")] = "E->E-T";
 
Action[item("13","+")] = "T->T*F";
Action[item("13","-")] = "T->T*F";
Action[item("13","*")] = "T->T*F";
Action[item("13","/")] = "T->T*F";
Action[item("13",")")] = "T->T*F";
Action[item("13","$")] = "T->T*F";
 
Action[item("14","+")] = "T->T/F";
Action[item("14","-")] = "T->T/F";
Action[item("14","*")] = "T->T/F";
Action[item("14","/")] = "T->T/F";
Action[item("14",")")] = "T->T/F";
Action[item("14","$")] = "T->T/F";
 
Action[item("15","+")] = "F->(E)";
Action[item("15","-")] = "F->(E)";
Action[item("15","*")] = "F->(E)";
Action[item("15","/")] = "F->(E)";
Action[item("15",")")] = "F->(E)";
Action[item("15","$")] = "F->(E)";
 
 
 
Error[item("0","+")] = "e1";
Error[item("0","id")]= "e1";
Error[item("4","+")] = "e1";
Error[item("4","id")]= "e1";
Error[item("6","+")] = "e1";
Error[item("6","id")]= "e1";
Error[item("0",")")] = "e2";
Error[item("1",")")] = "e2";
Error[item("4",")")] = "e2";
Error[item("6",")")] = "e2";
Error[item("7",")")] = "e2";
Error[item("8","$")] = "e3";
Error[item("1","id")]= "e4";
Error[item("1","(")] = "e4";
Error[item("8","id")]= "e4";
Error[item("8","(")] = "e4";
Error[item("2","id")]= "e5";
Error[item("2","(")] = "e5";
Error[item("9","id")]= "e5";
Error[item("9","(")] = "e5";
 
sta.push("0");
 
 
char in[100];
cin.getline(in,100);
string in1 = in;
handle(in1);
analyse();
if(flag!=1)
{cout << E.top();}
return 0;
}
