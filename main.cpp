#include<bits/stdc++.h>
using namespace std;
#include "Poco/LRUCache.h"

#define CACHE_LEN 128

int CAHCHE[CACHE_LEN];

int main(){
    int size;
    cout << "Enter the size of the cache: ";
    cin >> size;

    vector<int> arr(size);
    
    cout << "Enter " << size << " integers:\n";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    return 0;
}