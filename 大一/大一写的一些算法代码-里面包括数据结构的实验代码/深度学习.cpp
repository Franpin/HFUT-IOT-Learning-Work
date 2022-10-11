#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
class Linear{
	public:
		vector<vector<double> > w1,w2,b1,b2,x,y,y_pred,A1,A2,h_relu;
		Linear(vector<vector<double> > x,vector<vector<double> > y,int output_size){
			this->x=x;
			this->y=y; 
			vector<vector<double> > w1(20,vector<double>(x.size()));
			this->w1=w1;
			vector<vector<double> >b1(20,vector<double>(x[0].size()));
			this->b1=b1;
			vector<vector<double> >w2(output_size,20);
			this->w2=w2;
			vector<vector<double> >b2(output_size,vector<double>(x[0].size()));
			this->b2=b2;
		}
		vector<vector<double> > dot(vector<vector<double> > v1,vector<vector<double> > v2){
			vector<vector<double> > v3(v1.size(),vector<double>(v2[0].size()));
			double s=0.00000;
			for(int h=0;h<v2[0].size();h++){
				for(int k=0;k<v1.size();k++){
					for(int j=0;j<v2.size();j++){
						s+=v1[k][j]*v2[j][h];
					}
					v3[k][h]=s;
					s=0.00000;
				}
			}
			return v3;
		}
		vector<vector<double> >Relu(vector<vector<double> > v){
			vector<vector<double> > v3(v.size(),vector<double>(v[0].size()));
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					if(v[i][j]<0){
						v3[i][j]=0;
					}
					else{
						v3[i][j]=v[i][j];
					}
				}
			}
			return v3;
		}
		vector<vector<double> > add(vector<vector<double> > v1,vector<vector<double> > v2){
			vector<vector<double> > v3(v1.size(),vector<double>(v1[0].size()));
			for(int i=0;i<v1.size();i++){
				for(int j=0;j<v1[0].size();j++){
					v3[i][j]=v1[i][j]+v2[i][j];
				}
			}
			return v3;	
		}
		vector<vector<double> > subtract(vector<vector<double> > v1,vector<vector<double> > v2){
			vector<vector<double> > v3(v1.size(),vector<double>(v1[0].size()));
			for(int i=0;i<v1.size();i++){
				for(int j=0;j<v1[0].size();j++){
					v3[i][j]=v1[i][j]-v2[i][j];
				}
			}
			return v3;	
		}
		vector<vector<double> > softmax(vector<vector<double> > v){
			vector<vector<double> > v3(v.size(),vector<double>(v[0].size()));
			vector<vector<double> > v4(1,vector<double>(v[0].size()));
			double max,max_idx;
			for(int j=0;j<v[0].size();j++){
				for(int i=0;i<v[0].size();i++){
					v3[i][j]=exp(v[i][j]);
				}
			}
			for(int j=0;j<v3[0].size();j++){
				max=v3[0][j];
				max_idx=0;
				for(int i=1;i<v3[0].size();i++){
					if(v3[i][j]>max){
						max=v3[i][j];
						max_idx=i;
					}
				}
				v4[0][j]=max_idx;
			}
			return v4;
		}
		vector<vector<double> >multiply(vector<vector<double> > v1,vector<vector<double> > v2){
			vector<vector<double> > v3(v1.size(),vector<double>(v1[0].size()));
			for(int i=0;i<v1.size();i++){
				for(int j=0;j<v1[0].size();j++){
					v3[i][j]=v1[i][j]*v2[i][j];
				}
			}		
		}
		vector<vector<double> >mult_num(vector<vector<double> > v,double num){
			vector<vector<double> > v3(v.size(),vector<double>(v[0].size()));
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					v3[i][j]=v[i][j]*num;
				}
			}
			return v3;
		}
		vector<vector<double> >Exp(vector<vector<double> > v){
			vector<vector<double> > v3(v.size(),vector<double>(v[0].size()));
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					v3[i][j]=exp(v[i][j]);
				}
			}
			return v3;
		}
		vector<vector<double> >Log(vector<vector<double> > v){
			vector<vector<double> > v3(v.size(),vector<double>(v[0].size()));
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					v3[i][j]=log(v[i][j]);
				}
			}
			return v3;
		}
		vector<vector<double> >division(vector<vector<double> > v,double num){
			vector<vector<double> > v3(v.size(),vector<double>(v[0].size()));
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					v3[i][j]=v[i][j]/num;
				}
			}
			return v3;
		}
		double sum(vector<vector<double> > v){
			double s=0.00000000;
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					s+=v[i][j];
				}
			}
			return s;
		}
		vector<vector<double> > T(vector<vector<double> > v){
			vector<vector<double> > v3(v[0].size(),v.size());
			for(int i=0;i<v.size();i++){
				for(int j=0;j<v[0].size();j++){
					v3[j][i]=v[i][j];
				}
			}
			return v3;
		}
		void forward(){
			A1=add(dot(w1,x),b1);
			h_relu=Relu(A1);
			A2=add(dot(w2,h_relu),b2); 
			y_pred=Exp(A2);
			double s=sum(y_pred);
			y_pred=division(y_pred,s);
			double loss=sum(multiply(y,Log(y_pred)));
		}
		void optimization(double alpha){
			vector<vector<double> > dA2=subtract(y_pred,y);
			vector<vector<double> >	dw2=dot(dA2,T(A1));
			vector<vector<double> >	db2=dA2;
			vector<vector<double> >	dh_relu=dot(T(w2),dA2);
			vector<vector<double> >	dA1=dh_relu;
			for(int i=0;i<A1.size();i++){
				for(int j=0;j<A1[0].size();j++){
					if(A1[i][j]<0){
						dA1[i][j]=0;
					}
				}
			}
			vector<vector<double> > dw1=dot(dA1,T(x));
			vector<vector<double> >	db1=dA1;
			w1=subtract(w1,mult_num(dw1,alpha));
			b1=subtract(b1,mult_num(db1,alpha));
			w2=subtract(w2,mult_num(dw2,alpha));
			b2=subtract(b2,mult_num(db2,alpha));
		}	
};
int main(){
	int a[]={1,1,1};
	int b[]={2,2,2};
	vector<int> vec1{1,2,3};
	vector<int> vec2(3,2);
	vector<vector<int> >v1(3,vec1);
	vector<vector<int> >v2(5,vec2);
	Linear lin;
	vector<vector<int> > v3=lin.dot(v1,v2);
	for(int i=0;i<v3.size();i++){
		for(int j=0;j<v3[0].size();j++){
			cout<<v3[i][j]<<" ";
		}
		cout<<endl;
	}
	
}
