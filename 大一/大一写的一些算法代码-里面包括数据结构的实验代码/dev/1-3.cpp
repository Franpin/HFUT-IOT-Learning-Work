#include<stdio.h>
int main(){
	char str[50];
	scanf("%s",str);
	for(int i=0;str[i]!=0;i++){
		if(str[i]<='Z'&&str[i]>='A'){
			if(str[i]+5>'Z'){//��������˴�д��ĸ�ķ�Χ 
				str[i]=char(str[i]+5-26);//����5��26��ʾ����Z���A��ʼ 
			}else{
				str[i]=char(str[i]+5);//û�г�����Χ��ֱ�Ӽ���5 
			}	
		}
		if(str[i]<='z'&&str[i]>='a'){
			if(str[i]+5>'z'){//���������Сд��ĸ�ķ�Χ 
				str[i]=char(str[i]+5-26);// ����5��26��ʾ����z���a��ʼ
			}else{
				str[i]=char(str[i]+5);//û�г�����Χ��ֱ�Ӽ���5
			}
		}
	}
	printf("%s",str);
	return 0;
}
