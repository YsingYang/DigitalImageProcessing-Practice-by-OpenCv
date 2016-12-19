#include<stdio.h>
#include<iostream>
#include<complex.h>
#include<vector>
using namespace std;

int main(){
    const float PI = 3.1415;
    vector<int> ori={2,1,1,1};
    vector<complex<double > > res(ori.size());
    for(int i=0;i<ori.size();++i){
        complex<double> temp;
        for(int u=0;u<ori.size();++u){
            double part = u * i *1.0/ori.size();
            complex<double> e = exp(complex<double> (0.0,-2*PI*part));
            temp += (ori[u]*1.0 *e);
        }
        res[i] = temp;
    }
    for(auto i:res){
        cout<<i<<endl;
    }
    return 1;
}

