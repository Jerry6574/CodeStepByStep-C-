#include <iostream>
#include "map.h"
#include <fstream>
#include <sstream>
#include "set.h"
#include <ctype.h>
#include "strlib.h"
#include "lexicon.h"
#include "random.h"

using namespace std;

Map<string, int> intersection(Map<string, int>& map1, Map<string, int>& map2) {
    Map<string, int> intersect;
    if(map1.isEmpty() || map2.isEmpty()){
        return intersect;
    }

    Vector<string> keys1 = map1.keys();
    Vector<string> keys2 = map2.keys();

    for(string key: keys1){
        if(keys2.contains(key) && map1[key] == map2[key]){
            intersect[key] = map1[key];
        }
    }

    return intersect;
}

Map<string, int> reverse(Map<int, string>& map) {
    Map<string, int> reversed;
    Vector<int> keys = map.keys();

    for(int k: keys){
        string val = map[k];
        if(!reversed.containsKey(val)){
            reversed[val] = k;
        } else{
            if(k < reversed[val]){
                reversed[val] = k;
            }
        }
    }

    return reversed;
}

Map<string, Set<string>> friendList(string filename) {
    ifstream input;
    input.open(filename);

    string line;
    Map<string, Set<string>> friendship;

    while(getline(input, line)){
        istringstream lineStream(line);
        string name1, name2;
        lineStream >> name1 >> name2;

        friendship[name2].add(name1);
        friendship[name1].add(name2);
    }

    input.close();

    return friendship;
}

Set<char> commonFirstLetters(Vector<string>& v) {
    Map<char, int> firstLetterFreq;
    Set<char> firstLetters;

    for(string s: v){
        if(s.length() > 0){
            char firstLetter = tolower(s[0]);
            firstLetterFreq[firstLetter] += 1;
        }
    }

    for(char c: firstLetterFreq.keys()){
        if(firstLetterFreq[c] > 1){
            firstLetters.add(c);
        }
    }

    return firstLetters;
}

char mostCommonFirstChar(Set<string>& set) {
    Map<char, int> firstCharFreq;

    for(string s: set){
        char firstChar = tolower(s[0]);
        firstCharFreq[firstChar] += 1;
    }

    int maxOccur = 0;
    char maxChar = 'a';
    for(char c: firstCharFreq.keys()){
        if(firstCharFreq[c] > maxOccur){
            maxChar = c;
            maxOccur = firstCharFreq[c];
        } else if(firstCharFreq[c] == maxOccur && c < maxChar){
            maxChar = c;
            maxOccur = firstCharFreq[c];
        }
    }

    return maxChar;
}

Map<int, string> byAge(const Map<string, int>& ages, int min, int max) {
    Map<int, string> byAgeMap;

    for(string name: ages.keys()){
        int age = ages[name];
        if(age >= min && age <= max){
            if(byAgeMap.containsKey(age)){
                byAgeMap[age] += (" and " + name);
            } else{
                byAgeMap[age] = name;
            }
        }
    }

    return byAgeMap;
}

string getLastName(string name){
    istringstream iss(name);
    string lastName;
    while(iss >> lastName){

    }
    return lastName;
}

Map<int, string> lastNamesByAge(const Map<string, int>& ages, int min, int max) {
    Map<int, string> byAgeMap;

    for(string name: ages.keys()){
        string lastName = getLastName(name);
        int age = ages[name];

        if(age >= min && age <= max){
            if(byAgeMap.containsKey(age)){
                byAgeMap[age] += (" and " + lastName);
            } else{
                byAgeMap[age] = lastName;
            }
        }
    }

    return byAgeMap;
}

Set<char> starters(const Vector<string>& v, int k) {
    Set<char> set;
    Map<char, int> charFreq;

    for(string s: v){
        if(s.length() > 0){
            char c = tolower(s[0]);
            charFreq[c] += 1;
        }
    }

    for(char c: charFreq.keys()){
        if(charFreq[c] >= k){
            set.add(c);
        }
    }

    return set;
}

string rarest(const Map<string, string>& map) {
    if(map.isEmpty()){
        throw "Map is empty";
    }

    Map<string, int> nameFreq;
    for(string k: map.keys()){
        nameFreq[map[k]] += 1;
    }

    string rarestName = nameFreq.keys()[0];
    int min = nameFreq[rarestName];

    for(string k: nameFreq){
        if(nameFreq[k] < min || (nameFreq[k] == min && k < rarestName)){
            min = nameFreq[k];
            rarestName = k;
        }
    }

    return rarestName;
}

