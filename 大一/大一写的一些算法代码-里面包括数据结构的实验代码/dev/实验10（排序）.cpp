#include<iostream>
using namespace std;
int *a;
int partition(int low,int hign){
	a[0]=a[low];
	while(low<hign){
		while(low<hign&&a[hign]>=a[0]){
			hign--;
		}
		a[low]=a[hign];
		while(low<hign&&a[low]<=a[0]){
			low++;
		}
		a[hign]=a[low];
	}
	a[hign]=a[0];
	return hign;
}
void quick_sort(int low,int hign){
	if(low<hign){
		int mid=partition(low,hign);
		quick_sort(low,mid-1);
		quick_sort(mid+1,hign); 
	}
}
void classify(int *data){
	int mid[100];
	int left[100];
	int right[100];
	int x=0,y=0,z=0;
	for(int i=0;data[i]!=0;i++){
		switch(data[i]%3){
			case 0:
				left[x]=data[i];
				x++;
				break;
			case 1:
				mid[y]=data[i];
				y++;
				break;
			case 2:
				right[z]=data[i];
				z++;
				break;	
		}
	}
	int i,j,k;
	for(i=0;i<x;i++){
		data[i]=left[i];
	}
	for(j=0;j<y;j++){
		data[i+j]=mid[j];
	}
	for(k=0;k<z;k++){
		data[i+j+k]=right[k];
	}
	for(int p=0;p<i+j+k;p++){
		cout<<data[p]<<" ";
	}
}
void swap(int &a,int &b){
	int t=a;
	a=b;
	b=t;
}
void shell_sort(int len){
	int d=len;
	while(d!=1){
		d=d/2;
		for(int i=0;i<d;i++){
			for(int j=i+d;j<len;j+=d){
				for(int k=j;k>i;k-=d){
					if(a[k]<a[k-d]){
						swap(a[k],a[k-d]);
					}
				}
			}
			
		}	
	}	
} 
void sift(int k,int n,int *A){
	int x=A[k];
	while(k<=n/2){
		int j=2*k;

		if(j+1<=n){
			if(A[j]<A[j+1]){
				j=j+1;
			}
		}

		if(A[j]<=x){
			break;
		}
		else{
			A[k]=A[j];
			k=j; 
		}
	}
		A[k]=x;
}
void heap_sort(int n,int *A){
	for(int i=n/2;i>=1;i--){
		sift(i,n,A); 
	}
	for(int i=n;i>=2;i--){
		swap(A[1],A[i]);
		sift(1,i-1,A);
		cout<<"µÚ"<<n-i+1<<"ÌËÅÅÐò:";
		for(int i=1;i<26;i++){
			cout<<A[i]<<" "; 
		}
		cout<<endl;
	}
}
void Merge(int *A,int low,int mid,int hign,int n){
	int a[100];
	int i=low,j=mid+1,k=0;
	if(hign>=n){
		hign=n-1;
	}
	if(mid>=n){
		return;	
	}
	while(i<=mid&&j<=hign){
		if(A[i]<A[j]){
			a[k]=A[i];
			i++;
		}
		else{
			a[k]=A[j];
			j++;
		}
		k++;		
	}
	while(i<=mid){
		a[k]=A[i];
		k++;
		i++;
	}
	while(j<=hign){
		a[k]=A[j];
		k++;
		j++;
	}

	for(int h=0;h<hign-low+1;h++){
		A[low+h]=a[h];

	}

}
void merge_sort(int n,int *A){
	int len=1;
	while(len<n-1){
		for(int i=1;i<n;i+=2*len){
			Merge(A,i,i+len-1,i+2*len-1,n);
		}

		len=len*2;	
	}
} 
int main(){
	int data[27]={11,12,13,14,15,1,2,3,4,5,6, 10, 16, 1,22,23,2,17,18,19,20,24, 7,8,9,25,26};
	int A[26]={0,106,213,325,446,579,654,721,870,917,510,21,632,73,14,815,316,412,18,619,720,21,808,923,25,26};
	a=A;
	cout<<"¿ìËÙÅÅÐò£º";
	quick_sort(0,27); 
	for(int i=1;i<26;i++){
		cout<<A[i]<<" "; 
	}
	cout<<endl<<"Ï£¶ûÅÅÐò£º";
	shell_sort(27);
	for(int i=1;i<26;i++){
		cout<<A[i]<<" "; 
	}
	cout<<endl<<"¶ÑÅÅÐò£º"<<endl;
	heap_sort(25,A);
	cout<<"¹é²¢ÅÅÐò£º"<<endl;
	merge_sort(26,A); 
	for(int i=1;i<26;i++){
		cout<<A[i]<<" "; 
	}
	cout<<endl<<"·ÖÀà£º"<<endl; 
	classify(data);
	
}
