#include <iostream>
#include "BinaryTree.h" 
#include "OrderBinaryTree.h"
using namespace std;
int main(int argc, char** argv) {
	int a[100]={1,2,8,0,0,9,0,0,3,4,5,0,0,6,0,0,7};
	OrderBinaryTree obt(a);
//	OrderBinaryTree obt(a);			通过顺序存储 
//	BinaryTree bt(obt);	
//	BinaryTree bt(obt);
	BinaryTree bt1(a);
	BinaryTree bt(bt1);				//复制构造函数 
	bt.swap_child(bt.root);
	cout<<"通过交换后："<<endl; 
	cout<<"前序序列为：";
	bt.pre_find(bt.root);
	cout<<endl<<"中序序列为：";
	bt.mid_find(bt.root);
	cout<<endl<<"后序序列为：";
	bt.back_find(bt.root); 
	cout<<endl<<"层序序列为：";
	bt.layer_find(); 
	int x1,x2;
	cout<<endl<<"中序输出为："<<endl;
	bt.mid_output(bt.root,1);
	bt.get_attribute(); 
	cout<<"请输入元素：";
	cin>>x1;
	bt.find_node(bt.root,x1);
	int layer=0;
	cout<<"请输入元素：";
	cin>>x2;
	bt.get_layer(bt.root,x2,0,layer);
	if(layer==0){
		cout<<"结点不存在！"<<endl;
	}
	else{
		cout<<"该结点的层次为："<<layer<<endl;
	}
	cout<<"各叶子结点的路径为："<<endl;
	bt.Print_Path(bt.root,0); 
	bt.closest_path(); 
	return 0;
}
