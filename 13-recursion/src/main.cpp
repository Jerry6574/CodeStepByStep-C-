#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctype.h>
#include "stack.h"
#include "filelib.h"
#include "vector.h"  // for Vector
#include "hashmap.h"

using namespace std;

int factorial(int n) {

    if(n == 1 || n == 0){
        return 1;
    } else{
        return n * factorial(n - 1);
    }
}

void printStars(int n) {
    if(n > 0){
        cout << "*";
        printStars(n-1);
    }
}

int power(int base, int exp) {
    if(exp == 0){
        return 1;
    } else{
        return base * power(base, exp - 1);
    }
}

bool isPalindrome(string s) {
    string lowerS = s;
    transform(lowerS.begin(), lowerS.end(), lowerS.begin(), ::tolower);

    if(lowerS.length() <= 1){
        return true;
    } else{
        char first = lowerS[0];
        char last = lowerS[lowerS.length()-1];

        if(first != last) {
            return false;
        } else {
            lowerS = lowerS.substr(1, lowerS.length()-2);
            return isPalindrome(lowerS);
        }
    }
}

int evenDigits(int n) {
    if(n == 0) {
        return 0;
    } else {
        int last = n % 10;

        if(last % 2 == 0) {
            return 10 * evenDigits(n / 10) + last;
        } else {
            return evenDigits(n / 10);
        }
    }
}

void printBinary(int n) {
    if(n > 1) {
        printBinary(n / 2);
        cout << n % 2;
        return;
    } else if(n < 0){
        cout << "-";
        printBinary(abs(n) / 2);
        cout << abs(n) % 2;
    } else {
        cout << n;
    }
}

void reverseLines(ifstream& input) {
    string line;
    if(getline(input, line)){
        reverseLines(input);
        cout << line << endl;
    }
}

void crawlHelper(string filename, string indent){
    cout << indent + getTail(filename) << endl;
    if(isDirectory(filename)){
        Vector<string> files = listDirectory(filename);
        for(string file: files){
            crawlHelper(filename + "/" + file, indent + "    ");
        }
    }
}

void crawl(string filename) {
    crawlHelper(filename, "");
}

int digitSum(int n) {
    if(n / 10 == 0) {
        return n;
    } else {
        int digit = n % 10;
        return digit + digitSum(n / 10);
    }
}

void travelHelper(int x, int y, string output) {
    if(x > 0 && y > 0) {
        travelHelper(x-1, y-1, output + "NE ");
        travelHelper(x, y-1, output + "N ");
        travelHelper(x-1, y, output + "E ");
    } else if(y > 0) {
        travelHelper(x, y-1, output + "N ");
    } else if(x > 0) {
        travelHelper(x-1, y, output + "E ");
    } else if (x == 0 && y == 0){
        cout << output << endl;
    }
}

void travel(int x, int y) {
    travelHelper(x, y, "");
}

int sumOfSquares(int n) {
    if(n < 0){
        throw 404;
    } else if(n == 0){
        return  0;
    } else{
        return n*n + sumOfSquares(n-1);
    }
}

int gcd(int a, int b) {
    if(a < 0 || b < 0){
        throw 1;
    }else if(a % b == 0){
        return b;
    } else{
        return gcd(b, a % b);
    }
}

long long int fastFact(int n, HashMap<int, long long int>& memo){
    if(n == 0 || n == 1){
        return 1;
    } else if(memo.containsKey(n)){
        return memo[n];
    } else{
        long long int x = fastFact(n-1, memo) * n;
        memo[n] = x;
        return x;
    }
}

// nCk = n! / (k! * (n - k)!)
long long int combin(int n, int k) {
    HashMap<int, long long int> memo;
    if(k == 0 || k == n){
        return 1;
    } else if(n <= 0 || k < 0 || k > n){
        return 0;
    } else{
        return combin(n-1, k-1) * n;
    }
}

string reverse(string s) {
    if(s.length() <= 1) {
        return s;
    } else {
        string first = string(1, s[0]);
        string last = string(1, s[s.length() - 1]);

        return last + reverse(s.substr(1, s.length() - 2)) + first;
    }
}

