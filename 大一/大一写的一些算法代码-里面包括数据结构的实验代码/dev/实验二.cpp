#include<iostream>
using namespace std;
typedef int elementype;
struct node{
	elementype data;
	node *next;
};
class List{
	public:
		node *head;	
		int len_size;
	List(int a[]){
		head=new node;//带有头节点 
		head->next=NULL;
		tail_create(a);
		len_size=get_lenth();
	}
	List(List &list){//复制构造函数 
		head=new node;
		head->next=NULL;
		node* ptr=list.head->next;
		node* ptr1=head;
		while(ptr){
			node *new_node=new node;
			new_node->data=ptr->data;
			new_node->next=NULL;
			ptr1->next=new_node;
			ptr=ptr->next;
			ptr1=ptr1->next;
		}		
	} 
	~List(){
		node* ptr=head;
		while(ptr){
			delete []ptr;
			ptr=ptr->next;	
	}
	}						//静态成员函数 
	static node* find_common_element(node *List1,node *List2);
	void find_list(){		//遍历链表 
		node *ptr=head->next;
		while(ptr){
			cout<<ptr->data<<" ";
			ptr=ptr->next;
		}
		cout<<endl;
	} 
	void tail_create(int *a){			//尾插法 
		 node* tail=NULL;
		 node* ptr=head;
		 for(int i=0;a[i]!=0;i++)
		 {
		 	tail=new node;
		 	tail->data=a[i];
		 	tail->next=NULL;
		 	ptr->next=tail;
		 	ptr=tail;
		 }
	} 
	void head_create(int a[]){		//头插法 
		for(int i=0;a[i]!=0;i++){
			node *ptr=new node;
			ptr->data=a[i];
			ptr->next=head->next;
			head->next=ptr;
	}
	}
	int get_lenth(){
		int n=0;
		node *ptr=head->next;//因为带有头节点
		while(ptr){
			n++;
			ptr=ptr->next;	
		}
		return n; 
	}
	int get_element(){
		int m;
		cout<<"请输查找的位置："<<endl;
		cin>>m;
		node *ptr=head->next;
		int i=1;
		while(ptr){
			if(i==m){
				cout<<"查找的元素为："<<ptr->data<<endl;
				return 1;
			}	
			ptr=ptr->next;	
			i++;
		}
		cout<<"查找的位置出错！"<<endl; 
		return -1;
	}
	node *find_element(){
		int x;
		cout<<"请输入查找的元素："<<endl;
		cin>>x;
		node *ptr=head->next;
		while(ptr){
			if(ptr->data==x){
				cout<<"该元素的地址为："<<ptr<<endl; 
				return ptr;
			}
			ptr=ptr->next;	
		}
		cout<<"查找失败！"<<endl;
		return NULL;
	}
	void insert_element(){
		int x,i;
		cout<<"请输入插入的位置："<<endl;
		cin>>i; 
		cout<<"请输入插入的元素："<<endl;
		cin>>x;
		node* ptr=head; 
		if(i<1){
			cout<<"插入的位置出错！"<<endl; 
			return ;
		}
		for(int t=0;t<i-1;t++){
			ptr=ptr->next;
			if(ptr==NULL){
				cout<<"插入的位置出错"<<endl; 
				return ;
			}	
		}
		node* new_node=new node;
		new_node->data=x;
		new_node->next=ptr->next;	
		ptr->next=new_node;
		len_size++;
		cout<<"插完后链表："<<endl; 
		find_list();
	}
	void delete_element(){
		int i;
		cout<<"请输入删除的位置："<<endl;
		cin>>i;
		node* ptr=head;
		if(i<1){
			cout<<"删除序号错误!"<<endl; 
			return ;
		}
		for(int t=0;t<i-1;t++){
			ptr=ptr->next;
				if(ptr==NULL){
				cout<<"删除序号出错"<<endl; 
				return ;
		}
	}
		node *p=ptr->next;
		ptr->next= p->next;
		delete []p;
		len_size--;
		cout<<"删除后的链表："<<endl;
		find_list();
	}
	void insert_orderList(){
		int x;
		cout<<"请输入插入的元素："<<endl;
		cin>>x;
		node *ptr=head;	
		node* new_node=new node;
		new_node->data=x;
		while(ptr->next){
			if(ptr->next->data>x){
			
				new_node->next=ptr->next;	
				ptr->next=new_node;
				len_size++;
				return ;
			}
			ptr=ptr->next;
		}
		ptr->next=new_node;
		new_node->next=NULL;
		len_size++;
		cout<<"插完后链表："<<endl; 
		find_list();
	} 
	void seperate(){
		node *head1=new node,*head2=new node;
		node *ptr=head->next,*ptr1=head1,*ptr2=head2;
		while(ptr){
			if(ptr->data%2==1){
				node *new_node1=new node;
				new_node1->next=NULL;
				new_node1->data=ptr->data;
				ptr1->next=new_node1; 
				ptr1=ptr1->next;
			} 
			else{
				node *new_node2=new node;
				new_node2->next=NULL;
				new_node2->data=ptr->data;
				ptr2->next=new_node2; 
				ptr2=ptr2->next;
			}
			ptr=ptr->next;
		}
		ptr=head->next;
		ptr1=head1->next;
		ptr2=head2->next;
		cout<<"原链表为："<<endl;
		while(ptr){
			cout<<ptr->data<<" ";
			ptr=ptr->next;	
		}
		cout<<endl;
		cout<<"奇数单链表为："<<endl;
		while(ptr1){
			cout<<ptr1->data<<" ";
			ptr1=ptr1->next;
		}
		cout<<endl;
		cout<<"偶数单链表为："<<endl;
		while(ptr2){
			cout<<ptr2->data<<" ";
			ptr2=ptr2->next;
		}
		cout<<endl;	
	}

