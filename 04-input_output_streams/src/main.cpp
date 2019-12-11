#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "strlib.h"
#include "filelib.h"
#include "set.h"
#include <map>
#include <ctype.h>

using namespace std;

void inputStats(string filename) {
    ifstream input(filename);
    if(input.is_open()){
        string newline, line;
        int lineNum = 0;
        int charCount = 0;
        int maxCharCount = 0;
        double totalCharCount = 0.0;
        double avgCharCount = 0.0;

        while(getline(input,line)){
           lineNum++;
           charCount = line.size();
           totalCharCount += charCount;
           if(charCount > maxCharCount){
               maxCharCount = charCount;
           }
           cout << "Line " << lineNum << " has " << charCount << " chars" << endl;

           newline=line;
        }
        avgCharCount = totalCharCount / lineNum;

        cout << lineNum << " lines; longest = " << maxCharCount << ", average = " << avgCharCount << endl;
    }
    input.close();
}

int isVowel(char c){
    char vowels[10] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    for(int i = 0; i < sizeof (vowels) / sizeof (vowels[0]); i++){
        if(c == vowels[i]){
            return 1;
        }
    }

    return 0;
}

int countVowel(string s){
    int vowelCounts = 0;

    for(int i = 0; i < s.length(); i++){
        if(isVowel(s[i])){
            vowelCounts++;
        }
    }

    return vowelCounts;
}

void vowelStats(string filename) {
    ifstream input(filename);
    if(input.is_open()){
        string newline, line;
        int lineNum = 0;
        int charCount = 0;
        int maxCharCount = 0;
        int vowelCount = 0;
        double totalCharCount = 0.0;
        double avgCharCount = 0.0;

        while(getline(input,line)){
           lineNum++;
           charCount = line.size();
           totalCharCount += charCount;
           vowelCount = countVowel(line);

           if(charCount > maxCharCount){
               maxCharCount = charCount;
           }
           cout << "Line " << lineNum << " has " << charCount << " chars and " << vowelCount << " vowels" << endl;

           newline=line;
        }
        avgCharCount = totalCharCount / lineNum;

        cout << lineNum << " lines; longest = " << maxCharCount << ", average = " << avgCharCount << endl;
    }
    input.close();
}

void hoursWorked(string filename) {
    ifstream input;
    input.open(filename.c_str());

    string line, id, name;

    while(getline(input, line)){
        double totalhours = 0.0;
        double hours;
        int days = 0;
        istringstream lineStream(line);

        lineStream >> id >> name;

        while(lineStream >> hours){
            totalhours += hours;
            days++;
        }
        double avgHours = totalhours / days;
        cout << setw(9) << left << name << "(ID# " << setw(4) << right << id
             << ") worked " << setprecision(1) << fixed << totalhours
             << " hours (" << setprecision(2) << fixed << avgHours << "/day)" << endl;
    }
    input.close();
}

string mostCommon(string filename){
    ifstream input;
    input.open(filename);

    string line;

    // pair<int count, int pos>
    map<string, pair<int, int>> namesMap;
    int currentPos = 0;

    while(getline(input, line)){
        istringstream lineStream(line);
        string name;

        while(lineStream >> name){
            if(namesMap.count(name) != 0){
                namesMap[name].first = namesMap[name].first + 1;
            } else{
                namesMap[name].first = 1;
                namesMap[name].second = currentPos;
                currentPos++;
            }
        }
    }

    map<string, pair<int, int>>::iterator namesIt;
    string mostCommonName;

    int maxOcurrence = 0;
    int minPos = 0;

    pair<string, pair<int, int>> maxEntry;

    for(namesIt = namesMap.begin(); namesIt != namesMap.end(); namesIt++){
        if(namesIt->second.first > maxOcurrence ||
           // earlier name takes precedence if same number of occurence
           (namesIt->second.first == maxOcurrence && namesIt->second.second < minPos)){

            mostCommonName = namesIt->first;
            maxOcurrence = namesIt->second.first;
            minPos = namesIt->second.second;
        }
    }
    input.close();
    return mostCommonName;
}

void wordStats(string filename) {
    ifstream input;
    input.open(filename);
    string line;

    int wordCount = 0;
    double totalLength = 0.0;

    if(!input.is_open()){
        cout << "Error, bad input file." << endl;
        input.close();
        return;
    }

    Set<char> uniqueLetters;

    while(getline(input, line)){
        istringstream lineStream(line);
        string word;

        while(lineStream >> word){
            for(int i = 0; i < word.size(); i++){
                if(isalpha(word[i])){
                    uniqueLetters.add(tolower(word[i]));
                }
            }
            wordCount++;
            totalLength += word.size();
        }
    }

    cout << "Total words    = " << wordCount << endl;
    cout << "Average length = " << setprecision(1) << fixed << totalLength / wordCount << endl;
    cout << "Unique letters = " << uniqueLetters.size() << endl;
    input.close();
}

