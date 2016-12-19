#include<iostream>
#include<stdio.h>
#include<math.h>
#include<complex.h>

using namespace std;

int main(){
    complex<double> cp(1.1,1.2);
    cp *=2;
    complex<double> test(1.1,1.2);
    cp += test;
    cp = exp(complex<double> (0.0,2*3.14));
    cout<<cp.real()<<"  "<<cp.imag()<<endl;
    return 1;

}
