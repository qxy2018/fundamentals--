#include<iostream>
#include<cstring>
#include<map>
#include<stack>
#include<queue>
#include<iomanip> 
#include<stdio.h>
#include<cmath>
using namespace std;
struct item;                   //���״̬���ս�� 
stack<string> sta;             //ջ  
queue<string> input;           //���ڴ�����봮 
map<item,string> Action;       //map���͵�Action������Ϊ̫�����ú���д̫�鷳�� 
map<item,string> :: iterator it;
 
 
queue<double> NUM; 
stack<double> T;
stack<double> F;
stack<double> E; 
map<item,string> Error;       //map���͵Ĵ�������� 
map<item,string> :: iterator itError;
 
string Goto(string state,string nonter){         //Goto���� 
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
 
struct item{                   //��state��nonterminal�����ս���� 
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
 
/*����һ��������Ͳ���Ҫ��������˰��� 
string find(map<item,string> m,item i){
	map<item,string> :: iterator it;
	for(it = m.begin();it!=m.end();it++)
		if(it->first==i)
			return it->second;
	return "mo";
}*/ 
 
void handle(string in){        //�Ѷ���Ĵ��ŵ������� 
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
		else if(in[0]==' ')    //�ո񣬶��� 
			in = in.substr(1); 
		else{                  //�����ģ���һ���ַ� 
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
	//���ջ�е�Ԫ��
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
	//��������е�Ԫ�� 
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
	//	cout << "δ֪���ţ���������" << endl;
		input.pop();flag=1;
		return ;	
	}
	error_type = itError->second;
	if(error_type=="e1"){
		//cout << "ȱ���������" << endl; 
		flag=1;
		cout<<"������������������"<<endl;
		sta.push("id");
		sta.push("5");
	}
	else if(error_type=="e2"){
		cout << "��ƥ����ұ�����" << endl;
		input.pop();	flag=1;
	}
	else if(error_type=="e3"){
		cout << "ȱ��������" << endl;
		sta.push(")");
		sta.push("11");	flag=1;
	}
	else if(error_type=="e4"){
		cout << "ȱ�������+" << endl;
		sta.push("+");
		sta.push("6");	flag=1;
	}
	else if(error_type=="e5"){
		cout << "ȱ�������*" << endl;
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
		//�ȿ���ջ����״̬ 
		state = sta.top();                 //cout << "state = " << state << endl;
		//ȡ��һ������ 
		next = input.front();              //cout << "next = "  << next << endl;
		//������Ӧ�Ķ��� 
		it = Action.end();
		it = Action.find(item(state,next));   
		while(it==Action.end()){//�������������������ţ����ſ���һ�� 
		//	cout << "error" << endl;
			show();
			//������������
			analyse_error(state,next); 
			//input.pop();
			if(input.empty()){
				cout << "����" << endl; 
				return ;
			}
			next = input.front();              //cout << "next = "  << next << endl;
			state = sta.top();
			it = Action.find(item(state,next));		
		}
		res = it->second;   //�ã����������Ѿ��ҵ�����Ӧ�Ķ��� 
		//�ƽ�
		if(res.size()<=2){
			show();
		//	cout << "�ƽ�" << endl;	
			state=it->second;     //�õ��ƽ����״̬ 
			sta.push(next);        
			sta.push(state);
			input.pop(); 
			
		}
		//��Լ
		else if(res.size()>2&&res!="acc"){
			show();
		//	cout << "��" << res << "��Լ" << endl; 
			//�õ���Լ��ķ��ս����������ʽ����
			string left; 
			left = res.substr(0,1);
			//�����Ǽ���
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
			//���ȵ�������ʽ�Ҳ����Ҳ�����*2��
			int length; 
			if(res.size()!=5)//����id 
				length = 2*(res.size()-3);
			else if(res.size()==5) // ��id 
				length = 2;
			for(int i=0;i<length;i++)
				sta.pop();
				
			//����ջ��״̬ 
			state = sta.top();
			//�õ���Լ���״̬(��ջ����״̬�����ڹ�Լ������ʽ����)
			state = Goto(state,left);
			sta.push(left);
			sta.push(state); 
		}
		//����
		else if(res=="acc"){
			show();
		//	cout << "����" << endl;
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
