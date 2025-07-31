#include"LinkedList.h"

int main(){
    LinkedList<int> l;

    l.insert(5);
    l.insert(4);
    l.insert(2);
    l.insert(3);
    l.insert(1);

    l.display();

    l.sort();

    l.display();

    return 0;

}