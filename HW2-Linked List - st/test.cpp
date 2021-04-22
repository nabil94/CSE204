#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

void foo(){
    int a = 2;
    float b = 2.5;
    bool c = false;
    if(b > a){
        c = true;
    }
    cout<<c<<endl;
}


int main(){
    foo();
    //cout<<a<<endl;
    return 0;
}
