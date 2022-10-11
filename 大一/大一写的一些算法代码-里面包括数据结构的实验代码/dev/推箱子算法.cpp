#include<iostream>
using namespace std;
#include<queue>
int state[5][5][5][5]={0};
int map[5][5]={
	{4,0,0,0,4},
	{4,0,0,6,4},
	{4,0,3,0,4},
	{4,0,5,0,4},
	{4,0,0,4,4}, 
};//,2,2,3,2
int next[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
bool bound(int x1,int y1,int x2,int y2){
	if(x1>=0&&x1<5&&x2>=0&&x2<5&&y1>=0&&y1<5&&2>=0&&y2<5&&state[x1][y1][x2][y2]==0&&map[x1][y1]!=4&&map[x2][y2]!=4)
		return true;
	else
		return false;
}
struct node{
	int data;
	int bx,by,px,py;
	node (int x1,int y1,int x2,int y2){
		px=x1;
		py=y1;
		bx=x2;
		by=y2;
	}
};

int bfs(int px,int py,int bx,int by){
	queue<node>q;
	node head(px,py,bx,by);
	q.push(head);
	state[px][py][bx][by]==1;
	while(!q.empty()){
		int tx,ty,px,py;
		head=q.front();
		cout<<head.px<<","<<head.py<<"£»"<<head.bx<<","<<head.by<<endl;
		q.pop();
		for(int i=0;i<4;i++)
	{
			
			px=head.px+next[i][0];
			py=head.py+next[i][1];
			if(px==head.bx&&py==head.by){
				bx=head.bx+next[i][0];
				by=head.by+next[i][1];
			
				if(!bound(px,py,bx,by)){
					continue;
				}
				if(map[bx][by]==6){
					cout<<"people= "<<px<<","<<py<<endl;
					cout<<"box= "<<bx<<","<<by<<endl;
					return 1;
				}
					
				state[px][py][bx][by]=1;
				q.push(node(px,py,bx,by));
				
			}
			else{
			if(bound(px,py,head.bx,head.by)){
				state[px][py][head.bx][head.by]=1;
				q.push(node(px,py,head.bx,head.by));
			}
		}
	}
}			 
	return 0;	
}

int main(){
	if(bfs(2,2,3,2)){
		cout<<"ok,finish1"<<endl; 
	}
	else
		cout<<"NO find! "<<endl;
}
