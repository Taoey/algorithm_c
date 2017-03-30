#include <iostream>
#include<stack>
#include <queue>
#include<fstream>
using namespace std;


class Digraph{
private: 
	int v_num;
	int e_num;
	int *V;   //顶点集合
	int **Matrix;
	int *book_V;//用作广度和深度生成树,顶点是否被访问的标记的工具
public:
	Digraph(int v_num,int e_num){
		this->v_num=v_num;
		this->e_num=e_num;
		V=new int[v_num];//生成顶点矩阵

		book_V=new int[v_num];//生成标记工具
		initMatrix();   
		initBook_V();
	}
	~Digraph(){
		delete []V;
		for (int i=0;i<v_num;i++)
		{
			delete []Matrix[i];
		}
		delete[]Matrix;
	}
	void initMatrix();//初始化边关系的矩阵
	void initBook_V();//初始化标记工具
	void input();
	void print();
	void printVertex();
	void delete_edge();

	void BFSpaningTree(int ver);//广度优先生成树  从ver顶点开始遍历
	void DFSpaningTree(int ver);//深度优先生成树

	
};

void Digraph::initMatrix(){
	//建立起一个矩阵
	Matrix=new int *[v_num];
	for (int i=0;i<v_num;i++){	
		Matrix[i]=new int[v_num];
	}
	//将矩阵初始化
	for(int i=0;i<v_num;i++){
		for(int j=0;j<v_num;j++){
			Matrix[i][j]=0;
		}
	}

}
void Digraph::initBook_V(){
	for(int i=0;i<v_num;i++){
		book_V[i]=0;
	}
}

void Digraph::input(){	
	int v_temp;
	int v0,v1;
	int x=-1; //边关系所在的边的坐标
	int y=-1;
	for(int i=0;i<v_num;i++){
		cout<<"请输入第"<<i+1<<"个顶点";
		cin>>v_temp;
		V[i]=v_temp;
	}
	for(int i=0;i<e_num;i++){
		cout<<"请输入第"<<i+1<<"条边的第一个顶点";
		cin>>v0;
		cout<<"请输入第"<<i+1<<"条边的第二个顶点";
		cin>>v1;
		int count=0;
		for(int j=0;j<v_num;j++){
			if(v0==V[j]){
				x=j;
				count++;
			}
			else if(v1==V[j]){
				y=j;
				count++;
			}
			if(2==count){//找到了这两个顶点;
				break;
			}
		}//end for(in)
		if(x==-1||y==-1){
			cout<<"未找到所给的边关系,请重新输入:"<<endl;
			i--;
		}
		else{//所给边的关系正确,进行边关系的赋值操作
			Matrix[x][y]=1;
			Matrix[y][x]=1;
		}
	}//end for(out)


}
void Digraph::print(){
	cout<<"这个无向图的邻接矩阵是："<<endl;
	for(int i=0;i<v_num;i++){
		for(int j=0;j<v_num;j++){
			cout<<Matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}
void Digraph::printVertex(){
	for(int i=0;i<v_num;i++){
		cout<<V[i]<<" ";
	}
	cout<<endl;
}
void Digraph::delete_edge(){
	int v0,v1,x,y;
	cout<<"请输入要删除的边的第一个顶点：";
	cin>>v0;
	cout<<"请输入要删除的边的第二个顶点：";
	cin>>v1;
	int k=0;
	for (int n=0;n<v_num;n++)
	{
		if (V[n]==v0)
		{
			x=n;
			k++;
		}
		else if (V[n]==v1)
		{
			y=n;
			k++;
		}
		if (k==2)
		{
			break;
		}
	}
	Matrix[x][y]=0;
	Matrix[y][x]=0;

}

void Digraph::BFSpaningTree(int ver){
	int location=-1;//结点位置
	queue<int> bfs_queue;
	for(int i=0;i<v_num;i++){
		if(ver=V[i]){//找到该节点,获得将结点的位置
			location=i;
			bfs_queue.push(location);
			book_V[location]=1;//设置为已遍历
			break;
		}
	}
	while(!bfs_queue.empty()){//结点正确,进行深度遍历
		location=bfs_queue.front();
		for(int i=0;i<v_num;i++){			
			if(Matrix[location][i]==1&&book_V[i]!=1){
				bfs_queue.push(i);
				book_V[i]=1;
				cout<<"<"<<V[location]<<","<<V[i]<<">";
			}
		}
		bfs_queue.pop();
	}
	cout<<endl;
}
void Digraph::DFSpaningTree(int ver){
	/*简单逻辑:
	找到初始结点位置,将位置入栈
	判断栈是否为空 --N--->遍历结点位置行,将列中没有访问过的结点入栈,打印关系,将已经操作过的结点弹栈
	               --Y--->操作结束
	*/
	int location=-1;//结点位置
	stack<int> dfs_stack;
	for(int i=0;i<v_num;i++){
		if(ver=V[i]){//找到该节点,获得将结点的位置
			location=i;
			dfs_stack.push(location);
			book_V[location]=1;//设置为已遍历
			break;
		}
	}
	while(!dfs_stack.empty()){//结点正确,进行深度遍历
		location=dfs_stack.top();
		for(int i=0;i<v_num;i++){			
			if(Matrix[location][i]==1&&book_V[i]!=1){
			dfs_stack.push(i);
			book_V[i]=1;
			cout<<"<"<<V[location]<<","<<V[i]<<">";
			}
		}
		dfs_stack.pop();
	}
	cout<<endl;

}


void main(){
	int choose;
	int v_number;
	int e_number;	
	Digraph *graph;
	while(1){
		cout<<"1:用邻接矩阵描述一个无向图"<<endl;
		cout<<"2:删除无向图的一条边"<<endl;
		cout<<"3:深度遍历树"<<endl;
		cout<<"4:广度遍历树"<<endl;
		cout<<"5:查看顶点"<<endl;
		cout<<"0:退出"<<endl;
		cout<<"请输入操作选项:";
		cin>>choose;

		if(1==choose){				
				cout<<"请输入顶点的个数:";
				cin>>v_number;
				cout<<"请输入边的条数:";
				cin>>e_number;
				graph=new Digraph(v_number,e_number);		//要从堆中建立对象,如果仅仅使用Digraph graph(v_number,e_number)则生成对象后,代码块结束后会销毁的mdzz
				graph->input();
				graph->print();
				graph->printVertex();
			
		}else if(2==choose){		
			graph->delete_edge();
		}else if(3==choose){
			int a;
			cout<<"请输入遍历开始的结点";
			cin>>a;
			graph->DFSpaningTree(a);
			graph->initBook_V();
		}else if(4==choose){
			int a;
			cout<<"请输入遍历开始的结点";
			cin>>a;
			graph->BFSpaningTree(a);
			graph->initBook_V();
		}else if(5==choose){
			graph->print();
		}
		else{
			exit(1);
		}			
	}
}