void zigzag(int n) {
    if(n < 1) {
        throw 1;
    } else if(n == 1) {
        cout << "*";
    } else if(n == 2) {
        cout << "**";
    } else {
        cout << "<";
        zigzag(n-2);
        cout << ">";
    }
}

string repeatString(string s, int n){
    if(n < 0) {
        throw "n must be > 1";
    } else if(n == 0) {
        return "";
    } else {
        return s + repeatString(s, n-1);
    }
}

string starString(int n) {
    string stars = "";
    if(n < 0) {
        throw 1;
    } else if(n == 0) {
        return "*";
    } else {
        stars = repeatString("*", static_cast<int>(pow(2, n-1)));
        return stars + starString(n - 1);
    }
}

void stutterStack(Stack<int>& s) {
    if(s.size() == 0) {
        return;
    } else {
        int top = s.pop();
        stutterStack(s);
        s.push(top);
        s.push(top);
    }
}

bool isSubsequence(string big, string small) {
    if(small.length() == 0) {
        return true;
    } else if(big.length() == 0) {
        return false;
    } else {
        // last char of two strings match
        if(big[big.length()-1] == small[small.length()-1]){
            return isSubsequence(big.substr(0, big.length()-1), small.substr(0, small.length()-1));
        // last char of two strings don't match
        } else {
            return isSubsequence(big.substr(0, big.length()-1), small);
        }
    }
}

void countToByHelper(int n, int m){
    if(n >= 1) {
        countToByHelper(n-m, m);
        cout << n << ", ";
    }
}

void countToBy(int n, int m) {
    if(n < 1 || m < 1) {
        throw 1;
    } else {
        countToByHelper(n-m, m);
        cout << n;
    }
}

void numberSequence(int n) {
    if(n < 1) {
        throw 1;
    } else if(n == 1) {
        cout << "1";
    } else if(n == 2){
        cout << "1 1";
    } else {
        if(n % 2 == 1) {
            cout << n / 2 + 1 << " ";
            numberSequence(n - 2);
            cout << " " << n / 2 + 1;
        } else {
            cout << n / 2 << " ";
            numberSequence(n - 2);
            cout << " " << n / 2;
        }
    }
}

int editDistance(const string& s1, const string& s2) {
    if(s1.length() == 0) {
        return s2.length();
    } else if(s2.length() == 0) {
        return s1.length();
    } else {
        int replacement = 0;
        if(s1[0] == s2[0]) {
            return editDistance(s1.substr(1), s2.substr(1));
        } else {
            replacement = 1;
        }

        int replacements = replacement + editDistance(s1.substr(1), s2.substr(1));
        int insertions = editDistance(s1, s2.substr(1)) + 1;
        int deletions = editDistance(s1.substr(1), s2) + 1;

        return min(deletions, min(replacements, insertions));
    }
}

void hanoi(int disks, int from, int to) {
    if(disks == 1) {
        cout << "move disk " << disks << " from peg " << from << " to peg " << to << endl;
    } else {
        int temp = 0;
        if((from == 1 && to == 2) || (from == 2 && to == 1)) {
            temp = 3;
        } else if((from == 1 && to == 3) || (from == 3 && to == 1)){
            temp = 2;
        } else if((from == 2 && to == 3) || (from == 3 && to == 2)) {
            temp = 1;
        }

        hanoi(disks - 1, from, temp);
        cout << "move disk " << disks << " from peg " << from << " to peg "<< to << endl;
        hanoi(disks - 1, temp, to);
    }
}

string moveToEnd(string s, char c) {
    if(s.length() == 0) {
        return s;
    } else {
        char first = s[0];
        if(tolower(first) == tolower(c)) {
            if(isalpha(first)) {
                return moveToEnd(s.substr(1), c) + string(1, toupper(first));
            } else {
                return moveToEnd(s.substr(1), c) + string(1, first);
            }
        } else {
            return string(1, first) + moveToEnd(s.substr(1), c);
        }
    }
}

int matchCountHelper(const Vector<int>& v1, const Vector<int>& v2, int v1Index, int v2Index) {
    if(v1Index + 1 > v1.size() || v2Index + 1 > v2.size()){
        return 0;
    } else{
        int match = 0;
        if(v1[v1Index] == v2[v2Index]){
            match = 1;
        }

        return match + matchCountHelper(v1, v2, v1Index+1, v2Index+1);
    }
}

