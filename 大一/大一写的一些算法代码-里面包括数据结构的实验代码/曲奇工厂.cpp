#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
int dp[100010];
struct work{
    int A,B;
};
bool operator<(struct work temp1,struct work temp2){
    if(temp1.A==temp2.A) {
    	return temp1.B>temp2.B;
	}
    return temp1.A<temp2.A;
}
struct work w[6];
int main(){
    int N,C,S,minx=0x3f3f3f3f;
    cin>>N>>C>>S;
    for(int i=1;i<=N;i++){
        cin>>w[i].A>>w[i].B;
    }//��������
    int k=C%S==0?C/S:C/S+1;//k��ֵΪ�������⹤�����ѵ�����ʱ��
    dp[0]=0;//dp����dp[i]������Ϊǰi�����������������������
    for(int i=1;i<=k;i++){
        dp[i]=i*S;//��ʼ��dp���飬���򹤳�ÿ��������S��
    }
    sort(w+1,w+N+1);
    do
    {
        for(int i=1;i<=N;i++){
            int index=0;//index������Ϊ�������ڵ�index����������𹤳�i
            for(int j=1;j<=k;j++){
                if(dp[j]>=w[i].A){
                    if(index==0){
                        index=j;//��ֵ�õ�index
                        
                    }
                    else{
                        dp[j]=max(dp[j],dp[j]-w[i].A+(j-index)*w[i].B);
                        //�ö�̬ת�Ʒ��̵�����Ϊ ��
                        // 1.����j�����򹤳�i,���j���ӵ����������Ϊ dp[j]-A[i]+(j-index)*B[i]
                        // 2.����j���Ӳ��򹤳�i,���j���ӵ�������������䣬��ȻΪdp[j]��
                        //���ת�Ʒ���Ϊ dp[j]=max(dp[j],dp[j]-A[i]+(j-index)*B[i]) 
                    }          
                }
                //cout<<dp[j]<<endl;  
            }   
        }
        for(int i=1;i<=k;i++){
        
            if(dp[i]>=C){
                if(minx>i) minx=i;
                for(int j=1;j<=k;j++){
                    dp[j]=j*S;//��ʼ��dp���飬���򹤳�ÿ��������S��
                }
                break;//�����С��ʱ��
            }
        }
    }while(next_permutation(w+1,w+N+1));
    cout<<minx<<endl;
    
   
    return 0;
}

