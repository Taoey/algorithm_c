#include <iostream>
#include<stack>
#include <queue>
#include<fstream>
using namespace std;


class Digraph{
private: 
	int v_num;
	int e_num;
	int *V;   //���㼯��
	int **Matrix;
	int *book_V;//������Ⱥ����������,�����Ƿ񱻷��ʵı�ǵĹ���
public:
	Digraph(int v_num,int e_num){
		this->v_num=v_num;
		this->e_num=e_num;
		V=new int[v_num];//���ɶ������

		book_V=new int[v_num];//���ɱ�ǹ���
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
	void initMatrix();//��ʼ���߹�ϵ�ľ���
	void initBook_V();//��ʼ����ǹ���
	void input();
	void print();
	void printVertex();
	void delete_edge();

	void BFSpaningTree(int ver);//�������������  ��ver���㿪ʼ����
	void DFSpaningTree(int ver);//�������������

	
};

void Digraph::initMatrix(){
	//������һ������
	Matrix=new int *[v_num];
	for (int i=0;i<v_num;i++){	
		Matrix[i]=new int[v_num];
	}
	//�������ʼ��
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
	int x=-1; //�߹�ϵ���ڵıߵ�����
	int y=-1;
	for(int i=0;i<v_num;i++){
		cout<<"�������"<<i+1<<"������";
		cin>>v_temp;
		V[i]=v_temp;
	}
	for(int i=0;i<e_num;i++){
		cout<<"�������"<<i+1<<"���ߵĵ�һ������";
		cin>>v0;
		cout<<"�������"<<i+1<<"���ߵĵڶ�������";
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
			if(2==count){//�ҵ�������������;
				break;
			}
		}//end for(in)
		if(x==-1||y==-1){
			cout<<"δ�ҵ������ı߹�ϵ,����������:"<<endl;
			i--;
		}
		else{//�����ߵĹ�ϵ��ȷ,���б߹�ϵ�ĸ�ֵ����
			Matrix[x][y]=1;
			Matrix[y][x]=1;
		}
	}//end for(out)


}
void Digraph::print(){
	cout<<"�������ͼ���ڽӾ����ǣ�"<<endl;
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
	cout<<"������Ҫɾ���ıߵĵ�һ�����㣺";
	cin>>v0;
	cout<<"������Ҫɾ���ıߵĵڶ������㣺";
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
	int location=-1;//���λ��
	queue<int> bfs_queue;
	for(int i=0;i<v_num;i++){
		if(ver=V[i]){//�ҵ��ýڵ�,��ý�����λ��
			location=i;
			bfs_queue.push(location);
			book_V[location]=1;//����Ϊ�ѱ���
			break;
		}
	}
	while(!bfs_queue.empty()){//�����ȷ,������ȱ���
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
	/*���߼�:
	�ҵ���ʼ���λ��,��λ����ջ
	�ж�ջ�Ƿ�Ϊ�� --N--->�������λ����,������û�з��ʹ��Ľ����ջ,��ӡ��ϵ,���Ѿ��������Ľ�㵯ջ
	               --Y--->��������
	*/
	int location=-1;//���λ��
	stack<int> dfs_stack;
	for(int i=0;i<v_num;i++){
		if(ver=V[i]){//�ҵ��ýڵ�,��ý�����λ��
			location=i;
			dfs_stack.push(location);
			book_V[location]=1;//����Ϊ�ѱ���
			break;
		}
	}
	while(!dfs_stack.empty()){//�����ȷ,������ȱ���
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
		cout<<"1:���ڽӾ�������һ������ͼ"<<endl;
		cout<<"2:ɾ������ͼ��һ����"<<endl;
		cout<<"3:��ȱ�����"<<endl;
		cout<<"4:��ȱ�����"<<endl;
		cout<<"5:�鿴����"<<endl;
		cout<<"0:�˳�"<<endl;
		cout<<"���������ѡ��:";
		cin>>choose;

		if(1==choose){				
				cout<<"�����붥��ĸ���:";
				cin>>v_number;
				cout<<"������ߵ�����:";
				cin>>e_number;
				graph=new Digraph(v_number,e_number);		//Ҫ�Ӷ��н�������,�������ʹ��Digraph graph(v_number,e_number)�����ɶ����,��������������ٵ�mdzz
				graph->input();
				graph->print();
				graph->printVertex();
			
		}else if(2==choose){		
			graph->delete_edge();
		}else if(3==choose){
			int a;
			cout<<"�����������ʼ�Ľ��";
			cin>>a;
			graph->DFSpaningTree(a);
			graph->initBook_V();
		}else if(4==choose){
			int a;
			cout<<"�����������ʼ�Ľ��";
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