#include<stdio.h>
int main(){
	char str[50];
	scanf("%s",str);
	for(int i=0;str[i]!=0;i++){
		if(str[i]<='Z'&&str[i]>='A'){
			if(str[i]+5>'Z'){//如果超出了大写字母的范围 
				str[i]=char(str[i]+5-26);//加上5减26表示超出Z后从A开始 
			}else{
				str[i]=char(str[i]+5);//没有超出范围则直接加上5 
			}	
		}
		if(str[i]<='z'&&str[i]>='a'){
			if(str[i]+5>'z'){//如果超出了小写字母的范围 
				str[i]=char(str[i]+5-26);// 加上5减26表示超出z后从a开始
			}else{
				str[i]=char(str[i]+5);//没有超出范围则直接加上5
			}
		}
	}
	printf("%s",str);
	return 0;
}