	void delete_common_element(){
		node* ptr=head->next;
		while(ptr->next){
			if(ptr->data==ptr->next->data){
				node* p=ptr->next->next;
				delete [](ptr->next);
				ptr->next=p;
			}
			else{
			ptr=ptr->next;	
			}
		}
		len_size=get_lenth();
		cout<<"删除重复元素后，单链表为："<<endl;
		find_list();
	} 
	void merge_Lists(node* List1,node *List2){
		node *ptr2=List2->next;
		node *ptr1=List1;
		while(ptr1->next&&ptr2){
			if(ptr2->data<ptr1->next->data){
			//	cout<<"ptr2->data:"<<ptr2->data<<endl;
				node *new_node=new node;
				new_node->data=ptr2->data;
				new_node->next=ptr1->next;
				ptr1->next=new_node;
				ptr2=ptr2->next;
				continue;
			}
			if(ptr2->data==ptr1->next->data){
				ptr2=ptr2->next;		
				continue;
			}
			if(ptr2->data>ptr1->next->data){
				ptr1=ptr1->next;
				if(ptr1->next==NULL&&ptr2!=NULL){
					ptr1->next=ptr2;
				break;
			} 
				continue;
			}		
		}
		delete []List2;	
		cout<<"合并后的单链表为："<<endl;
		ptr1=List1->next;
		while(ptr1){
			cout<<ptr1->data<<" ";
			ptr1=ptr1->next;
		}	
		cout<<endl;
	}
	
};
node* List::find_common_element(node *List1,node *List2){
		node *List3=new node;
		node *ptr1=List1->next;
		node *ptr2=List2->next;;
		node *ptr3=List3;
		while(ptr1&&ptr2){
			if(ptr1->data<ptr2->data){
				ptr1=ptr1->next;	
				continue;
			}
			if(ptr1->data==ptr2->data){
				node *new_node=new node;
				new_node->data=ptr1->data;
				ptr3->next=new_node;
				ptr3=ptr3->next;
				ptr1=ptr1->next;
				ptr2=ptr2->next;
				continue;
			}
			if(ptr1->data>ptr2->data) {
				ptr2=ptr2->next;
				continue;
			}
		}
		ptr3=List3->next;
		cout<<"两单链表的公共元素为："<<endl;
		while(ptr3){
			cout<<ptr3->data<<" ";
			ptr3=ptr3->next;
		}
		cout<<endl;
		return List3;
	}
int main(){
	int list1[20]={1,3,4,10,15,16,17,18,19,20};
	int list2[20]={10,20,30,40,50,60,70,80,90,100};
	int list3[20]={1,2,3,4,5,6,7,8,9,10,20,30,40,50,60};
	int list4[20]={1,3,6,10,15,16,17,18,19,20};
	int list5[20]={1,2,3,4,5,6,7,8,9,10,18,20,30};
	int list6[20]={1,1,2,2,2,3,4,5,5,5,6,6,7,7,8,8,9};
	int list7[20]={1,3,6,10,15,16,17,18,19,20};
	int list8[20]={1,2,3,4,5,6,7,8,9,10,18,20,30};
	List List1(list1);
	List1.get_element();	
	List1.find_element();
	List1.insert_element();
	List1.delete_element();
	List List2(list2);
	List2.insert_orderList();
	List List3(list3);
	List3.seperate();
	List List4(list4);
	List List5(list5);
	List::find_common_element(List4.head,List5.head);
	List1.seperate();
	List List6(list6);
	List6.delete_common_element();
	List List7(list7);
	List List8(list8);
	List8.merge_Lists(List7.head,List8.head);	
	return 0;
}
