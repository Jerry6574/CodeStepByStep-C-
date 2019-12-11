#include <iostream>
#include <string>
#include "vector.h"
#include "lexicon.h"
#include "set.h"
#include "map.h"    ""

using namespace std;

struct Cryptarithm {
    string op1, op2, sum;
    void replace(char c, int i);
    void unreplace(char c, int i);
};

void printAllBinaryHelper(int digits, string prefix);
void printAllBinary(int digits);
void printAllDecimalHelper(int digits, string prefix);
void printAllDecimal(int digits);
void diceRollsHelper(int dice, string output);
void diceRolls(int dice);
void diceSumHelper(int dice, int desiredSum, int sumSoFar, Vector<int>& chosen);
void diceSum(int dice, int desiredSum);
void diceSum2(int dice, int desiredSum);
void permuteHelper(string s, string chosen);
void permute(string s);
void combin(string s);
bool partitionableHelper(Vector<int>& v, int sum1, int sum2);
bool partitionable(Vector<int>& v);
void makeChange(int amount, Vector<int>& coins);
void printSquares(int n);
string longestCommonSubsequence(string s1, string s2);
void waysToClimbHelper(int stairs, string output, int stride);
void waysToClimb(int stairs);
void listTwiddles(const string& str, const Lexicon& lex);
bool containsHelper(Vector<int>& v, int target, int min, int max);
bool contains(Vector<int>& v, int target);
int maxSum(Vector<int>& numbers, int limit);
void squishWord(string word, Set<string>& dictionary);
bool canBalance(int target, Vector<int>& weights);
string crack(int maxLength);
bool isMeasurable(Vector<int>& weights, int target);
//bool chainExists(const Vector<Domino>& dominoes, int start, int end);
bool isElementSpellable(string text, Lexicon& symbols);
bool canPack(Vector<int>& bags, Vector<int>& items);
bool canMakeSum(Vector<int>& v, int target);
int largestSum(Vector<int>& numbers, int limit);
void phoneWords(string phoneNumber, Lexicon& dictionary, Map<int, string>& letterMap);
void printSubVectors(const Vector<int>& v);
void numberPuzzle(Vector<int>& numbers, int desiredSum);
bool weave(string s1, string s2, Lexicon& dict);
bool cryptaSolver(Cryptarithm& puzzle);

int main() {
    diceRolls(0);
    return 0;
}

void printAllBinaryHelper(int digits, string prefix) {
    if(digits <= 0){
        cout << prefix << endl;
    } else{
        printAllBinaryHelper(digits - 1, prefix + "0");
        printAllBinaryHelper(digits - 1, prefix + "1");
    }
}

void printAllBinary(int digits) {
    printAllBinaryHelper(digits, "");
}

void printAllDecimalHelper(int digits, string prefix){
    if(digits <= 0){
        cout << prefix << endl;
    } else{
        for(int i = 1; i <=9; i++){
            printAllDecimalHelper(digits-1, prefix + to_string(i));
        }
    }
}

void printAllDecimal(int digits) {
    printAllDecimalHelper(digits, "");
}

void diceRollsHelper(int dice, string output) {
    if(dice <= 0){
        if(output.length() == 1){
            return;
        }
        // replace ", " with "}"
        cout << output.substr(0, output.length()-2) << "}" << endl;
    } else{
        for(int i = 1; i <= 6; i++){
            diceRollsHelper(dice - 1, output + to_string(i) + ", ");
        }
    }
}

void diceRolls(int dice) {
    diceRollsHelper(dice, "{");
}

void diceSumHelper(int dice, int desiredSum, int sumSoFar, Vector<int>& chosen) {
    if(dice == 0){
        if(sumSoFar == desiredSum){
            cout << chosen << endl;
        }
    } else{
        for(int i = 1; i <= 6; i++){
            if(sumSoFar + i + 1*(dice-1) <= desiredSum &&
                    sumSoFar + i + 6*(dice-1) >= desiredSum){
                chosen.add(i);
                diceSumHelper(dice - 1, desiredSum, sumSoFar + i, chosen);
                chosen.remove(chosen.size() - 1);
            }
        }
    }
}

void diceSum(int dice, int desiredSum) {
    Vector<int> chosen;
    diceSumHelper(dice, desiredSum, 0, chosen);
}

void diceSumHelper2(int dice, int desiredSum, int sumSoFar, Vector<int>& chosen, Set<Set<int>>& found){
    if(dice == 0){
        Set<int> set;
        for(int n: chosen){
            set.add(n);
        }
        if(!found.contains(set)){
            cout << chosen << endl;
            found.add(set);
        }

    } else{
        for(int i = 1; i <= 6; i++){
            if(sumSoFar + i + 1*(dice-1) <= desiredSum &&
                    sumSoFar + i + 6*(dice-1) >= desiredSum){
                chosen.add(i);
                diceSumHelper2(dice - 1, desiredSum, sumSoFar + i, chosen, found);
                chosen.remove(chosen.size() - 1);
            }
        }
    }
}