void toMorseCode(Map<char, string>& codeMap, string text) {
    string upperText = toUpperCase(text);

    for(char c: upperText){
        if(isalpha(c)){
            cout << codeMap[c] << " ";
        }
    }
}

void pairFrequencies(Lexicon& dictionary) {
    if(dictionary.size() == 0){
        return;
    }

    Map<string, int> pairFreq;
    for(string word: dictionary){
        if(word.length() > 1){
            for(int i = 0; i < word.length()-1; i++){
                string pair = word.substr(i, 2);
                pairFreq[pair] += 1;
            }
        }
    }

    for(string pair: pairFreq.keys()){
        cout << pair << ": " << pairFreq[pair] << endl;
    }
}

void wordChain(string filename, string startWord) {
    if(startWord.length() < 2){
        throw "startWord length must be greater than or equal 2.";
    }

    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        input.close();
        throw "File not found.";
    }

    Map<string, Vector<string>> dict;
    string word;

    // store first2char and wordlist in dict
    while(getline(input, word)){
        if(word.length() >= 2){
            word = toLowerCase(word);
            string first2char = word.substr(0, 2);
            dict[first2char].add(word);
        }
    }

    input.close();

    word = toLowerCase(startWord);
    string end2char = word.substr(word.length()-2, 2);

    // print wordchain
    while(true){
        cout << word << endl;
        if(dict.containsKey(end2char)){
            int wordListSize = dict[end2char].size();
            int randInt = randomInteger(0, wordListSize-1);

            word = dict[end2char][randInt];
            end2char = word.substr(word.length()-2, 2);
        } else{
            break;
        }
    }
}

void areaCodes(string filename) {
    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        input.close();
        return;
    }

    string phoneNum;
    Map<int, Set<string>> areaCodeFreq;
    while(getline(input, phoneNum)){
        int areaCode = stringToInteger(phoneNum.substr(0, 3));
        areaCodeFreq[areaCode].add(phoneNum);
    }

    input.close();

    int maxCount = 0;
    int maxAreaCode = 0;

    Vector<int> areaCodeKeys = areaCodeFreq.keys();

    for(int areaCode: areaCodeKeys){
        int n_phoneNums = areaCodeFreq[areaCode].size();

        if(n_phoneNums > maxCount || (n_phoneNums == maxCount && areaCode < maxAreaCode)){
            maxAreaCode = areaCode;
            maxCount = n_phoneNums;
        }
    }

    for(string phoneNum: areaCodeFreq[maxAreaCode]){
        cout << phoneNum << endl;
    }
}

void biggestFamily(string filename) {
    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        input.close();
        throw "File not found.";
    }

    string name;
    Map<string, Set<string> > families;

    while(getline(input, name)){
        istringstream nameStream(name);
        string firstName, lastName;

        nameStream >> firstName >> lastName;
        families[lastName].add(firstName);
    }

    input.close();

    int biggestSize = 0;

    for(string lastName: families.keys()){
        int familySize = families[lastName].size();
        if(familySize > biggestSize){
            biggestSize = familySize;
        }
    }

    for(string lastName: families.keys()){
        int familySize = families[lastName].size();

        if(familySize == biggestSize){
            cout << lastName << " family: ";
            for(string firstName: families[lastName]){
                cout << firstName << " ";
            }
            cout << endl;
        }
    }
}

void chatBuddies(string filename) {
    ifstream input;
    input.open(filename);
    if(!input.is_open()){
        throw "File not found. ";
    }

    string line;
    bool newConvo = true;
    Map<string, pair<int, bool>> convoFreq;

//    while(getline(input, line)){
//        istringstream lineStream(line);
//        string name;
//        lineStream >> name;

//        //delete ": "
//        name = name.substr(0, name.length()-2);

//        if(newConvo){
//            convoFreq[name]++;
//        }
//    }
}


int main() {
    Vector<string> v = {"Julie", "hi", "how", "is", "He", "Marty!", "this", "morning?", "fine.", "?huh?", "HOW", "I"};
    Set<char> firstLetters = commonFirstLetters(v);
    cout << firstLetters.toString() << endl;

    return 0;
}
