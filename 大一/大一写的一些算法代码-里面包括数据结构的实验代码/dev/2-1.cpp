#include<stdio.h>
int main(){
	int n;
	int num[1000][3];
	scanf("%d",&n);
	for(int i=0;i<n;i++){//���� 
		scanf("%d %d %d",&num[i][0],&num[i][1],&num[i][2]);
	}
	for(int i=0;i<n;i++){
		int flag=0;//�߼���־��ʼ������������ɵ�ʽʱ����־�Ų��ᷢ���ı� 
		if(num[i][0]+num[i][1]==num[i][2]){
			flag=1;
		}
		if(num[i][0]-num[i][1]==num[i][2]){
			flag=1;
		}
		if(num[i][0]*num[i][1]==num[i][2]){
			flag=1;
		}
		if(num[i][1]!=0){//��������Ϊ0 
			if(double(num[i][0])/num[i][1]==num[i][2]){
				flag=1;
			}
			if(num[i][0]%num[i][1]==num[i][2]){
				flag=1;
			}
		}
		
		if(flag==0){//��־��Ӧ 
			printf("NO\n");
		}else{//flag==1��ʾǰ�����������֮һ������ 
			printf("YES\n");
		}
	}
	return 0;
}
