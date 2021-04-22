#include <iostream>
using namespace std;

void countingSort(int arr[],int n,int RANGE){
    int count[RANGE];
    for(int i = 0;i < RANGE;i++){
        count[i] = 0;
    }
    int i;
    int out[n];


    for(i=0;i<n;i++){
        count[arr[i]]++;
    }


    for(i=1;i<RANGE;i++){
        count[i]+=count[i-1];
    }




    for(i=n-1;i>=0;i--){
        out[count[arr[i]]-1]=arr[i];
        --count[arr[i]];
    }

    for(i=0;i<n;i++)
    arr[i]=out[i];



}
void print(int arr[],int n){
    cout<<"array : ";
    for(int i=0;i<n;i++)
    cout<<arr[i]<<' ';
    cout<<endl;
}

int main() {
	// your code goes here
	int n;
	cin>>n;
	int a[n];
	for(int i = 0; i < n; i++){
        cin>>a[i];
	}

	int m = 0;
	for(int i = 0;i < n; i++){
        if(a[i]>m){
            m = a[i];
        }
	}
	cout<<m<<endl;

	print(a,n);

	countingSort(a,n,m+1);

    print(a,n);

	return 0;
}
