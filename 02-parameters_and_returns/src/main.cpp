#include <iostream>
#include <math.h>

using namespace std;

int daysInMonth(int month) {
    int days;
    switch (month) {
        case 2: days = 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11: days = 30;
            break;
        default: days = 31;
            break;
    }
    return days;
}

int decimalToBinary(int number) {

    int decimalNum = number;
    int binaryPos = 1;
    int binaryNum = 0;

    while(1) {
        if(decimalNum == 0) {
            break;
        }

        // build up binary number from least significant bit to most significant bit
        binaryNum = binaryNum + decimalNum % 2 * binaryPos;
        decimalNum /= 2;
        binaryPos *= 10;
    }

    return binaryNum;
}

int binaryToDecimal(int number) {
    int binaryNum = number;

    int decimalNum = 0;
    int exponent = 0;

    while(1) {
        if(binaryNum == 0) {
            break;
        }

        // raise each binary digit to the power of its position (0-base),
        // then sum all the results as the decimal number
        decimalNum = decimalNum + static_cast<int> (binaryNum % 10 * pow(2, exponent));
        exponent++;
        binaryNum /= 10;
    }
    return decimalNum;
}

int isFactor(int factor, int num) {
    if(num % factor == 0) {
        return 1;
    } else {
        return 0;
    }
}

int factorCount(int n) {
    if(n == 1) {
        return 1;
    }

    // 1 and number itself are always factors
    int nFactors = 2;

    for(int i = 2; i <= n / 2; i++) {
        if(isFactor(i, n)) {
            nFactors++;
        }
    }
    return nFactors;
}

double computeBMI(double height, double weight) {
    double bmi = weight / pow(height, 2) * 703;
    return bmi;
}

int classify(double bmi){
    if(bmi < 18.5){
        return 1;
    } else if(bmi >= 18.5 && bmi <= 24.9){
        return 2;
    } else if(bmi >= 25.0 && bmi <= 29.9){
        return 3;
    } else{
        return 4;
    }

}

void BMI(){
    cout << "This program reads data for two people" << endl;
    cout << "and computes their body mass index (BMI)." << "\n" << endl;

    double heightP1, weightP1, heightP2, weightP2, bmiP1, bmiP2;
    int classP1, classP2;

    cout << "Enter Person 1's information:" << endl;
    cout << "height (in inches)? ";
    cin >> heightP1;
    cout << "weight (in pounds)? ";
    cin >> weightP1;

    bmiP1 = computeBMI(heightP1, weightP1);
    classP1 = classify(bmiP1);
    cout << "BMI = " << bmiP1 << ", class " << classP1 << "\n" << endl;

    cout << "Enter Person 2's information:" << endl;
    cout << "height (in inches)? ";
    cin >> heightP2;
    cout << "weight (in pounds)? ";
    cin >> weightP2;

    bmiP2 = computeBMI(heightP2, weightP2);
    classP2 = classify(bmiP2);
    cout << "BMI = " << bmiP2 << ", class " << classP2 << "\n" << endl;

    cout << "BMI difference = " << fabs(bmiP1 - bmiP2) << endl;
}

void xkcdDatingRange(int age, int& min, int& max) {
    min = age / 2 + 7;
    max = 2 * (age - 7);
}

void quadratic(int a, int b, int c, double& root1, double& root2) {
    root1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    root2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
}

int main() {
    cout << daysInMonth(11) << endl;
    cout << decimalToBinary(44) << endl;
    cout << binaryToDecimal(101100) << endl;
    cout << factorCount(24) << endl;
    BMI();
    return 0;
}