int matchCount(const Vector<int>& v1, const Vector<int>& v2) {
    return matchCountHelper(v1, v2, 0, 0);
}

int indexOfHelper(string s1, string s2, int s1beginIndex){
    string subS1 = s1.substr(s1beginIndex);
    if(subS1.length() < s2.length()) {
        return -1;
    } else if(subS1.substr(0, s2.length()) == s2) {
        return s1beginIndex;
    } else {
        return indexOfHelper(s1, s2, s1beginIndex+1);
    }
}

int indexOf(string s1, string s2) {
    if(s2.length() == 0) {
        return 0;
    } else {
        return indexOfHelper(s1, s2, 0);
    }
}

void sequence(int k) {
    if(k < 1) {
        throw 1;
    } else if(k == 1) {
        cout << k;
    } else {
        if(k % 2 == 0) {
            cout << "(" << k << " + ";
            sequence(k - 1);
            cout << ")";
        } else {
            cout << "(";
            sequence(k - 1);
            cout << " + " << k << ")";
        }
    }
}

void printRange(int x, int y) {
    if(x > y) {
        throw 1;
    } else if(x == y) {
        cout << x;
    } else if(x + 1 == y) {
        cout << x << " -- " << y;
    } else {
        cout << x << " > ";
        printRange(x+1, y-1);
        cout << " < " << y;
    }
}

int mergeDigitPairs(int n) {
    if(n / 10 == 0) {
        return n;
    } else {
        int a = n % 10;
        int b = n / 10 % 10;

        int merged = mergeDigitPairs(a+b);
        return 10 * mergeDigitPairs(n/100) + merged;
    }
}

string collapseSequences(string s, char ch) {
    if(s.length() <= 1){
        return s;
    } else{
        if(s[0] == s[1] && s[0] == ch){
            return collapseSequences(s.substr(1), ch);
        }
        else{
            return string(1, s[0]) + collapseSequences(s.substr(1), ch);
        }
    }
}


bool digitsSorted(int x) {
    if(x / 10 == 0) {
        return true;

    } else {
        int abs_x = abs(x);

        if(abs_x / 10 % 10 > abs_x % 10) {
            return false;
        } else {
            return digitsSorted(abs_x / 10);
        }
    }
}

string replaceAll(string s, char from, char to) {
    if(s.length() == 0){
        return "";
    }

    char first = s[0];
    if(first == from){
        first = to;
    }

    if(s.length() == 1){
        return string(1, first) + "";
    } else{
        return string(1, first) + replaceAll(s.substr(1), from, to);
    }
}

string lettersOnly(string s) {
    if(s.length() == 0){
        return "";
    }

    if(isalpha(s[0])){
        return string(1, s[0]) + lettersOnly(s.substr(1, s.length()-1));
    } else{
        return lettersOnly(s.substr(1, s.length()-1));
    }
}

int nonMatching(string s1, string s2) {
    if(s1.length() == 0) {
        return s2.length();

    } else if(s2.length() == 0) {
        return s1.length();

    } else {
        int nonMatchCount = 0;
        if(s1[0] != s2[0]) {
            nonMatchCount = 1;
        }
        return nonMatchCount + nonMatching(s1.substr(1), s2.substr(1));
    }
}

int countOccurrencesHelper(Vector<int>& v1, Vector<int>& v2, int i) {
    if(v1.subList(i, v1.size()-i).size() < v2.size()){
        return 0;
    } else{
        int count = 0;
        if(v1.subList(i, v2.size()).equals(v2)){
            count++;
        }

        return count + countOccurrencesHelper(v1, v2, i+1);
    }
}

int countOccurrences(Vector<int>& v1, Vector<int>& v2){
    return countOccurrencesHelper(v1, v2, 0);
}

int countDuplicates(Stack<int>& stack) {
    if(stack.size() <= 1){
        return 0;
    } else{
        int count = 0;
        int top = stack.pop();

        if(top == stack.peek()){
            count = 1 + countDuplicates(stack);
        } else{
            count = countDuplicates(stack);
        }
        stack.push(top);
        return count;
    }
}

int longestRun(Vector<int>& v) {
    return 0;
}

int main() {
    cout << "Hello world" << endl;

    return 0;
}
