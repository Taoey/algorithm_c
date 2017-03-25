#include<iostream>
#include<stack>
#include <stdlib.h>
#include<stdio.h>


using namespace std;

//把一个算式先转化为逆波兰表达式

int Priority(char ch)//定义优先级别 
{
	int i;
	switch(ch)
	{
	case'(':i=1;break;
	case'+':i=2;break;
	case'-':i=2;break;
	case'*':i=4;break;
	case'/':i=4;break;
	case')':i=5;break;
	default:i=-1;break;
	}
	return i; 
}
void tonibolan(char *ch,char retch[100])
{
	stack<char> st2;
	int i=0;
	while(*ch!='\0')
	{
		if(*ch>='0'&&*ch<='9')
		{
			retch[i++]=*ch;
		}
		else if(*ch=='(')//左括号直接压栈 
		{
			st2.push(*ch);
		}
		else if(*ch==')')
		{
			while(st2.top()!='(')
			{
				retch[i++]=st2.top();
				st2.pop();
			}
			if(st2.top()=='(')
			{
				st2.pop();
			}

		}
		else if(st2.empty()||Priority(*ch)>Priority(st2.top()))
		{
			st2.push(*ch);
		}
		else 
		{
			while(Priority(*ch)<=Priority(st2.top()))
			{
				retch[i++]=st2.top();
				st2.pop();
				if(st2.empty())
				{
					break;
				}   
			}
			st2.push(*ch);
		}   
		ch++;   
	}

	while(!st2.empty())
	{
		retch[i++]=st2.top();
		st2.pop();  
	}

} 

//计算逆波兰表达式的值

int calcval(char *ret)
{

	stack<char> st;
	while(*ret!='\0')
	{
		if(*ret>='0'&&*ret<='9')
		{
			st.push(*ret);
		}
		else
		{
			switch(*ret)
			{
			case'+':
				{
					char a=st.top();
					st.pop();
					char b=st.top();
					st.pop();
					st.push(((a-'0')+(b-'0')+'0'));//注意类型的运算 
					break;
				}
			case'-':
				{
					char a=st.top();
					st.pop();
					char b=st.top();
					st.pop();
					st.push(((b-'0')-(a-'0'))+'0');
					break;
				}   
			case'*':
				{
					char a=st.top();
					st.pop();
					char b=st.top();
					st.pop();
					st.push(((b-'0')*(a-'0'))+'0');
					break;
				}
			case'/':
				{
					char a=st.top();
					st.pop();
					char b=st.top();
					st.pop();
					if(a!='0')
					{
						st.push((((b-'0')/(a-'0'))+'0'));
					}
					else
					{
						cout<<"除数为0错误"<<endl; 
					}
					break;
				}                   
			}  
		}
		//cout<<*ret;
		ret++;
	}


	return st.top()-'0';
} 


int main()
{
	char ret[100]={0};
	char ch[100]={0};
	cin.get(ch,100);
	tonibolan(ch,ret);
	int len=sizeof(ret)/sizeof(0);
	int i=0;
	cout<<"算式的逆波兰表达式为："<<endl; 
	while(len--)
	{
		cout<<' '<<ret[i++];
	}

	cout<<"\n算式的计算结果为："<<endl;
	cout<<calcval(ret)<<endl;
	//calcval(ret);     
	return 0;
}