#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int stop[9][2]={{0,0},{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
//������ߵ���λ��
int bx,by,mx,my;
int f[22][22];//f[i][j]�����A�㵽(i,j)�ᾭ������·��
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
    //����+1�Է�Խ��
    f[2][2] = 1;//��ʼ��
    for(int i = 2; i <= bx; i++){
        for(int j = 2; j <= by; j++){
            if(!horse(i,j))continue;
            f[i][j] = max( f[i][j] , f[i - 1][j] + f[i][j - 1] ); 
            //״̬ת�Ʒ���
        }
    }
    printf("%d\n", f[bx][by]);
    return 0;
} 
