#include<iostream>
#include"Queue.h"

using namespace std;



int main(){

    Queue<int> q;  // Allows storing 3 elements because of 1-slot gap

    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;
    cout << "Initial size = " << q.size() << endl;

    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);

    cout << "After enqueueing 10, 20, 30:" << endl;
    cout << "Front = " << q.getFront() << endl;
    cout << "Size = " << q.size() << endl;

    cout << "Trying to enqueue 40 (should overflow):" << endl;
    q.enQueue(40);

    cout << "Dequeuing twice..." << endl;
    cout << "Dequeue -> " << q.deQueue() << endl;
    cout << "Dequeue -> " << q.deQueue() << endl;

    cout << "Size = " << q.size() << endl;

    cout << "Enqueueing 50, 60..." << endl;
    q.enQueue(50);
    q.enQueue(60);  // should now wrap around

    cout << "Front = " << q.getFront() << endl;
    cout << "Dequeue -> " << q.deQueue() << endl;
    cout << "Dequeue -> " << q.deQueue() << endl;
    cout << "Dequeue -> " << q.deQueue() << endl;

    cout << "Dequeue again (should underflow):" << endl;
    q.deQueue();

    
}