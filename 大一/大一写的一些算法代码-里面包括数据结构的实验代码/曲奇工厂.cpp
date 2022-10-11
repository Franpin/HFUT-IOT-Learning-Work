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
    }//读入数据
    int k=C%S==0?C/S:C/S+1;//k的值为不买任意工厂花费的最少时间
    dp[0]=0;//dp数组dp[i]的意义为前i分钟最大能制造的曲奇饼数量
    for(int i=1;i<=k;i++){
        dp[i]=i*S;//初始化dp数组，不买工厂每分钟制造S个
    }
    sort(w+1,w+N+1);
    do
    {
        for(int i=1;i<=N;i++){
            int index=0;//index的意义为，最早在第index分钟能买的起工厂i
            for(int j=1;j<=k;j++){
                if(dp[j]>=w[i].A){
                    if(index==0){
                        index=j;//赋值得到index
                        
                    }
                    else{
                        dp[j]=max(dp[j],dp[j]-w[i].A+(j-index)*w[i].B);
                        //该动态转移方程的意义为 ：
                        // 1.若第j分钟买工厂i,则第j分钟的曲奇饼数量为 dp[j]-A[i]+(j-index)*B[i]
                        // 2.若第j分钟不买工厂i,则第j分钟的曲奇饼数量不变，仍然为dp[j]；
                        //因此转移方程为 dp[j]=max(dp[j],dp[j]-A[i]+(j-index)*B[i]) 
                    }          
                }
                //cout<<dp[j]<<endl;  
            }   
        }
        for(int i=1;i<=k;i++){
        
            if(dp[i]>=C){
                if(minx>i) minx=i;
                for(int j=1;j<=k;j++){
                    dp[j]=j*S;//初始化dp数组，不买工厂每分钟制造S个
                }
                break;//输出最小的时间
            }
        }
    }while(next_permutation(w+1,w+N+1));
    cout<<minx<<endl;
    
   
    return 0;
}

