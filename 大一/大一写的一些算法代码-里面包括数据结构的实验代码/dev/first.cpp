#include <iostream>
using namespace std;
class orderlist{
	public: 
		int *a,n;
		int len_size;
		orderlist(){
			;
		}
		orderlist(int *a){
			this->a=a;
			len_size=lenth(a);		
			}
		~orderlist(){
			delete []a;
		}
		int lenth(int *a){	//��˳����Ԫ�� 
			int i;
			for(i=0;a[i]!=0;i++)
				;
			return i;
		}
		void find(){		//��һ�� 
			int i;
			cout<<"����Ҫ���ҵ�Ԫ��λ�ã�";
			cin>>i; 
			if(i<1||i>len_size)
				cout<<"������Χ"<<endl;
			else 
				cout<<a[i-1]<<endl;
		}
		void insert(){		//�ڶ��� ||������ 
			int i,x;
			cout<<"����Ҫ�����λ�ã�";
			cin>>i; 
			if(i<1||i>len_size)
				cout<<"������Χ"<<endl;
			i--;
			cout<<"�����������ݣ�";
			cin>>x;
			for(int p=len_size;p>i;p--)
				a[p]=a[p-1];
			a[i]=x;
			len_size++;
			for(int i=0;i<len_size;i++)
				cout<<a[i]<<" "; 
			cout<<endl;	
		}
		void del(){		//������ 
			int i;
			cout<<"����Ҫɾ����λ�ã�";
			cin>>i;
			if(i<1||i>len_size)
				cout<<"������Χ"<<endl;
			i--;
			int *c=new int[len_size-1];
			for(int m=i;m<len_size-1;m++)
				a[m]=a[m+1];
			
			len_size--;
			
			for(int i=0;i<len_size;i++)
				cout<<a[i]<<" "; 
			cout<<endl;
	}
	void seperate(){	//������ 
		int j=0,k=0;
		int *b=new int[len_size];
		int *c=new int[len_size];
		for(int i=0;i<len_size;i++)
			if(is_odd_number(a[i]))
			{
					b[j]=a[i];
					j++;
			}
			else
			{
				c[k]=a[i];		
				k++;
			}
		cout<<"ԭ˳���";
		for(int i=0;i<len_size;i++)
			cout<<a[i]<<" ";
		cout<<endl<<"����˳���";
		for(int i=0;i<j;i++)
			cout<<b[i]<<" ";
		cout<<endl<<"ż��˳���";
		for(int i=0;i<k;i++)
			cout<<c[i]<<" ";
		cout<<endl; 
	}
	void common_elements(int *a,int *b){//������ 
		int* c=new int[100];
		int j=0;
		for(int i=0;i<lenth(a);i++)
			for(int m=0;m<lenth(b);m++)
				if(a[i]==b[m]){
					c[j]=a[i];
					j++;
				}
		cout<<"�����˳���Ĺ���Ԫ�غ󣬷������˳����Ԫ��Ϊ��"<<endl;
		for(int i=0;i<j;i++)
			cout<<c[i]<<" ";
		cout<<endl;
	}
	delete_same(){			//������ 
		int* list=new int[100];
		int j=0; 
		for(int i=0;i<len_size;i++)
			if(a[i]!=a[i+1]){
				list[j]=a[i];
				j++;
			}
		
		a=list;
		len_size=lenth(a);
		cout<<"ɾ���ظ�Ԫ�غ�,˳���Ԫ��Ϊ��"<<endl;
		for(int i=0;i<len_size;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}
	int is_odd_number(int x){
		if(x%2==0)
			return 0;
		else
			return 1;
	}
	
};
int main(int argc, char** argv) {
	int list1[100]={1,2,3,4,5,6,7,8,9,10,11,12};
	int list3[100]={1,2,3,4,5,6,7,8,9,10,20,30,40,50,60};
	int list4[100]={1,3,6,10,15,16,17,18,19,20};
	int list5[100]={1,2,3,4,5,6,7,8,9,10,18,20,30};
	int list6[100]={1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,9};
	orderlist array1(list1);
	array1.find();
	array1.insert();
	array1.del();
	orderlist array2(list3);
	array2.seperate();
	orderlist array3;
	array3.common_elements(list4,list5);
	orderlist array4(list6);
	array4.delete_same();
}
