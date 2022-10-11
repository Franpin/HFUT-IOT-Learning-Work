#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
int r,j,c=77;
int map[20][20]={
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
struct snake{
	int x;
	int y;
};
snake a[1000];
void gotoxy(int x,int y){
	COORD pos={x,y};	
	HANDLE hout;
	hout =GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,pos); 
} 
void creatmap(){
	gotoxy(0,0);
	for(int i=0;i<20;i++){
	for(int m=0;m<20;m++)
	switch(map[i][m]){
	case 0:
		cout<<"  ";
		break;
	case 1:
		cout<<"¡ö";
		break;
	case 2:
		cout<<"¡î";
		break;
	case 3:
		cout<<"¡ñ";
		break; 
}
cout<<endl;		
}
}
void food(){
	srand((unsigned int)time(NULL));
	r=1+rand()%18;
	j=1+rand()%18;
	map[r][j]=3;
}
void creatsnake(int n){
	for(int i=0;i<n;i++)
	{
		a[i].x=10-i;
		a[i].y=10;
		map[a[i].y][a[i].x]=2;
	}
}
int endplay(int n){
int t=0;
if(a[0].x==19||a[0].x==0||a[0].y==19||a[0].y==0)	
	return 1;
	for(int i=1;i<n;i++)
		if(a[0].x==a[i].x&&a[0].y==a[i].y)
		t=1;
	if(t)	
	return 1;

	return 0;
}
void move(int n,int c){		
		for(int i=n-1;i>0;i--)
	{
		map[a[i].y][a[i].x]-=2;
		a[i].x=a[i-1].x;
		a[i].y=a[i-1].y;	
	}	
	switch(c){
	case 72:
	a[0].y--;
	break;
	case 80:
	a[0].y++;
	break;
	case 75:
	a[0].x--;
	break;
	case 77:
	a[0].x++;
	break;
}
for(int i=0;i<n;i++)
	{
		map[a[i].y][a[i].x]=2;	
	}	
}

void pushkey(int &t){
	int m,b;
	if(kbhit()){
	b=getch();
	if(b==224){
	m=getch();
	if(c==72&&m!=80||c==80&&m!=72||c==75&&m!=77||c==77&&m!=75)
			c=m;		
		}
	if(b==112)
	t-=100;
}
}
int main(){
	int t=300;
	int n=4;
	food();	
	creatsnake(n);
	creatmap();	
	while(1){
	pushkey(t);
	move(n,c);
	creatmap();
	if(a[0].x==j&&a[0].y==r)
	{
		n++;
		food();
	}
	if(endplay(n))
	break;
	Sleep(t);	
}
cout<<"game over!"<<endl;
return 0;
}
