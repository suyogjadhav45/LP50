#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
template <typename T>
T parallelmin(const vector<T> &arr){
    T result=arr[0];
    #pragma omp parallel for reduction(min:result)
    for(int i=0;i<arr.size();i++){
        result=min(arr[i],result);
    }
    return result;
}
template <typename T>
T parallelmax(const vector<T> &arr){
    T result=arr[0];
    #pragma omp parallel for reduction(max:result)
    for(int i=0;i<arr.size();i++){
        result=max(arr[i],result);
    }
    return result;    
}

template <typename T>
T parallelsum(const vector<T> &arr){
    T result=arr[0];
    #pragma omp parallel for reduction(+:result)
    for(int i=0;i<arr.size();i++){
        result+=arr[i];
    }
    return result;  
}

template <typename T>
T parallelavg(const vector<T> &arr){
    T sum=parallelsum(arr);
    return static_cast<double>(sum)/arr.size();    
}
int main(){
    const int size=10;
    vector<int>arr(size);
    for(int i=0;i<size;i++){
        arr[i]=rand() %1000;
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    int minval=parallelmin(arr);
    int maxval=parallelmax(arr);
    int sum=parallelsum(arr);
    double avg=parallelavg(arr);

    cout << "Minimum value: " << minval << endl;
    cout << "Maximum value: " << maxval << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    return 0;
}