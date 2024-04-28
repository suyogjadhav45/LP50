%%writefile vector.cu
#include<bits/stdc++.h>
#include <cuda_runtime.h>
using namespace std;


__global__ void multiply(int *a,int *b,int *c,int size){
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;

    if(row<size && col<size){
        int sum=0;
        for(int i=0;i<size;i++){
            sum+=a[row*size+i]*b[i*size+col];
        }
        c[row*size+col]=sum;
    }
}

void initialize(int *a,int size){
    for(int i=0;i<size*size;i++){
        a[i]=rand()%10;
    }
}

void print(int *a,int size){
    for(int row=0;row<size;row++){
        for(int col=0;col<size;col++){
            cout<<a[row*size+col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


int main(){
    int n=2;
    int *a,*b,*c;
    int matrixSize=n*n;
    size_t matrixMem=matrixSize*sizeof(int);

    a=new int(matrixSize);
    b=new int(matrixSize);
    c=new int(matrixSize);

    initialize(a,n);
    initialize(b,n);

    cout << "Matrix A: \n";
    print(a, n);
    cout << "Matrix B: \n";
    print(b, n);

    int *x,*y,*z;

    cudaMalloc(&x,matrixMem);
    cudaMalloc(&y,matrixMem);
    cudaMalloc(&z,matrixMem);

    cudaMemcpy(x,a,matrixMem,cudaMemcpyHostToDevice);
    cudaMemcpy(y,b,matrixMem,cudaMemcpyHostToDevice);

    int THREADS=2;
    int BLOCKS=n/THREADS;

    dim3 threads(THREADS,THREADS);
    dim3 blocks(BLOCKS,BLOCKS);

    multiply<<<blocks,threads>>>(x,y,z,n);

    cudaMemcpy(c,z,matrixMem,cudaMemcpyDeviceToHost);
    cout << "Matrix C: \n";
    print(c, n);  
    delete[] a;
    delete[] b;
    delete[] c;

    cudaFree(x);
    cudaFree(y);
    cudaFree(z);


    return 0;
}