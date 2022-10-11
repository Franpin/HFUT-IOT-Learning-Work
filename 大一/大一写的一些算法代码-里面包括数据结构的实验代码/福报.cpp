#include<iostream>
using namespace std; 
struct Person{
	int idx;
	int level;
	int time;
	int need_time; 
};
int main(){
	int E;
	cin>>E;
	Person* p=new Person[E];
	for(int i=0;i<E;i++){
		cin>>p[i].idx>>p[i].level>>p[i].time;
	}
	
	for(int i=0;i<E;i++){
		p[i].need_time=0;
	}
	for(int i=0;i<E;i++){
		int index=i;
		while(p[index].idx!=-1){
			index=p[index].idx-1;
			p[index].need_time+=p[i].time;
		}	
	} 
	for(int i=0;i<E;i++){
		cout<<p[i].need_time<<endl;
		
	}
}
