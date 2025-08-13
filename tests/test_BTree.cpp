#include"BTree.h"

int main(){
    BTree<int> btree(3); // t = 3

    btree.insert(1);
    btree.insert(2);
    btree.insert(3);
    btree.insert(4);
    btree.insert(7);
    btree.insert(8);
    btree.insert(15);
    btree.insert(17);
    btree.insert(25);
    btree.display();
    // Output should show a balanced B-Tree with internal splits properly done



    return 0;
}