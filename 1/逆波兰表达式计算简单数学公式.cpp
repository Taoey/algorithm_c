#include<iostream>
#include<stack>
#include <stdlib.h>
#include<stdio.h>


using namespace std;

//��һ����ʽ��ת��Ϊ�沨�����ʽ

int Priority(char ch)//�������ȼ��� 
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
		else if(*ch=='(')//������ֱ��ѹջ 
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

//�����沨�����ʽ��ֵ

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
					st.push(((a-'0')+(b-'0')+'0'));//ע�����͵����� 
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
						cout<<"����Ϊ0����"<<endl; 
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
	cout<<"��ʽ���沨�����ʽΪ��"<<endl; 
	while(len--)
	{
		cout<<' '<<ret[i++];
	}

	cout<<"\n��ʽ�ļ�����Ϊ��"<<endl;
	cout<<calcval(ret)<<endl;
	//calcval(ret);     
	return 0;
}