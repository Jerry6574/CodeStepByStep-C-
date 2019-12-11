#include <iostream>

using namespace std;

void helloWorld(){
    cout << "Hello, world!" << endl;
}

void fearTheTree(){
    // fearTheTree
    cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
    cout << "|| FEAR THE TREE! ||" << endl;
    cout << "////////////////////" << endl;
}

void fixErrors(){
    int age;
    cout << "How old are you? ";
    cin >> age;
    cout << "You are " << age << ", wow!" << endl;
}

void stanfordVsCal(){
    int standfordScore, calScore;
    cout << "Stanford: How many points did they score? ";
    cin >> standfordScore;
    cout << "Cal: How many points did they score? ";
    cin >> calScore;

    if(standfordScore > calScore){
        cout << "Stanford won!" <<endl;
    } else{
        cout << "Cal won!" <<endl;
    }
}

void percentageGrade(){
    int percent = getInteger("What percentage did you earn? ");
    if (percent >= 90) {
        cout << "You got an A!" << endl;
    } else if (percent >= 80) {
        cout << "You got a B!" << endl;
    } else if (percent >= 70) {
        cout << "You got a C!" << endl;
    } else if (percent >= 60) {
        cout << "You got a D!" << endl;
    } else{
        cout << "You got an F!" << endl;
    }
}

void printTriangle() {
    int i = 0;
    int j = 0;
    int size = 6;
    for(i = 0; i < size; i++){
        for(j = 0; j <= i; j++){
            cout << "#";
        }
        cout << endl;
    }
}

void numberSquare(int min, int max) {
    int i = 0;
    int j = 0;

    for(i = min; i <= max; i++){
        for(j = i; j <= max; j++){
            cout << j;
        }
        for(j = min; j < i; j++){
            cout << j;
        }
        cout << "\n";
    }
}

void rangeOfNumbers(int start, int end) {
    int i = 0;

    if(start < end){
        for(i = 0; i < end - start; i++){
            cout << start + i << ", ";
        }
    } else if(start > end){
        for(i = 0; i < start - end; i++){
            cout << start - i << ", ";
        }
    }
    cout << end;
}

void evenAverage(){
    double sum = 0.0;
    int num = 0;
    double avg = 0.0;
    int count = 0;

    while (1) {
        cout << "Integer? ";
        cin >> num;

        if(num == 0){
            break;
        }
        if(num % 2 == 0){
            sum += num;
            count++;
        }
    }
    avg = sum / count;
    cout << "Average: " << avg;
}

void evenSum() {
    int sum = 0;
    int max = 0;
    int i = 0;
    int count = 0;
    int num = 0;

    cout << "how many integers? ";
    cin >> count;

    for(i = 0; i < count; i++){
        cout << "next integer? ";
        cin >> num;

        if(num % 2 == 0){
            sum += num;
            if(num > max){
                max = num;
            }
        }
    }

    cout << "even sum = " << sum << endl;
    cout << "even max = " << max << endl;
}

int main() {
    printTriangle();
    return 0;
}
