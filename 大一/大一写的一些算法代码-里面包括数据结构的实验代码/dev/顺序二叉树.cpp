#include<iostream>
using namespace std;
char Tree[100]={0};
int j=0;
void create_tree(int i,char* a){
	if(a[j]!='#'){
		Tree[i]=a[j];
		j++;
		create_tree(2*i,a);
		create_tree(2*i+1,a);
	}
	else{
		j++;
	}	
}
void back_find(int i){
	if(Tree[i]!=0){
		back_find(2*i);
		back_find(2*i+1);
		cout<<Tree[i]<<" ";
	}
}
void find_one(int i,int &num){
	if(Tree[i]!=0){
		if(Tree[2*i]==0&&Tree[2*i+1]!=0||Tree[2*i]!=0&&Tree[2*i+1]==0){
			cout<<Tree[i]<<" ";
			num++;
		}
		find_one(2*i,num);
		find_one(2*i+1,num);
	}
} 

int get_height(int i){
	if(Tree[i]!=0){
		int a=get_height(2*i);
		int b=get_height(2*i+1);
		if(a>b){
			return a+1;
		}
		else{
			return b+1;			
		}
	}
	return 0;
}
void output_path(int i,char* path,int j){
	if(Tree[i]!=0){
		path[j]=Tree[i];
		output_path(2*i,path,j+1);
		output_path(2*i+1,path,j+1);
		if(Tree[2*i]==0&&Tree[2*i+1]==0){
			for(int k=j;k>=0;k--){
				cout<<path[k];
			}
			cout<<endl;
		}
	}
}
void max_path(int i,char* path,int j,int height){
	if(Tree[i]!=0){
		path[j]=Tree[i];
		max_path(2*i,path,j+1,height);
		max_path(2*i+1,path,j+1,height);
		if(j==height-1){
			cout<<"最长路径为："<<endl;
			for(int k=j;k>=0;k--){
				cout<<path[k];
			}
			cout<<endl;
		}
	}
} 
int main(){
	char a[]="ABC#D##E#F##GH##I##";
	create_tree(1,a);
//	cout<<"后序序列为："; 
//	back_find(1);
//	int num=0; 
//	cout<<endl<<"度为一的结点为："; 
//	find_one(1,num);
//	cout<<endl<<"数量为："<<num<<endl;
	int height=get_height(1);
	cout<<"树的深度为："<<height<<endl;
	char path1[100]={0};
	char path2[100]={0};
	cout<<"各个叶子结点到根节点的路径为："<<endl;
	output_path(1,path1,0);
	max_path(1,path2,0,height); 
	cout<<"最长路径长度为："<<height<<endl; 
}
