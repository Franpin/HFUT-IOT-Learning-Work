#include<stdio.h>
int main(){
	int n;
	int num[1000][3];
	scanf("%d",&n);
	for(int i=0;i<n;i++){//输入 
		scanf("%d %d %d",&num[i][0],&num[i][1],&num[i][2]);
	}
	for(int i=0;i<n;i++){
		int flag=0;//逻辑标志初始化，当不能组成等式时，标志才不会发生改变 
		if(num[i][0]+num[i][1]==num[i][2]){
			flag=1;
		}
		if(num[i][0]-num[i][1]==num[i][2]){
			flag=1;
		}
		if(num[i][0]*num[i][1]==num[i][2]){
			flag=1;
		}
		if(num[i][1]!=0){//除数不能为0 
			if(double(num[i][0])/num[i][1]==num[i][2]){
				flag=1;
			}
			if(num[i][0]%num[i][1]==num[i][2]){
				flag=1;
			}
		}
		
		if(flag==0){//标志相应 
			printf("NO\n");
		}else{//flag==1表示前面的条件其中之一满足了 
			printf("YES\n");
		}
	}
	return 0;
}