void wordStatsPlus(string filename) {
    ifstream input;
    input.open(filename);
    string line;

    int lineCount = 0;
    int wordCount = 0;
    double totalLength = 0.0;

    if(!input.is_open()){
        cout << "Error, bad input file." << endl;
        return;
    }

    Set<char> uniqueLetters;

    while(getline(input, line)){
        istringstream lineStream(line);
        string word;

        while(lineStream >> word){
            for(int i = 0; i < word.size(); i++){
                if(isalpha(word[i])){
                    uniqueLetters.add(tolower(word[i]));
                }
            }
            wordCount++;
            totalLength += word.size();
        }
        lineCount++;
    }

    double uniqueToTotal = static_cast<double>(uniqueLetters.size()) / 26;

    cout << "Total lines = " << lineCount << endl;
    cout << "Total words = " << wordCount << endl;

    cout << "Total unique letters = " << uniqueLetters.size() << " ("
         <<  static_cast<int>(uniqueToTotal * 100) << "% of alphabet)" << endl;

    cout << "Average words/line = " << static_cast<double>(wordCount) / lineCount << endl;

    cout << "Average word length = " << totalLength / wordCount << endl;
    input.close();
}

double averageValueInFile(string filename) {
    ifstream input;
    input.open(filename);
    string line;
    double sum = 0.0;
    int count = 0;

    if(!input.is_open()){
        input.close();
        return sum;
    }

    while(getline(input, line)){
        istringstream lineStream(line);
        string numStr;

        while(lineStream >> numStr){
            double num = stringToReal(numStr);
            sum += num;
            count++;
        }
    }
    input.close();
    if(count == 0){
        return sum;
    } else {
        return sum / count;
    }
}

void flipLines(string filename) {
    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        cout << "Unable to open input file \"" << filename << "\"!" << endl;
        input.close();
    }


    string line1, line2;

    while(getline(input, line1)){
        if(getline(input, line2)){
            transform(line2.begin(), line2.end(), line2.begin(), ::toupper);
            transform(line1.begin(), line1.end(), line1.begin(), ::tolower);
            cout << line2 << endl;
            cout << line1 << endl;
        } else{
            transform(line1.begin(), line1.end(), line1.begin(), ::toupper);
            cout << line1 << endl;
        }
    }

    input.close();
}

