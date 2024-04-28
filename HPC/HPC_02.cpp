/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <omp.h>
#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;
void bubblesort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
//Parallel bubblesort
void Parallelbubblesort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){
#pragma omp parallel for
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
void merge(vector<int>&arr, int l,int m,int r){
    int n1=m-l+1;
    int n2=r-m;
    vector<int>L(n1), R(n2);
    for(int i=0;i<n1;++i){
        L[i]=arr[l+i];
    }
    for(int j=0;j<n2;++j){
        R[j]=arr[m+1+j];
    }
    int i=0,j=0,k=l;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]){
            arr[k]=L[i];
            i++;
        }
        else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(i<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
}
void mergesort(vector<int>&arr, int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergesort(arr,l,m);
        mergesort(arr,m+1,r);
        
        merge(arr,l,m,r);
    }
}
//PArallel Merge sort
void parallelmergesort(vector<int>&arr, int l,int r){
    if(l<r){
        int m=(l+r)/2;
#pragma omp parallel sections
    {
#pragma omp section
        parallelmergesort(arr,l,m);
#pragma omp section
        parallelmergesort(arr,m+1,r);
    }    
        merge(arr,l,m,r);
    }
}
int main(){
    const int size=1000;
    vector<int>arr(size), arr_copy(size);
    for(int i=0;i<size;i++){
        arr[i]=rand()%1000;
        arr_copy[i]=arr[i];
    }

//Sequential Bubble sort execution time
auto start=high_resolution_clock::now();
bubblesort(arr_copy);
auto stop=high_resolution_clock::now();
auto seq_duration_bubble=duration_cast<milliseconds>(stop-start);

//Parallel Bubble sort execution time
start=high_resolution_clock::now();
Parallelbubblesort(arr);
stop=high_resolution_clock::now();
auto par_duration_bubble=duration_cast<milliseconds>(stop-start);

//Sequential Merge sort execution time
start=high_resolution_clock::now();
mergesort(arr_copy,0,size-1);
stop=high_resolution_clock::now();
auto seq_duration_merge=duration_cast<milliseconds>(stop-start);

//Parallel Bubble sort execution time
start=high_resolution_clock::now();
parallelmergesort(arr,0,size-1);
stop=high_resolution_clock::now();
auto par_duration_merge=duration_cast<milliseconds>(stop-start);

cout<<"-------------Execution Times------------"<<endl;
cout<<"Sequential Bubble Sort: "<<seq_duration_bubble.count()<<"milliseconds"<<endl;
cout<<"Parallel Bubble Sort: "<<par_duration_bubble.count()<<endl;
cout<<"Sequential Merge Sort: "<<seq_duration_merge.count()<<endl;
cout<<"Parallel Merge Sort: "<<par_duration_merge.count()<<endl;
return 0;
}