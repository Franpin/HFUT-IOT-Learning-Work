#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int stop[9][2]={{0,0},{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
//马可以走到的位置
int bx,by,mx,my;
int f[22][22];//f[i][j]代表从A点到(i,j)会经过的线路数
int horse(int x,int y){
	for(int i=0;i<9;i++){
		int tx=mx+stop[i][0];
		int ty=my+stop[i][1];
		if(x==tx&&y==ty){
			return 0;
		}
	}	
	return 1;
}
int main(){
    scanf("%d%d%d%d", &bx, &by, &mx, &my);
    bx += 2; by += 2; mx += 2; my += 2;
    //坐标+1以防越界
    f[2][2] = 1;//初始化
    for(int i = 2; i <= bx; i++){
        for(int j = 2; j <= by; j++){
            if(!horse(i,j))continue;
            f[i][j] = max( f[i][j] , f[i - 1][j] + f[i][j - 1] ); 
            //状态转移方程
        }
    }
    printf("%d\n", f[bx][by]);
    return 0;
} 
