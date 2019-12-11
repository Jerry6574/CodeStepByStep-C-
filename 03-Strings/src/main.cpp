#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdlib>

using namespace std;

string repeat(string s, int n) {
    string repeatedS = "";
    int i;
    for(i = 0; i < n; i++){
        repeatedS += s;
    }
    return repeatedS;
}

string replaceAll(string s, char c1, char c2) {
    string newS = s;
    for(int i = 0; i < s.size(); i++){
        if(newS[i] == c1){
            newS[i] = c2;
        }
    }
    return newS;
}

void swapPairs(string& s) {
    if(s.size() >= 2){
        for(int i = 0; i < s.size()-1; i += 2){
            char temp = s[i];
            s[i] = s[i+1];
            s[i+1] = temp;
        }
    }
}

void crazyCaps(string& s) {
    for(int i = 0; i < s.size(); i++){
        if(i % 2 == 0){
            s[i] = tolower(s[i]);
        } else{
            s[i] = toupper(s[i]);
        }
    }
}

void nameDiamond(string s) {
    for(int i = 1; i <= s.size(); i++){
        cout << s.substr(0, i) << endl;;
    }
    for(int i = 1; i < s.size(); i++) {
        string subS = s.substr(i, s.size()-i);

        // print padding spaces
        for(int j = 0; j < s.size() - subS.size(); j++) {
            cout << " ";
        }
        cout << subS << endl;
    }
}

int main() {
    cout << repeat("Hello", 3);
    return 0;
}
