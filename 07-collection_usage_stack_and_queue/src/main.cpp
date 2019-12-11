
#include <iostream>
#include "console.h"
#include "ginteractors.h" // for GWindow
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "stack.h"
#include "queue.h"

using namespace std;

void stutter(Queue<int>& q) {
    int qsize = q.size();

    for(int i = 0; i < qsize; i++){
        int n = q.dequeue();
        q.enqueue(n);
        q.enqueue(n);
    }
}

void mirror(Queue<string>& q) {
    Stack<string> stack;

    // reverse queue
    for(int i = 0; i < q.size(); i++) {
        string s = q.dequeue();
        stack.push(s);
        q.enqueue(s);
    }

    // reverse queue again to restore initial sequence
    for(int i = 0; i < q.size(); i++) {
        string s = q.dequeue();
        q.enqueue(s);
    }

    // add a reversed queue sequence from stack
    while(!stack.isEmpty()) {
        q.enqueue(stack.pop());
    }
}

int checkBalance(string code) {
    Stack<char> stack;

    for(int i = 0; i < code.length(); i++) {
        char c = code[i];

        if(c == '(' || c == '{') {
            stack.add(c);
        }

        // no matching '(' for ')' or '{' for '}'
        if((c == ')' || c == '}') && stack.size() == 0) {
            return i;

        // mismatching '(' for '}' or '{' for ')'
        } else if((c == ')' && stack.peek() != '(') || (c == '}' && stack.peek() != '{')) {
            return i;
        } else if((c == ')' && stack.peek() == '(') || (c == '}' && stack.peek() == '{')) {
            stack.pop();
        }
    }

    if(stack.size() == 0) {
        return -1;
    } else {
        return code.length();
    }
}

int maxInQueue(Queue<int>& q){
    int max = q.peek();
    int qsize = q.size();
    for(int i = 0; i < qsize; i++){
        int num = q.dequeue();

        if(num > max){
            max = num;
        }

        q.enqueue(num);
    }

    return max;
}

void reorder(Queue<int>& queue){
    Stack<int> stack;

    while(!queue.isEmpty()) {
        int max = maxInQueue(queue);
        int n = queue.dequeue();

        if(n == max) {
            stack.push(n);
        } else {
            queue.add(n);
        }
    }

    while(!stack.isEmpty()) {
        queue.add(stack.pop());
    }
}

void flipHalf(Queue<int>& queue) {
    Stack<int> stack;

    int queueSize = queue.size();

    for(int i = 0; i < queueSize; i++) {
        int n = queue.dequeue();

        if(i % 2 == 1) {
            stack.push(n);
        } else {
            queue.add(n);
        }
    }

    while(!stack.isEmpty()) {
        int n = queue.dequeue();
        queue.add(n);
        queue.add(stack.pop());
    }

    // when queue size is odd, queue needs to deque and enque (queueSize / 2) + 1 times
    if(queueSize % 2 == 1){
        int n = queue.dequeue();
        queue.add(n);
    }
}

void splitStack(Stack<int>& stack) {
    Queue<int> queue;

    while(!stack.isEmpty()) {
        queue.add(stack.pop());
    }

    int queueSize = queue.size();


    for(int i = 0; i < queueSize; i++) {
        int n = queue.dequeue();

        // push negative numbers to stack first
        if(n < 0) {
            stack.push(n);

        // add positive number back to tail of queue
        } else {
            queue.add(n);
        }
    }

    while(!queue.isEmpty()) {
        stack.push(queue.dequeue());
    }
}

bool isSorted(Stack<int>& s) {
    if(s.size() <= 1) return true;

    Stack<int> tempStack;
    bool sorted = false;

    int n = s.pop();
    tempStack.push(n);
    while(!s.isEmpty()) {
        if(s.peek() < n) {
            break;
        } else {
            n = s.pop();
            tempStack.push(n);
        }
    }

    if(s.size() == 0) {
        sorted = true;
    }

    while(!tempStack.isEmpty()) {
        s.push(tempStack.pop());
    }

    return sorted;
}

// stackUsingQueue
void push(Queue<int>& queue, int element) {
    queue.enqueue(element);
}
int pop(Queue<int>& queue){
    for(int i = 0; i < queue.size()-1; i++){
        queue.enqueue(queue.dequeue());
    }
    return queue.dequeue();
}

void collapse(Stack<int>& s) {
    if(s.size() <= 1){
        return;
    }

    Stack<int> temp;
    if(s.size() % 2 == 1){
        temp.push(s.pop());
    }

    while (!s.isEmpty()) {
        int sum = 0;
        sum += s.pop();
        sum += s.pop();
        temp.push(sum);
    }

    while(!temp.isEmpty()){
        s.push(temp.pop());
    }
}

bool isPalindrome(Queue<int>& q) {
    if(q.size() <= 1){
        return true;
    }

    Stack<int> s;

    for(int i = 0; i < q.size(); i++){
        int n = q.dequeue();
        s.push(n);
        q.enqueue(n);
    }

    bool isPal = true;

    for(int i = 0; i < q.size()/2 + q.size()% 2 ; i++){
        int n = s.pop();
        int m = q.dequeue();
        if(n != m){
            isPal = false;
        }
        q.enqueue(m);
    }

    // restore q
    for(int i = 0; i < q.size()/2 ; i++){
        q.enqueue(q.dequeue());
    }

    cout << q.toString() << endl;
    return isPal;
}

void rearrange(Queue<int>& q) {
    Stack<int> temp;
    int qSize = q.size();

    for(int i = 0; i < qSize; i++){
        int num = q.dequeue();
        if(num % 2 == 0){
            temp.add(num);
        } else{
            q.enqueue(num);
        }
    }

    // add evens back to q
    while(!q.isEmpty()){
        temp.push(q.dequeue());
    }
    while(!temp.isEmpty()){
        q.enqueue(temp.pop());
    }

    // reverse q
    while(!q.isEmpty()){
        temp.push(q.dequeue());
    }
    while(!temp.isEmpty()){
        q.enqueue(temp.pop());
    }
}

void shift(Stack<int>& s, int n) {
    if(n == 0){
        return;
    }

    int popsize = s.size() - n;
    Queue<int> temp;

    for(int i = 0; i < popsize; i++){
        temp.enqueue(s.pop());
    }

    while(!temp.isEmpty()){
        s.push(temp.dequeue());
    }

    // reverse s
    while(!s.isEmpty()){
        temp.enqueue(s.pop());
    }
    while(!temp.isEmpty()){
        s.push(temp.dequeue());
    }
}

void switchPairs(Stack<int>& s) {
    if(s.size() <= 1){
        return;
    }

    Queue<int> temp;

    if(s.size() % 2 != 0){
        temp.enqueue(s.pop());
    }

    while(!s.isEmpty()){
        int a = s.pop();
        int b = s.pop();
        temp.enqueue(b);
        temp.enqueue(a);
    }

    while(!temp.isEmpty()){
        s.push(temp.dequeue());
    }

    // reverse stack
    while(!s.isEmpty()){
        temp.enqueue(s.pop());
    }
    while(!temp.isEmpty()){
        s.push(temp.dequeue());
    }
}

int main() {
//    Queue<int> q = {3, 8, 17, 9, 17, 8, 3};
//    cout << isPalindrome(q) << endl;

    Stack<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    shift(s, 6);

    return 0;
}
