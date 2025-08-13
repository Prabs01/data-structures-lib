#include"BST.h"

int main(){

    BST<int> bst;

    bst.insert(23);
    bst.insert(18);
    bst.insert(12);
    bst.insert(44);
    bst.insert(35);
    bst.insert(52);
    bst.insert(20);
    bst.insert(19);
    bst.insert(22);

    bst.display();

    bst.remove(23);
    bst.display();


    return 0;
}