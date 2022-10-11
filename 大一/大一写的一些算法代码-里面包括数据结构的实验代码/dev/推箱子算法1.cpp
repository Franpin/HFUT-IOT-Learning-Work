#include<iostream>
using namespace std;
#include<queue>
int state[5][5][5][5][5][5]={0};//Á½¸öÏä×Ó 
int map[5][5]={
	{4,4,4,4,4},
	{4,6,0,3,4},
	{4,5,5,0,4},
	{4,6,0,0,4},
	{4,4,4,4,4}, 
};//1,3,2,2,2,3
int next[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool bound(int x,int y){
	if(x>=0&&x<5&&y>=0&&y<5&&map[x][y]!=4)
		return true;
	else
		return false;
}
struct node{
	int data;
	int *bx,*by,px,py;
	node (int x1,int y1,int x2[2],int y2[2]){
		px=x1;
		py=y1;
		bx=x2;
		by=y2;
	}
};

int bfs(int px,int py,int dx[2],int dy[2]){
	queue<node>q;
	node h(px,py,dx,dy);
	q.push(h);
	state[px][py][dx[0]][dy[0]][dx[1]][dy[1]]=1;
	while(!q.empty()){
		int tx[2],ty[2],px,py;
		node head=q.front();
		q.pop();
	//	cout<<head.px<<","<<head.py<<endl;
		for(int i=0;i<4;i++)
	{
			int t=0;
			int j;
			int *bx=new int[2],*by=new int[2];
			px=head.px+next[i][0];
			py=head.py+next[i][1];
			
			bx[0]=head.bx[0];
			bx[1]=head.bx[1];
			by[0]=head.by[0];
			by[1]=head.by[1];
			for(int m=0;m<2;m++){
			if(px==head.bx[m]&&py==head.by[m]){
						j=m;
						t=1;
						//cout<<"1231312321321";
					}
						
			}
			if(t){
			bx[j]=head.bx[j]+next[i][0];
			by[j]=head.by[j]+next[i][1];
			
				if(!bound(px,py)||!bound(bx[j],by[j])||bx[0]==bx[1]&&by[0]==by[1]||state[px][py][bx[0]][by[0]][bx[1]][by[1]]!=0){
								continue;
				}
				//cout<<"j="<<j<<","<<px<<","<<py<<","<<bx[0]<<","<<by[0]<<","<<bx[1]<<","<<by[1]<<endl;
				if(map[bx[1]][by[1]]==6&&map[bx[0]][by[0]]==6){
					cout<<"people= "<<px<<","<<py<<endl;
					cout<<"box1= "<<bx[0]<<","<<by[0]<<endl;
					cout<<"box2= "<<bx[1]<<","<<by[1]<<endl;
					return 1;
				}		
				state[px][py][bx[0]][by[0]][bx[1]][by[1]]=1;
				
				q.push(node(px,py,bx,by));
			}
			else{
			if(bound(px,py)&&state[px][py][head.bx[0]][head.by[0]][head.bx[1]][head.by[1]]==0){
			
			state[px][py][head.bx[0]][head.by[0]][head.bx[1]][head.by[1]]=1;
			q.push(node(px,py,head.bx,head.by));
			}
		}	
	}
}			 
	return 0;	
}

int main(){
	//4,1,2,2,2,3
	int bx[2]={2,2};
	int by[2]={1,2};
	if(bfs(1,3,bx,by)){
		cout<<"ok,finish1"<<endl; 
	}
	else
		cout<<"NO find! "<<endl;
}
