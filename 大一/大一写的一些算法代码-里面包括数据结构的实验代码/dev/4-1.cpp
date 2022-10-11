#include "stdio.h"
int get_lenth(char a[]){//获取数组长度的函数 
	int i;
	for(i=0;a[i]!=0;i++){
	}
	return i;
} 
void insert(char a[],int j,char ch){//插入操作 
	int lenth=get_lenth(a);
	for(int i=lenth;i>j;i--){
		a[i]=a[i-1];
	}
	a[j]=ch;
}
int main(){
	char str[1000]={0};//初始化为全零 
	scanf("%s",str);
	char ch;
	int n;
	scanf("%d %c",&n,&ch);
	for(int p=0;p<n;p++){
		int i,j,flag=0;
		scanf("%d %d",&i,&j);
		for(int x=i-1;x<j;x++){
			if(str[x]==ch){
				str[x]='$';//把他设置成'$'表示删除它 
				flag=1;
				break;
			}
		}
		if(flag==0){
			insert(str,j,ch);//插入运算 
		}
	}
	for(int i=0;str[i]!=0;i++){//结果查看 
		if(str[i]!='$'){
			printf("%c",str[i]);
		}
	}
	return 0;
}
