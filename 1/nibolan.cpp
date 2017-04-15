#include <iostream>
#include <string>
#include <vector>
#include<stack>
#include <sstream>  
using namespace std;

/*��ȡ�û��ַ��������н�ȡ���string����*/
vector<string> getStrList(char * str)
{
	char ch;
	int num = 0;
	vector<string> list;
	ch = str[num];
	string temp = "";

	while (ch != '\0')
	{

		if (ch >= '0'&&ch <= '9')//����
		{
			temp += ch;
			ch = str[++num];
		}
		else                //�����
		{
			string s_ch;   //�������ת��Ϊstring���ͣ�char��>string��
			stringstream stream;
			stream << ch;
			s_ch = stream.str();

			list.push_back(temp);
			list.push_back(s_ch);
			temp = "";
			ch = str[++num];

		}

	}
	list.push_back(temp);

	return list;
}


/*�������ȼ���*/ 
int priority(string str)//��ʵֻ��Ҫ��+-*/ ����,��Ϊ�˿��������ַ������ȼ��Ͷ�д��Щ
{	
	int i=-1;
	if (str == "(")
		i = 1;
	else if (str == "+" || str == "-")
		i = 2;
	else if (str == "*" || str == "/")
		i = 3;
	else if (str == ")")
		i = 4;
	return i;
	

}


/*�ж�һ���ַ����Ƿ�Ϊ����*/
bool isNum(string str)
{
	stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d))
		return false;
	if (sin >> c)
		return false;
	return true;
}

/*��һ���ַ���ת��Ϊint*/
int str2num(string s)
{
	int num;
	stringstream ss(s);
	ss >> num;
	return num;
}
/*��vector �ַ���ת��Ϊ�沨�����ʽ*/
vector<string> trans(vector<string> & data)
{
	vector<string>result;//�����
	stack<string> operate;//��������ջ

	//�������ݼ��е�ÿһ��Ԫ��
	for (int i = 0;i < data.size();i++)
	{		
		if (isNum(data[i]))//����,ֱ��������
		{
			result.push_back(data[i]);
		}
		else if (data[i]=="(")//������,ֱ��ѹջ
		{
			operate.push(data[i]);
		}
		else if (data[i] ==")")//������,�������ϵ�ջֱ������������
		{
			while(!operate.empty()&&operate.top() != "(")//����ջ��Ϊ��,����ջ��Ԫ�ز���������
			{
				result.push_back(operate.top());
				operate.pop();
			}
			operate.pop();

		}
		else if(operate.empty()||priority(data[i])>priority(operate.top()))
		{
			operate.push(data[i]);
		}
		else
		{
			while (!operate.empty()&&priority(data[i]) <= priority(operate.top()))
			{
				result.push_back(operate.top());
				operate.pop();
			}
			operate.push(data[i]);
		}
	}

	//���ݼ���������,��ջ��ʣ���Ԫ��ȫ����ӵ������
	while (!operate.empty())
	{
		result.push_back(operate.top());
		operate.pop();
	}

	return result;
}

/*�����沨�����ʽ*/
double getResult(vector<string> & data)
{
	double  c, a, b;
	stack<double> operate;
	for (int i = 0; i < data.size(); i++)
	{
		if (isNum(data[i]))        //����,ת��Ϊʵ��double�����ջ
		{			
			operate.push(atof(data[i].c_str()));
		}
		else if (data[i] == "+")
		{
			b = operate.top();
			operate.pop();
			a = operate.top();
			operate.pop();
			c = a + b;
			operate.push(c);
		}
		else if (data[i] == "-")
		{
			b = operate.top();
			operate.pop();
			a = operate.top();
			operate.pop();
			c = a - b;
			operate.push(c);
		}
		else if (data[i] == "*")
		{
			b = operate.top();
			operate.pop();
			a = operate.top();
			operate.pop();
			c = a * b;
			operate.push(c);
		}
		else if (data[i] == "/")
		{
			b = operate.top();
			operate.pop();
			a = operate.top();
			operate.pop();
			c = a / b;
			operate.push(c);
		}
	}
	return operate.top();

}

int main()
{
	
	char str[100];
	cin.getline(str, 100);
	vector<string> rstr;
	rstr = getStrList(str);
	vector<string>nibolan = trans(rstr);
	double r=getResult(nibolan);
	cout << r << endl;
	return 0;
}