#include"BinaryTree.h"

int main(){
    BinaryTree<int> tree;
    tree.initializeRoot(1);

    tree.inOrderTraversal();

    tree.insertLeft(2);
    tree.insertRight(3);


    tree.inOrderTraversal();
    tree.preOrderTraversal();
    tree.postOrderTraversal();
    tree.levelOrderTraversal();

}