#include "map.h"
#include"iostream"
using namespace std;
drawmap::drawmap(){
	x=0;
}
void drawmap::draw(){
	for(int i=0;i<9;i++){
	for(int m=0;m<9;m++)
	switch(map[x][i][m]){
		case 1:
		cout<<"¡ö";
		break;
		case 0:
		cout<<" "; 
		break;
		case 2:
		cout<<"¡ñ";
		break;
	}
	cout<<endl;	
}
}
