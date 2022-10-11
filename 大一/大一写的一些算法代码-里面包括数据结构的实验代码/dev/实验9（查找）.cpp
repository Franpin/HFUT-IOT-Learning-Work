#include<iostream>
using namespace std;
int data[]={1,2,3,4,5,6,7,8,9,10,11,12,13,17,18,19,20,24,25,26,30,35,40,45,50,100};
void find(int x,int low,int hign){
	int mid=(low+hign)/2;
	cout<<"所比较元素的下标为："<<mid<<endl;
	if(x==data[mid]){
		cout<<"二分法查找成功！"<<endl;
		return ;
	}
	if(low==hign){
		cout<<"二分法查找失败！"<<endl;
		return ;
	}
	if(x<data[mid]){
		find(x,low,mid-1);
	}
	if(x>data[mid]){
		find(x,mid+1,hign);
	}
}
struct node{
	int data;
	node* lchild;
	node* rchild;
};
class Binary_Search_Tree{
	public:
		Binary_Search_Tree(int *a);
		Binary_Search_Tree(int *b,int p);
		void insert_element(int x);
		void find_element(node* ptr,int x); 
		void delete_element(node* &ptr,node* pre,int x);
		void Balance_create(node* &ptr,int low,int hign);
		void mid_find(node *ptr);
		int *a; 
		node *root;
		node* mid_pre;
		node* pre_mid_pre; 
}; 
Binary_Search_Tree::Binary_Search_Tree(int* a){
	this->a=a;
	node* r_node=new node;
	r_node->data=a[0]; 
	root=r_node;
	root->lchild=NULL;
	root->rchild=NULL;
	for(int i=1;a[i]!=0;i++){
		insert_element(a[i]);
	}
}
Binary_Search_Tree::Binary_Search_Tree(int *b,int p){
	a=b;
	root=NULL;
	Balance_create(root,0,25);
}
void Binary_Search_Tree::Balance_create(node* &ptr,int low,int hign){
	if(low<=hign){
		int mid=(low+hign)/2;
		node* new_node=new node;
		new_node->data=a[mid];
		new_node->lchild=NULL;
		new_node->rchild=NULL;
		ptr=new_node;
		Balance_create(ptr->lchild,low,mid-1);
		Balance_create(ptr->rchild,mid+1,hign); 
	}
}
void Binary_Search_Tree::mid_find(node *ptr){
	if(ptr!=NULL){
		mid_find(ptr->lchild);
		cout<<ptr->data<<" ";
		mid_find(ptr->rchild); 
	}
}
void Binary_Search_Tree::insert_element(int x){
		node* ptr=root;
		node* new_node=new node;
		new_node->data=x;
		new_node->lchild=NULL;
		new_node->rchild=NULL;
		while(1){
			if(new_node->data<ptr->data){
				if(ptr->lchild==NULL){
					ptr->lchild=new_node;
					return ;
				} 
				ptr=ptr->lchild;
				continue ;
			}
			if(new_node->data>=ptr->data){
				if(ptr->rchild==NULL){
					ptr->rchild=new_node;
					return ;
				} 
				ptr=ptr->rchild;
				continue ;
			}
		}
}
void Binary_Search_Tree::find_element(node* ptr,int x){
	if(ptr!=NULL){
		if(x==ptr->data){
			return ;
		}
		if(x>ptr->data){
			find_element(ptr->rchild,x);
		}
		if(x<ptr->data){
			find_element(ptr->lchild,x);
		}
	}
	if(ptr==NULL){
		cout<<"查找"<<x<<"失败！"<<endl;
	}		
}
void Binary_Search_Tree::delete_element(node* &ptr,node *pre,int x){
	if(ptr!=NULL){
		delete_element(ptr->lchild,ptr,x);
		if(ptr->data==x){
			if(ptr->lchild==NULL){
				ptr=ptr->rchild;
				return ;
			} 
			if(ptr->rchild==NULL){
				ptr=ptr->lchild;
				return ;
			}
			if(pre_mid_pre->lchild==mid_pre){
				pre_mid_pre->lchild=mid_pre->lchild;
			}
			if(pre_mid_pre->rchild==mid_pre){
				pre_mid_pre->rchild=mid_pre->lchild;
			}
			node* lchild=ptr->lchild;
			node* rchild=ptr->rchild;
			ptr=mid_pre;
			mid_pre->lchild=lchild;
			mid_pre->rchild=rchild;
		}
		pre_mid_pre=pre;
		mid_pre=ptr;
		pre_mid_pre=pre;
		delete_element(ptr->rchild,ptr,x);
	}
} 

int main(){
	find(100,0,25);
	int a[100]={100,150,120,50,70,1,80,170,180,160,110,30,40,35,175};
	int b[100]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
	Binary_Search_Tree bst(a);
	bst.find_element(bst.root,66);
	bst.delete_element(bst.root,NULL,50);
	cout<<"删除元素50后，中序序列为："<<endl;
	bst.mid_find(bst.root); 
	Binary_Search_Tree bst1(b,0);
	cout<<endl<<"构建的平衡二叉树中序序列为："<<endl;
	bst.mid_find(bst1.root);
	return 0;
}

