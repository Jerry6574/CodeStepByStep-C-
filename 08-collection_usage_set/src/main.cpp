#include <iostream>
#include <set.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <hashset.h>
#include <hashmap.h>

using namespace std;

bool isHappyNumber(int n) {
    int num = n;
    Set<int> sumsOfSquare;

    while(true){
        int sumOfSquare = 0;

        while(true){
            sumOfSquare += pow(num % 10, 2);
            num /= 10;

            if(num < 10){
                sumOfSquare += pow(num % 10, 2);
                break;
            }
        }
        num = sumOfSquare;

        // if the same sumOfSquare comes up, it will be an infinite loop if we don't stop it.
        if(sumsOfSquare.contains(sumOfSquare) || sumOfSquare == 1) {
            break;
        } else {
            sumsOfSquare.add(sumOfSquare);
        }
    }

    if(num == 1) {
        return true;
    } else {
        return false;
    }
}

int wordCount(string filename) {
    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        input.close();
        return 0;
    }

    string line;

    Set<string> uniqueWords;

    while(getline(input, line)){
        istringstream lineStream(line);
        string word;

        while(lineStream >> word){
            uniqueWords.add(word);
        }
    }

    return uniqueWords.size();
}

int maxLength(Set<string>& set) {
    if(set.size() == 0){
        return 0;
    }
    int max = 0;
    for(string s: set){
        if(s.length() > max){
            max = s.length();
        }
    }
    return max;
}

Set<int> unionSets(HashSet<Set<int> >& sets) {
    Set<int> unionSet;

    for(Set<int> set: sets){
        unionSet.addAll(set);
    }

    return unionSet;
}

Set<int> twice(Vector<int>& v) {
    HashMap<int, int> numFreq;
    for(int num: v){
        if(numFreq.containsKey(num)){
            numFreq[num] += 1;
        } else{
            numFreq[num] = 1;
        }
    }

    Set<int> twiceSet;
    for(int k: numFreq.keys()){
        if(numFreq[k] == 2){
            twiceSet.add(k);
        }
    }

    return twiceSet;
}

int numInCommon(Vector<int>& v1, Vector<int>& v2) {
    if(v1.isEmpty() || v2.isEmpty()){
        return 0;
    }

    Set<int> commonNums;
    for(int n: v1){
        if(v2.contains(n)){
            commonNums.add(n);
        }
    }

    return commonNums.size();
}

void removeDuplicates(Vector<int>& v) {
    Set<int> set;
    for(int i = 0; i < v.size(); i++){
        if(set.contains(v[i])){
            v.remove(i);
            i--;
        } else{
            set.add(v[i]);
        }
    }
}

int main() {
    cout << isHappyNumber(139) << endl;

    return 0;
}
