#include <iostream>
#include "pqueue.h"
#include "stack.h"

using namespace std;

bool isConsecutive(PriorityQueue<int>& pq) {
    if(pq.isEmpty()){
        return true;
    }

    PriorityQueue<int> tempPQ;
    int curValue = pq.peek();
    int nextValue;
    bool isConsec = true;
    int i = 0;

    while(!pq.isEmpty()){
        double priority = pq.peekPriority();
        int value = pq.peek();
        pq.dequeue();
        tempPQ.enqueue(value, priority);

        if(i != 0){
            nextValue = value;
            if(curValue + 1 != nextValue){
                isConsec = false;
            } else{
                curValue = nextValue;
            }
        }
        i++;
    }

    pq = tempPQ;
    return isConsec;
}

int main() {
    PriorityQueue<int> pq1;
    pq1.enqueue(1, 1);
    pq1.enqueue(2, 2);
    pq1.enqueue(3, 3);
    pq1.enqueue(5, 4);

    PriorityQueue<int> pq2;
    pq2.enqueue(1, 1);
    pq2.enqueue(2, 2);
    pq2.enqueue(3, 3);
    pq2.enqueue(4, 4);

    cout << "pq1 is consecutive: " << isConsecutive(pq1) << endl;
    cout << "pq2 is consecutive: " << isConsecutive(pq2) << endl;
    return 0;
}
