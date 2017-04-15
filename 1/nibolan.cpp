#include <iostream>
#include <string>
#include <vector>
#include<stack>
#include <sstream>  
using namespace std;

/*获取用户字符串并进行截取获得string数组*/
vector<string> getStrList(char * str)
{
	char ch;
	int num = 0;
	vector<string> list;
	ch = str[num];
	string temp = "";

	while (ch != '\0')
	{

		if (ch >= '0'&&ch <= '9')//数字
		{
			temp += ch;
			ch = str[++num];
		}
		else                //运算符
		{
			string s_ch;   //将运算符转化为string类型（char—>string）
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


/*定义优先级别*/ 
int priority(string str)//其实只需要有+-*/ 即可,但为了看出其他字符的优先级就多写了些
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


/*判断一个字符串是否为数字*/
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

/*把一个字符串转化为int*/
int str2num(string s)
{
	int num;
	stringstream ss(s);
	ss >> num;
	return num;
}
/*将vector 字符串转化为逆波兰表达式*/
vector<string> trans(vector<string> & data)
{
	vector<string>result;//结果集
	stack<string> operate;//操作运算栈

	//遍历数据集中的每一个元素
	for (int i = 0;i < data.size();i++)
	{		
		if (isNum(data[i]))//数字,直接入结果集
		{
			result.push_back(data[i]);
		}
		else if (data[i]=="(")//左括号,直接压栈
		{
			operate.push(data[i]);
		}
		else if (data[i] ==")")//右括号,连续不断弹栈直到遇到左括号
		{
			while(!operate.empty()&&operate.top() != "(")//操作栈不为空,并且栈顶元素不是右括号
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

	//数据集遍历结束,将栈中剩余的元素全部添加到结果中
	while (!operate.empty())
	{
		result.push_back(operate.top());
		operate.pop();
	}

	return result;
}

/*计算逆波兰表达式*/
double getResult(vector<string> & data)
{
	double  c, a, b;
	stack<double> operate;
	for (int i = 0; i < data.size(); i++)
	{
		if (isNum(data[i]))        //数字,转化为实际double入操作栈
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