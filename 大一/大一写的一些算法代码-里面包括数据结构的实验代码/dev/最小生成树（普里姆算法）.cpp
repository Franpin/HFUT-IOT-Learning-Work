#include<iostream>
using namespace std;
double map[8][8]={		//初始化邻接矩阵 
	{0  ,1.3,2.1,0.9,0.7,1.8,2.0,1.8}, 
	{1.3,0  ,0.9,1.8,1.2,2.8,2.3,1.1},
	{2.1,0.9,0  ,2.6,1.7,2.5,1.9,1.0},
	{0.9,1.8,2.6,0  ,0.7,1.6,1.5,0.9},
	{0.7,1.2,1.7,0.7,0  ,0.9,1.1,0.8},
	{1.8,2.8,2.5,1.6,0.9,0  ,0.6,1.0},
	{2.0,2.3,1.9,1.5,1.1,0.6,0  ,0.5},
	{1.8,1.1,1.0,0.9,0.8,1.0,0.5,0  }
}; 
void MiniSpanTree_Prim(){
	double lowcost[8]={0};//储存最小边 
	int adjvex[8]={0}; //储存顶点 
	int k=0;
	for(int i=1;i< 8;i++){
		lowcost[i]=map[k][i];
	}
	for(int i=1;i< 8;i++){
		double min=10000;		//初始化最小权值
		//遍历全部顶点 
		for(int j=1;j< 8;j++){
			//找出lowcost数组已存储的最小权值 
			if(lowcost[j]!=0&&lowcost[j]<min)
			{
				min=lowcost[j];
				k=j;		//将发现的最小权值的顶点下标存入k，以待使用 
			}
		}
		//打印当前顶点边中权值最小的边 
		cout<<"("<<adjvex[k]+1<<","<<k+1<<")"<<endl;
		lowcost[k]=0;		//将当前顶点的权值设置为0，表示此顶点已经完成任务，进行下一个顶点的遍历 
		
		//邻接矩阵k行逐个遍历全部顶点 
		for(int j=1;j<8;j++){
			if(lowcost[j]!=0&&map[k][j]<lowcost[j])
			{
				lowcost[j]=map[k][j];
				adjvex[j]=k;
			}
			
		}
	}
} 
int main(){
	cout<<"最小生成树相应的边:"<<endl; 
	MiniSpanTree_Prim(); //调用最小生成树算法 
}
