#include<stdio.h>
int main(){
	char str[10000]={0};
	scanf("%s\n",str);
	char a,b;
	scanf("%c %c",&a,&b);
	int t1=0,t2=0;
	for(int i=0;str[i]!=0;i++){
		if(str[i]==a||str[i]==a-32||str[i]==a+32){
			t1++;	//ͳ�Ƶ�һ���ַ����ֵĴ��� 
		}
		if(str[i]==b||str[i]==b-32||str[i]==b+32){
			t2++; 	//ͳ�Ƶڶ����ַ����ֵĴ��� 
		}
	}
	if(t1-t2<0){	//���о���ֵ���� 
		printf("%d",t2-t1);
	}else{
		printf("%d",t1-t2);
	}
	return 0;
}

