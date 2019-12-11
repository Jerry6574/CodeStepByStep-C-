#include <iostream>
#include "vector.h"

using namespace std;

int binarySearchHelper(Vector<int>& v, int target, int min, int max) {
    int mid = min + (max - min) / 2;

    if(max >= min) {
        if(v[mid] == target) {
            return mid;
        } else if(v[mid] < target) {
            min = mid + 1;
            // search left half of vector
            return binarySearchHelper(v, target, min, max);
        } else if(v[mid] > target) {
            max = mid - 1;
            // search right half of vector
            return binarySearchHelper(v, target, min, max);
        }
    }
    return -1;
}

int binarySearch(Vector<int>& v, int target){
    int min = 0;
    int max = v.size()-1;
    return binarySearchHelper(v, target, min, max);
}


int main() {
    Vector<int> v = {5, 11, 6, 32, 8, 14};
    cout << binarySearch(v, 32);

    return 0;
}
