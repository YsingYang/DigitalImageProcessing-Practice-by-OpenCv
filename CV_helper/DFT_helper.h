#include<stdio.h>
#include<iostream>
#include<vector>
#include<complex.h>
#include<bitset>
using namespace std;

vector<complex<double> > Rader(vector<complex<double> >&img){
    int flip(int num,int bit_count);
    int size = img.size();
    int bit_count=0;
    cout<<bit_count<<endl;
    while((size>>bit_count)!=0){
        ++bit_count;
    } cout<<bit_count<<endl;
    vector<complex<double>> res(size);
    for(int i=0;i<img.size();++i){;;
        res[flip(i,bit_count-1)] = img[i];
        cout<<i<<endl;
    }
    return res;
}

int flip(int num,int bit_count){
    int res=0;
    while(bit_count>0){
        res |= (num&1);
        res <<=1;
        num>>=1;
        --bit_count;
    }
    return res;
}