void diceSum2(int dice, int desiredSum) {
    Vector<int> chosen;
    Set<Set<int>> found;
    diceSumHelper2(dice, desiredSum, 0, chosen, found);
}

void permuteHelper(string s, string chosen){
    if(s.empty()){
        cout << chosen << endl;
    } else{
        for(int i = 0; i < s.length(); i++){
            char c= s[i];
            chosen += c;
            s.erase(i, 1);
            permuteHelper(s, chosen);
            s.insert(i, 1, c);
            chosen.erase(chosen.length()-1, 1);
        }
    }
}

void permute(string s) {
    permuteHelper(s, "");
}

void combinHelper(string s, string chosen, Set<string>& found){
    if(s.empty()){
        if(!found.contains(chosen)){
            cout << chosen << endl;
        }
        found.add(chosen);
    } else{
        for(int i = 0; i < s.length(); i++){
            char c= s[i];
            chosen += c;
            s.erase(i, 1);
            combinHelper(s, chosen, found);
            s.insert(i, 1, c);
            chosen.erase(chosen.length()-1, 1);
        }
    }
}

void combin(string s) {
    Set<string> found;
    combinHelper(s, "", found);
}

//void solveQueensHelper(Board& board, int col) {
//    if(col >= board.size()){
//        cout << board.toString() << endl;
//    } else{
//        for(int row = 0; row < board.size(); row++){
//            if(board.isSafe(row, col)){
//                board.place(row, col);
//                solveQueensHelper(board, col + 1);
//                board.remove(row, col);
//            }
//        }
//    }
//}

//void solveQueens(Board& board) {
//    solveQueensHelper(board, 0);
//}

bool partitionableHelper(Vector<int>& v, int sum1, int sum2){
    if(v.isEmpty()){
        return sum1 == sum2;
    } else{
        int val = v.pop_back();
        bool result = partitionableHelper(v, sum1 + val, sum2) ||
                      partitionableHelper(v, sum1, sum2 + val);
        v.push_back(val);
        return result;
    }
}

bool partitionable(Vector<int>& v) {
    return partitionableHelper(v, 0, 0);
}

//void makeChangeHelper(int amount, Vector<int>& coins, Vector<int> changes){
//    if(amount == 0){
//        cout << changes << endl;
//    } else{

//    }
//}

//void makeChange(int amount, Vector<int>& coins) {
//    Vector<int> changes = {0, 0, 0};
//    makeChangeHelper(amount, coins, changes);
//}

void printSquares(int n) {
    return;
}

string longestCommonSubsequence(string s1, string s2) {
    return "";
}

void waysToClimbHelper(int stairs, string output, int stride){
    if(stairs <= 0){
        throw stairs;
    } else if(stairs > stride) {
        waysToClimbHelper(stairs, output + "1, ", stride + 1);
        waysToClimbHelper(stairs, output + "2, ", stride + 2);
    } else if (stairs == stride && stairs != 0){
        // replace " ," with "}"
       cout << output.substr(0, output.length()-2) << "}" << endl;
    }
}

void waysToClimb(int stairs) {
    waysToClimbHelper(stairs, "{", 0);
}

void listTwiddles(const string& str, const Lexicon& lex) {
    return;
}

// Check the range from min to max, inclusive
bool containsHelper(Vector<int>& v, int target, int min, int max) {
    if (min == max) {
        return false;                // base case: no numbers to search
    } else {
        int mid = (max - min) / 2;   // index halfway between min and max
        if (v[mid] == target) {
            return true;
        } else {                     // recursive case
            return containsHelper(v, target, min, mid - 1);
            return containsHelper(v, target, mid + 1, max);
        }
    }
}

bool contains(Vector<int>& v, int target) {
    return containsHelper(v, target, 0, v.size());
}

int maxSum(Vector<int>& numbers, int limit) {
    return 0;
}

void squishWord(string word, Set<string>& dictionary) {
    return;
}

bool canBalance(int target, Vector<int>& weights) {
    return true;
}

string crack(int maxLength) {
    return "";
}

bool isMeasurable(Vector<int>& weights, int target) {
    return true;
}

//bool chainExists(const Vector<Domino>& dominoes, int start, int end) {
//    return true;
//}

bool isElementSpellable(string text, Lexicon& symbols) {
    return true;
}

bool canPack(Vector<int>& bags, Vector<int>& items) {
    return true;
}

bool canMakeSum(Vector<int>& v, int target) {
    return true;
}

int largestSum(Vector<int>& numbers, int limit) {
    return 0;
}

void phoneWords(string phoneNumber, Lexicon& dictionary, Map<int, string>& letterMap) {
    return;
}

void printSubVectors(const Vector<int>& v) {
    return;
}

void numberPuzzle(Vector<int>& numbers, int desiredSum) {
    return;
}

//void knightsTour(Grid<int>& board, Location startLoc) {
//	return;
//}

bool cryptaSolver(Cryptarithm& puzzle) {
    return true;
}

bool weave(string s1, string s2, Lexicon& dict) {
    return true;
}
