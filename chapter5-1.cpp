#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;
string input;//�����ַ��� 
size_t i=0;//�����ַ���ָ�룻 
stack <string> work;//ջ 
stack <string> val;

//�ķ� 
unordered_map <int,string> grammer{
{1,"E->E+T"},
{2,"E->T"},
{3,"T->T*F"},
{4,"T->F"},
{5,"F->(E)"},
{6,"F->id"}
};
//������ 
unordered_map<string,int> terminal={
{"id",0},
{"+",1},
{"*",2},
{"(",3},
{")",4},
{"$",5}	
};
unordered_map<string,int> nonterminal{
	{"E",0},
	{"T",1},
	{"F",2}
};
string Action[12][6];
string Goto[12][3];
void initial()
{
	work.push("0");
for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 6; j++) {
            Action[i][j] = "error"; // ��ÿ��Ԫ������Ϊ���ַ���
        }
    }	
    for (int i = 0; i < 12; i++) {
	        for (int j = 0; j < 3; j++) {
	            Goto[i][j] = "error"; // ��ÿ��Ԫ������Ϊ���ַ���
	        }
	    }
	    Action[0][0]="s5";
	    Action[0][3]="s4";
	    Action[1][1]="s6";
	    Action[1][5]="acc";
	    Action[2][1]="r2";
	    Action[2][2]="s7";
	    Action[2][4]="r2";
	    Action[2][5]="r2";
	    Action[3][1]="r4";
	    Action[3][2]="r4";
	    Action[3][4]="r4";
	    Action[3][5]="r4";
	    Action[4][0]="s5";
	    Action[4][3]="s4";
	    Action[5][1]="r6";
	    Action[5][2]="r6";
	    Action[5][4]="r6";
	    Action[5][5]="r6";
	    Action[6][0]="s5";
	    Action[6][3]="s4";
	    Action[7][0]="s5";
	    Action[7][3]="s4";
	    Action[8][1]="s6";
	    Action[8][1]="s11";
	    Action[9][1]="r1";
	    Action[9][2]="s7";
	    Action[9][4]="r1";
	    Action[9][5]="r1";
	    Action[10][1]="r3";
	    Action[10][2]="r3";
	    Action[10][4]="r3";
	    Action[10][5]="r3";
	    Action[11][1]="r5";
	    Action[11][2]="r5";
	    Action[11][4]="r5";
	    Action[11][5]="r5"; 
	    Goto[0][0]="1";
	    Goto[0][1]="2";
	    Goto[0][2]="3";
	    Goto[4][0]="8";
	    Goto[4][1]="2";
	    Goto[4][2]="3";
	    Goto[6][1]="9";
		Goto[6][2]="3";
		Goto[7][2]="10";
			    
}
int flag=0;
int flag_id =0;
void LR(string input)
{
	
	while(flag!=1){
		//���actionԪ��
		//ջ��״̬��ȡ
		if(i==input.length()){
			break;
				 }
		string state=work.top();
	
		int s =stoi(state);
	
		//��������Ӧ������ֵ 
		string in;
		if(input.substr(i,1)=="i"){
			in=input.substr(i,2);
			flag_id=1;
		}else{
			in=input.substr(i,1);
			flag_id=0;
		}
		
	
	
		 int a=terminal[in];
		 //��ȡactionֵ
		 string action;
		 action=Action[s][a];
		 
		if(action[0]=='s'){
		//	cout<<"�ƽ�"<<endl;
			work.push(in);
			val.push(in);	
			work.push(string (1,action[1]));
			//�ƽ����ƶ�����ָ�� 
			if(flag_id){
				i+=2;
			}else{
				i++;
			}
			
		}else if(action[0]=='r'){
		
			//��ȡ��Լ�ڼ����ķ� 
			int number =stoi(string(1,action[1]));
			
			//��ø��ķ� 
			string gram=grammer[number];
		//	cout<<"��"<<grammer[number]<<"��Լ"<<endl;
			if(number==3||number==1){
				string temp=val.top();
			
				int a=stoi(temp);
					val.pop();
					string op =val.top();
					val.pop();
				    temp=val.top();
					int b=stoi(temp);
					val.pop();
					if(op=="*"){
						int sum=a*b;
						val.push(to_string(sum));
						
					}else{
					   int sum=a+b;
						val.push(to_string(sum));
					}//TODO
			}
			
			//��ȡ�ķ��Ҳ� �Լ��� 
			size_t arrowPos = gram.find("->");
			string gram_leftSide = gram.substr(0, arrowPos);
			string gram_rightSide = gram.substr(arrowPos + 2);
			//��ȡ�³��� 
			size_t gram_right_len=gram_rightSide.length();
			if(gram_rightSide.find("id")!=string::npos){
				gram_right_len-=1;
			}
			//��ջ
			for(size_t i=0;i<gram_right_len*2;i++){
				work.pop();
			} 
			//���goto������ 
			int t=stoi(work.top());
			int A=nonterminal[gram_leftSide];
			//ѹջ
			work.push(gram_leftSide);
			work.push(Goto[t][A]);
			
		}else if(action=="acc"){
		//	cout<<"����"<<endl;
			string sum =val.top();
			cout<<stoi(sum)<<endl;
			break;
		}else{
			cout<<"������������������"<<endl;
			break;
		}
	}
}

int main()
{
	initial();
	
    cin >> input;
   input += "$";  // ��ӽ�������
    LR(input);
    return 0;
}
