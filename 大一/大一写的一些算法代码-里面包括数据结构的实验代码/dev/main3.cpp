#include <iostream>
#include "BinaryTree.h" 
#include "OrderBinaryTree.h"
using namespace std;
int main(int argc, char** argv) {
	int a[100]={1,2,8,0,0,9,0,0,3,4,5,0,0,6,0,0,7};
	OrderBinaryTree obt(a);
//	OrderBinaryTree obt(a);			ͨ��˳��洢 
//	BinaryTree bt(obt);	
//	BinaryTree bt(obt);
	BinaryTree bt1(a);
	BinaryTree bt(bt1);				//���ƹ��캯�� 
	bt.swap_child(bt.root);
	cout<<"ͨ��������"<<endl; 
	cout<<"ǰ������Ϊ��";
	bt.pre_find(bt.root);
	cout<<endl<<"��������Ϊ��";
	bt.mid_find(bt.root);
	cout<<endl<<"��������Ϊ��";
	bt.back_find(bt.root); 
	cout<<endl<<"��������Ϊ��";
	bt.layer_find(); 
	int x1,x2;
	cout<<endl<<"�������Ϊ��"<<endl;
	bt.mid_output(bt.root,1);
	bt.get_attribute(); 
	cout<<"������Ԫ�أ�";
	cin>>x1;
	bt.find_node(bt.root,x1);
	int layer=0;
	cout<<"������Ԫ�أ�";
	cin>>x2;
	bt.get_layer(bt.root,x2,0,layer);
	if(layer==0){
		cout<<"��㲻���ڣ�"<<endl;
	}
	else{
		cout<<"�ý��Ĳ��Ϊ��"<<layer<<endl;
	}
	cout<<"��Ҷ�ӽ���·��Ϊ��"<<endl;
	bt.Print_Path(bt.root,0); 
	bt.closest_path(); 
	return 0;
}
