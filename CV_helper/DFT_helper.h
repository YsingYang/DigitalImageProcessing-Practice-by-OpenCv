#include<stdio.h>
#include<iostream>
#include<vector>
#include<complex.h>
#include<bitset>
#include <limits.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

#define M_PI 3.1415926535897932384

int log2(int N){    /*number of bit */
  int k = N, i = 0;
  while(k) {
    k >>= 1;
    i++;
  }
  return i - 1;
}
//check是否为pow(2,X)的数
int check(int n){
  return n > 0 && (n & (n - 1)) == 0;
}

//由于蝶型算法需要逆转数组中的次序,逆转的方法为调换index的bit,如对于4个bit表示的1100逆转后结果为0011
int reverse(int N, int n){
  int j, p = 0;
  for(j = 1; j <= log2(N); j++) {
    if(n & (1 << (log2(N) - j)))
      p |= 1 << (j - 1);
  }
  return p;
}
//使用逆转的数组下表重组序列(该数组序列其实就是像素值的序列)
void ordina(vector<complex<double>> & f1, int N){
  vector<complex<double> >f2(N);
  for(int i = 0; i < N; i++)
    f2[i] = f1[reverse(N, i)];
  for(int j = 0; j < N; j++)
    f1[j] = f2[j];
}

//进行快速傅里叶变换,这里旋转因子值分配了N/2个,因为快速傅里叶变换并不需要算出所有的旋转因子,
//这里用了网上给的优化方法,通过极坐标计算旋转因子1,后面的旋转因为可以有幂i得到,然后就可以通过快速傅里叶变换的式子得到F[I]结果
void transform(vector<complex<double>>& f, int N){
  ordina(f, N);    //first: reverse order
  complex<double> *W;
  W = (complex<double> *)malloc(N / 2 * sizeof(complex<double>));
  W[1] = polar(1., -2. * M_PI / N);
  W[0] = 1;
  for(int i = 2; i < N / 2; i++)
    W[i] = pow(W[1], i);
  int n = 1;
  int a = N / 2;
  for(int j = 0; j < log2(N); j++) {
    for(int i = 0; i < N; i++) {
      if(!(i & n)) {//避免重复运算
        complex<double> temp = f[i];
        complex<double> Temp = W[(i * a) % (n * a)] * f[i + n];
        f[i] = temp + Temp;
        f[i + n] = temp - Temp;
      }
    }
    n *= 2;
    a = a / 2;
  }
}

void FFT(vector<complex<double>> &f, int N)
{
  transform(f, N);
}


void out_put_Vec(vector<vector<complex<double> >> &intervet){
    int rsize = intervet.size(), csize = intervet[0].size();
    for(int i=0;i<rsize;++i){
        for(int j=0;j<csize;++j){
            cout<<intervet[i][j]<<"    ";
        }
        cout<<endl;
    }
}//out_put_vector

//二维fft,由于上面的ff2是针对一维的,虽说二维可以由一维算的,但为了方便,重写了个利用一维fft计算二维fft的函数,
void  img_fft( vector<vector< complex<double> > > &intervet){
    int rsize =intervet.size(),csize = intervet[0].size();
    for(int i=0;i<rsize;++i){
        FFT(intervet[i],csize);
    }
    //out_put_Vec(intervet);
    vector<complex<double> > temp (rsize);
    for(int i=0;i<csize;++i){
        for(int j=0;j<rsize;++j){
            temp[j] = intervet[j][i];//取每一列
        }
        FFT(temp,rsize);
        for(int j=0;j<rsize;++j){
            intervet[j][i] = temp[j];
        }
    }
}//2d_fft

//进行ifft时,需要逆转数组下表,因为开始没有看到书上的取共轭,除以MN得到反变换,所以这里先逆转除数组第一个数外的数,具体的swap就
//是swap(f[1],发f[size-1]),有点像快排的patition.
 void idft_reverse(vector<vector<complex<double> >> &res){
    int rsize = res.size(),csize = res[0].size();
    for(int i=0;i<rsize;++i){
        int f=1,r=csize-1;
        while(f<r){
            swap(res[i][f++],res[i][r--]);
        }
    }
    for(int i=0;i<csize;++i){
        int f=1,r=rsize-1;
        while(f<r){
            swap(res[f++][i],res[r--][i]);
        }
    }
 }//ifft变换回去后 需要将其中元素置换 因为fft ifft使用相同函数.

//将图片像素点暂存至数组中
 void copy_img_vec(    vector<vector< complex<double> > > &vec,const Mat &img){//函数没写很完善 默认vec空间是大于img的,img 默认为int
    int ir = img.rows,ic = img.cols;
    int vr = vec.size(),vc = vec[0].size();
    for(int i=0;i<ir;++i){
        for(int j=0;j<ic;++j){
            vec[i][j] = img.at<uchar>(i,j);
        }
    }
}

//上述的float类型
 void copy_img_vec_float(    vector<vector< complex<double> > > &vec,const Mat &img){//函数没写很完善 默认vec空间是大于img的,img 默认为int
    int ir = img.rows,ic = img.cols;
    int vr = vec.size(),vc = vec[0].size();
    for(int i=0;i<ir;++i){
        for(int j=0;j<ic;++j){
            vec[i][j] = img.at<int8_t>(i,j);
        }
    }
}