void reverseString(string& s){
    int n = s.length();

    for(int i = 0; i < n / 2; i++){
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
}

int flipAndReverseLines() {
    ifstream input;
    promptUserForFile(input, "Input file name? ", "Unable to open that file.  Try again.");

    int lineCount = 0;
    string line1, line2;
    cout << endl;

    while(getline(input, line1)){
        if(getline(input, line2)){
            transform(line2.begin(), line2.end(), line2.begin(), ::toupper);
            transform(line1.begin(), line1.end(), line1.begin(), ::tolower);
            reverseString(line1);
            reverseString(line2);

            cout << line2 << endl;
            cout << line1 << endl;

            lineCount += 2;
        } else{
            reverseString(line1);
            transform(line1.begin(), line1.end(), line1.begin(), ::toupper);
            cout << line1 << endl;
            lineCount++;
        }
    }

    input.close();

    return lineCount;
}

void coinFlip(string filename) {
    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        input.close();
        return;
    }

    string line;
    int headCount = 0;
    int flipCount = 0;

    while(getline(input, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        istringstream lineStream(line);

        string flip;
        while(lineStream >> flip){
            if(flip == "h" || flip == "heads"){
              headCount++;
            }
            flipCount++;
        }
    }

    cout << headCount << " heads (" << setprecision(0) << fixed
         << static_cast<double>(headCount) / flipCount * 100 << "%)" << endl;

    if(headCount * 2 >= flipCount){
        cout << "You win!" << endl;
    } else{
        cout << "You lose!" << endl;
    }

    input.close();
}

void leetify(string& word){
    stringReplaceInPlace(word, "o", "0");
    stringReplaceInPlace(word, "l", "1");
    stringReplaceInPlace(word, "e", "3");
    stringReplaceInPlace(word, "a", "4");
    stringReplaceInPlace(word, "t", "7");

    if(word[word.length()-1] == 's'){
        word[word.length()-1] = 'Z';
    }

    word = "(" + word + ")";
}

void leetSpeak(string infile, string outfile) {
    ifstream input;
    input.open(infile);
    ofstream output;
    output.open(outfile);
    string line;

    while(getline(input, line)){
        istringstream lineStream(line);
        string word;
        while(lineStream >> word){
            leetify(word);
            output << word + " ";
        }
        output << "\n";
    }

    input.close();
    output.close();
}

void printBox(string filename, int width) {
    ifstream input;
    input.open(filename);
    string line;

    if(!input.is_open()){
        input.close();
        return;
    }

    if(width < 2){
        throw 20;
    }

    for(int i = 0; i < width; i++){
        cout << "#";
    }
    cout << endl;

    while(getline(input, line)){
        string formattedLine = "#";
        for(int i = 0; i <= width - 2; i++){
            if((i >= line.length() || line.length() == 0) && i != width - 2){
              formattedLine += " ";

            } else if(i == width - 2){
              formattedLine += "#";

            // uppercase the first letter of the line
            } else if(i == 0) {
                formattedLine += toupper(line[i]);

            // lowercase the remaining letters of the line
            } else {
                formattedLine += tolower(line[i]);
            }
        }

        cout << formattedLine << endl;
    }


    for(int i = 0; i < width; i++){
        cout << "#";
    }
    cout << endl;
    input.close();
}

int printMostCommonName(string filename) {
    ifstream input;
    input.open(filename);

    if(!input.is_open()){
        input.close();
        return 0;
    }
    string line;
    int currentPos = 0;

    // pair<int count, int pos>
    map<string, pair<int, int>> namesMap;
    Set<string> uniqueNames;

    while(getline(input, line)){
        istringstream lineStream(line);
        string name;

        while(lineStream >> name){
            if(namesMap.count(name) != 0){
                namesMap[name].first = namesMap[name].first + 1;
            } else{
                namesMap[name].first = 1;
                namesMap[name].second = currentPos;
                currentPos++;
            }

            uniqueNames.add(name);
        }
    }

    map<string, pair<int, int>>::iterator namesIt;
    string mostCommonName;

    int maxOcurrence = 0;
    int minPos = 0;

    pair<string, pair<int, int>> maxEntry;

    for(namesIt = namesMap.begin(); namesIt != namesMap.end(); namesIt++){
        if(namesIt->second.first > maxOcurrence ||
           // earlier name takes precedence if same number of occurence
           (namesIt->second.first == maxOcurrence && namesIt->second.second < minPos)){

            mostCommonName = namesIt->first;
            maxOcurrence = namesIt->second.first;
            minPos = namesIt->second.second;
        }
    }

    input.close();
    cout << "Most common name: " << mostCommonName << ", " << maxOcurrence;
    return uniqueNames.size();
}

int getPopScore(map<string, vector<string>>& twitterMap, string person){
    int popScore = 0;

    vector<string>::iterator follower;
    vector<string> followers = twitterMap[person];

    for(follower = followers.begin(); follower != followers.end(); follower++){
        popScore += twitterMap[*follower].size();
    }

    return popScore;
}

string coolest(string filename) {
    ifstream input;
    input.open(filename);
    string line;

    map<string, vector<string>> twitterMap;
    map<string, int> popScores;

    while(getline(input, line)){
        string name1, name2;
        istringstream lineStream(line);

        lineStream >> name1;
        lineStream >> name2;

        if(twitterMap.count(name2) == 0){
            twitterMap[name2] = vector<string>();
        }
        twitterMap[name2].push_back(name1);

        if(twitterMap.count(name1) == 0){
            twitterMap[name1] = vector<string>();
        }
    }

    input.close();

    // <name, followers>
    map<string, vector<string>>::iterator twitterProfile;

    for(twitterProfile = twitterMap.begin(); twitterProfile != twitterMap.end(); twitterProfile++){
        string name = twitterProfile->first;
        int popScore = getPopScore(twitterMap, name);
        popScores[name] = popScore;
    }

    // <name, score>
    map<string, int>::iterator scoreProfile;

    int maxScore = 0;
    string coolestName;

    for(scoreProfile = popScores.begin(); scoreProfile != popScores.end(); scoreProfile++){
        int score = scoreProfile->second;
        string name = scoreProfile->first;

        if(score > maxScore){
            maxScore = score;
            coolestName = name;
        } else if(score == maxScore){
            // name comes first in alphabetical order wins type-breaker
            if(name < coolestName){
                coolestName = name;
            // having followers wins type-breaker over having no followers
            } else if(twitterMap[name].size() > twitterMap[coolestName].size()){
                coolestName = name;
            }
        }
    }

    return coolestName;
}

int main() {
//    inputStats("carroll.txt");
//    hoursWorked("hours.txt");

//    cout << mostCommon("names.txt") << endl;

    cout << coolest("coolest.txt") << endl;
    return 0;
}
