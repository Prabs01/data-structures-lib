#include"BinaryTree.h"



template<typename T>
BinaryTreeNode<T>* buildTree(const std::vector<T>& values) {
    if(values.empty()) return nullptr;


    BinaryTreeNode<T>* root = new BinaryTreeNode<T>(values[0]); 

    BinaryTreeNode<T>* ptr = root;
    Queue<BinaryTreeNode<T>*> q;
    q.enQueue(root);

    int i = 1;

    while(i<values.size()){
        ptr = q.deQueue();


        ptr->left = new BinaryTreeNode<T>(values[i++]);
        q.enQueue(ptr->left);


        if(i >= values.size()) break;

        
        ptr->right = new BinaryTreeNode<T>(values[i++]);
        q.enQueue(ptr->right);
    }

    return root;
}

//find maximum element in a binary tree
int findMax(BinaryTreeNode<int>* n){
    int max = 0;

    if(n){
        int leftMax = n->left?findMax(n->left):0;
        int rightMax = n->right?findMax(n->right):0;

        max = leftMax>rightMax?leftMax:rightMax;

        if(n->data >max){
            return n->data;
        }
    }
    
    return max;
};


//search a element
bool search(BinaryTreeNode<int>* n, int value){
    if(!n) return false;

    if(n -> data == value) return true;

    bool isInLeft = search(n->left, value);
    bool isInRight = search(n->right, value);

    return (isInLeft || isInRight);
}

int main(){
    std::vector<int> values = {2,3,4,5,9,6,7,3};
    BinaryTreeNode<int>* root = buildTree(values);

    std::cout<<"max = "<<findMax(root)<<std::endl;

    int x = 1;
    std::cout<<"is "<<x<<" present?"<<(search(root,x)?"Yes":"No")<<std::endl;

    x = 9;
    std::cout<<"is "<<x<<" present?"<<(search(root,x)?"Yes":"No")<<std::endl;

    return 0;
}