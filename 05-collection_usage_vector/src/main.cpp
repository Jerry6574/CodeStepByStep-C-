#include <iostream>
#include "console.h"
#include "ginteractors.h" // for GWindow
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector

using namespace std;

int countInRange(Vector<int>& v, int min, int max) {
    if(v.size() == 0){
        return 0;
    }

    int count = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] >= min && v[i] <= max){
            count++;
        }
    }

    return count;
}

double mean(Vector<double>& data) {
    if(data.size() == 0){
        return 0.0;
    }

    double sum = 0.0;
    for(int i = 0; i < data.size(); i++){
        sum += data[i];
    }

    return sum / data.size();
}

void cumulative(Vector<int>& v) {
    for(int i = 1; i < v.size(); i++){
        v[i] = v[i] + v[i-1];
    }
}

void stretch(Vector<int>& v) {
    for(int i = 0; i < v.size(); i += 2){
        int right = v[i] /2;
        int left = v[i] - right;

        v[i] = left;
        v.insert(i+1, right);
    }
}

void switchPairs(Vector<int>& v) {
    for(int i = 0; i < v.size() - v.size() % 2; i += 2){
        int temp = v[i];
        v[i] = v[i+1];
        v[i+1] = temp;
    }
}

void addStars(Vector<string>& vec) {
    vec.insert(0, "*");
    for(int i = 1; i < vec.size(); i += 2){
        vec.insert(i+1, "*");
    }
}

void removeAll(Vector<string>& v, string value) {
    for(int i = 0; i < v.size(); i++){
        if(v[i] == value){
            v.remove(i);
            i--;
        }
    }
}

void removeEvenLength(Vector<string>& v) {
    int i = 0;

    while(i < v.size()) {
        if(v[i].length() % 2 == 0) {
            v.remove(i);

            // removing an element shifts arraylist to the left, i-- to offset
            i--;
        }
        i++;
    }
}

void removeConsecutiveDuplicates(Vector<int>& v) {
    for(int i = 1; i < v.size(); i++) {
        if(v[i-1] == v[i]) {
            v.remove(i-1);
            i--;
        }
    }
}

void removeBadPairs(Vector<int>& v) {
    if(v.size() == 0) {
        return;
    }
    int remainder = v.size() % 2;

    for(int i = 0; i < v.size() - remainder; i += 2) {
        // bad pair if left is greater than right element
        if(v[i] > v[i+1]) {
            v.remove(i);
            v.remove(i);
            i -= 2;
        }
    }

    // length is odd, ending element is bad by default
    if(remainder == 1) {
        v.remove(v.size() - 1);
    }
}

Vector<int> intersect(Vector<int>& v1, Vector<int>& v2) {
    Vector<int> intersectNums;

    for(int i = 0; i < v1.size(); i++) {
        if(v2.contains(v1[i])) {
            intersectNums.add(v1[i]);
        }
    }

    return intersectNums;
}

void reverseVec(Vector<int>& vec){
    if(vec.size() > 1){
        for(int i = 0; i < vec.size() / 2; i++){
            int temp = vec[i];
            vec[i] = vec[vec.size() - 1 - i];
            vec[vec.size() - 1 - i] = temp;
        }
    }
}

bool isKeithNumber(int n) {
    if(n / 10 == 0) return true;

    int num = n;
    Vector<int> nums;
    int nDigits = 0;

    // add each digit of n to nums
    while(true) {
        nums.add(num % 10);
        num /= 10;
        nDigits++;

        if(num == 0) {
            break;
        }
    }

    // reverse nums for better aesthetics and easy to add subsequent sums
    reverseVec(nums);

    for(int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for(int j = 0; j < nDigits; j++) {
            sum += nums.get(i+j);
        }

        if(sum == n) {
            return true;

        // once sum > n, it's not possible for it to be a Keith number
        } else if(sum > n) {
            break;
        }

        nums.add(sum);
    }

    return false;
}


void printKeithNumber(int n) {
    if(n / 10 == 0){
        cout << n << ": {" << n << "}" << endl;
        return;
    }
    int num = n;
    Vector<int> nums;
    int nDigits = 0;

    // add each digit of n to nums
    while(true) {
        nums.add(num % 10);
        num /= 10;
        nDigits++;

        if(num == 0) {
            break;
        }
    }

    // reverse nums for better aesthetics and easy to add subsequent sums
    reverseVec(nums);

    for(int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for(int j = 0; j < nDigits; j++) {
            sum += nums.get(i+j);
        }

        if(sum == n) {
            cout << n << ": " << nums.toString() << endl;

        // once sum > n, it's not possible for it to be a Keith number
        } else if(sum > n) {
            return;
        }
        nums.add(sum);
    }
}

void findKeithNumbers(int min, int max) {
    for(int i = min; i <= max; i++) {
        printKeithNumber(i);
    }
}

void histogram(Vector<int>& scores) {
    Vector<string> binLabels = {"0's : ", "10's : ", "20's : ", "30's : ", "40's : "};
    Vector<Vector<int>> distribution = {Vector<int>(), Vector<int>(), Vector<int>(), Vector<int>(), Vector<int>()};

    for(int i = 0; i < scores.size(); i++){
        int binIndex = scores[i] / 10;
        distribution[binIndex].add(scores[i]);
    }

    for(int i = 0; i < distribution.size(); i++){
        cout << binLabels[i] << distribution[i].toString() << endl;
    }
}

int main() {
    Vector<int> v = {1, 2, 1, 2, 1};
    switchPairs(v);
    cout << v.toString() << endl;

    findKeithNumbers(47, 742);

    return 0;
}
