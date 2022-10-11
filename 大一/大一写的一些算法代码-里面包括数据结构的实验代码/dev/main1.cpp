#include <iostream>
#include"stack.cpp"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	stack<int> s;
	s.push(2);
	cout<<s.pop()<<endl;
	return 0;
}
