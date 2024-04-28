%%writefile vector.cu
#include<bits/stdc++.h>
#include <cuda_runtime.h>
using namespace std;


__global__ void add(int *a, int *b, int *c, int size){
    int tid=blockIdx.x*blockDim.x+threadIdx.x;
    if(tid<size){
        c[tid]=a[tid]+b[tid];
    }
}

void initialize(int *a,int size){
    for(int i=0;i<size;i++){
        a[i]=rand()%100;
    }
}

void print(int *a,int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int n=20;
    int *a,*b,*c;

    size_t vecMem=n*sizeof(int);

    a=new int[n];
    b=new int[n];
    c=new int[n];

    initialize(a,n);
    initialize(b,n);

    cout << "Vector A: ";
    print(a, n);
    cout << "Vector B: ";
    print(b, n);

    int *x,*y,*z;
    cudaMalloc(&x,vecMem);
    cudaMalloc(&y,vecMem);
    cudaMalloc(&z,vecMem);

    cudaMemcpy(x,a,vecMem,cudaMemcpyHostToDevice);
    cudaMemcpy(y,b,vecMem,cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n+threads-1)/threads;
    
    add<<<blocks,threads>>>(x,y,z,n);
    cudaMemcpy(c,z,vecMem,cudaMemcpyDeviceToHost);
    cout << "Vector C: ";
    print(c, n);

    delete[] a;
    delete[] b;
    delete[] c;

    cudaFree(x);
    cudaFree(y);
    cudaFree(z);
    


    return 0;
}

// Cuda commands
// 1) nvcc filename.cu -o filename
// 2) ./filename

// Openmp
// 1)g++ filename.cpp -lgomp -o outputfilename
// 2)./filename