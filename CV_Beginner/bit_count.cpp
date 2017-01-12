#include<stdio.h>
#include<iostream>
#include"CV_helper/DFT_helper.h"

using namespace std;

int main(){
    vector<complex<double> > comp(8),res(8);
    int count=0;
    while(count<8){
        comp[count] = complex<double> (0.0,count);
        ++count;
    }
    res = Rader(comp);
    cout<<"执行"<<endl;
    for(auto i:comp){
        cout<<i<<"  ";
    }
    cout<<endl;
    for(auto i :res){
        cout<<i<<"  ";
    }
}
