#include<iostream>

using namespace std;


void counting_sort(int arr[],int n){
    int out[n];
    int maxi = 0;
    for(int i = 0;i < n;i++){
       if(maxi < arr[i]){
            maxi = arr[i];
       }
    }

    int b[maxi];
    for(int i = 0; i<maxi; i++){
        b[i] = 0;
    }

    for(int i=0;i<n;i++){
        b[arr[i]]++;
    }

    for(int i=1;i<maxi;i++){
        b[i]=b[i]+b[i-1];
    }

    for(int i=n-1;i>=0;i--){
        out[b[arr[i]]-1]=arr[i];
        b[arr[i]]--;
    }

    for(int i=0;i<n;i++){
        arr[i]=out[i];
    }


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
	//int RANGE=9;

	print(arr,n);

	counting_sort(arr,n);

    print(arr,n);

	return 0;
}
