#include"BinaryTree.h"

int main(){

    //TEST 1
    
    BinaryTree<int> tree;
    tree.initializeRoot(1);

    tree.inOrderTraversal();

    tree.insertLeft(2);
    tree.insertRight(3);


    tree.inOrderTraversal();
    tree.preOrderTraversal();
    tree.postOrderTraversal();
    tree.levelOrderTraversal();
    tree.levelOrderTraversalInReverse();



    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    tree.insert(8);
    tree.levelOrderTraversal();

    tree.levelOrderTraversalInReverse();

    int x = 1;
    std::cout<<"is "<<x<<" present?"<<(tree.search(x)?"Yes":"No")<<std::endl;

    x = 9;
    std::cout<<"is "<<x<<" present?"<<(tree.search(x)?"Yes":"No")<<std::endl;

    

    tree.display();

    std::cout<<"Size is "<<tree.size()<<std::endl;
    std::cout<<"depth is "<<tree.depth()<<std::endl;

    tree.insert(9);
    tree.insert(10);

    std::cout<<"Size is "<<tree.size()<<std::endl;
    std::cout<<"depth is "<<tree.depth()<<std::endl;


    tree.clear();

    tree.display();

    //#####################
    //TEST 2
    std::vector<int> values = {1,2,3,4,5,6};
    BinaryTree<int> tree2(values);

    tree2.display();

    std::cout<<"Size is "<<tree2.size()<<std::endl;
    std::cout<<"depth is "<<tree2.depth()<<std::endl;

}