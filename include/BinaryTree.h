#pragma once

#include<iostream>
#include"Queue.h"
#include"Stack.h"
#include<vector>
#include<string>

template<typename T>
struct BinaryTreeNode{
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(T val):data(val),left(nullptr),right(nullptr){}
};


template <typename T>
class BinaryTree{
    BinaryTreeNode<T>* root;

    void preOrderTraversalHelper(BinaryTreeNode<T>* node){
        if(node){
            std::cout<<node->data<<" ";
            preOrderTraversalHelper(node->left);
            preOrderTraversalHelper(node->right);
        }
    }

    void inOrderTraversalHelper(BinaryTreeNode<T>* node){
        if(node){
            inOrderTraversalHelper(node->left);
            std::cout<<node->data<<" ";
            inOrderTraversalHelper(node->right);
        }
    }

    void postOrderTraversalHelper(BinaryTreeNode<T>* node){
        if(node){
            postOrderTraversalHelper(node->left);
            postOrderTraversalHelper(node->right);
            std::cout<<node->data<<" ";
        }
    }


    void displayHelper(BinaryTreeNode<T>* node, std::string prefix = "", bool isLeft = true) const {
        if (!node) return;

        if (node->right)
            displayHelper(node->right, prefix + (isLeft ? "│   " : "    "), false);

        std::cout << prefix;
        std::cout << (isLeft ? "└── " : "┌── ");
        std::cout << node->data << std::endl;

        if (node->left)
            displayHelper(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }

    bool searchHelper(BinaryTreeNode<T>* node, T value) const{
        if(!node) return false;

        if(node->data == value) return true;

        return searchHelper(node->left, value) || searchHelper(node->right, value);
    }

    bool isLeaf(BinaryTreeNode<T>* node) const{
        return (node && (!node->left) && (!node->right));
    }

    int sizeHelper(BinaryTreeNode<T>* node) const{
        if(!node) return 0;

        return (sizeHelper(node->left) + sizeHelper(node->right) + 1 );
    }

    void clearHelper(BinaryTreeNode<T>* node){
        if(!node) return;

        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

    int depthHelper(BinaryTreeNode<T>* node) const{
        if(!node) return 0;

        int leftDepth = depthHelper(node->left);
        int rightDepth = depthHelper(node->right);

        return (leftDepth > rightDepth)?leftDepth + 1 : rightDepth + 1;
    }
 

    public:
        BinaryTree():root(nullptr){}

        BinaryTree(const std::vector<T> values){
            if(values.empty()) return;

            root = new BinaryTreeNode<T>(values[0]);

            BinaryTreeNode<T>* ptr = root;
            
            Queue<BinaryTreeNode<T>*> q;
            q.enQueue(root);

            int i = 1;

            while(i<values.size()){
                ptr = q.deQueue();
                
                ptr->left = new BinaryTreeNode<T>(values[i++]);
                q.enQueue(ptr->left);

                if(i>=values.size()) break;

                ptr->right = new BinaryTreeNode<T>(values[i++]);
                q.enQueue(ptr->right);
            }
        }

        ~BinaryTree(){
            clear();
        }

        void initializeRoot(T data){
            if(root){
                std::cout<<"Root already initialized"<<std::endl;
                return;
            }
            root = new BinaryTreeNode<T>(data);
        }

        void insertLeft(T data){
            if(!root){
                std::cout<<"Root node not initialized"<<std::endl;
                return;
            }
            BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(data);
            if(!root->left){
                root->left = newNode;
            }else{
                std::cout<<"Left branch already occupied "<<std::endl;
            }

        }

        void insertRight(T data){
            if(!root){
                std::cout<<"Root node not initialized"<<std::endl;
                return;
            }
            BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(data);
            if(!root->right){
                root->right = newNode;
            }else{
                std::cout<<"Right branch already occupied "<<std::endl;
            }

        }

        void insert(T data){
            if(!root){
                root = new BinaryTreeNode<T>(data);
                return;
            }

            Queue<BinaryTreeNode<T>*> q;
            BinaryTreeNode<T>* ptr = root;
            q.enQueue(root);

            while(!q.isEmpty()){
                ptr = q.deQueue();

                if(!ptr->left){
                    ptr->left = new BinaryTreeNode<T>(data);
                    return;
                }else if(!ptr->right){
                    ptr->right = new BinaryTreeNode<T>(data);
                    return;
                }

                q.enQueue(ptr->left);
                q.enQueue(ptr->right);
            }
        }

        void preOrderTraversal(){
            preOrderTraversalHelper(root);
            std::cout<<"\n";
        }

        void inOrderTraversal(){
            inOrderTraversalHelper(root);
            std::cout<<"\n";
        }

        void postOrderTraversal(){
            postOrderTraversalHelper(root);
            std::cout<<"\n";
        }

        void levelOrderTraversal(){
            if(!root) return;

            Queue<BinaryTreeNode<T>*> q;
            BinaryTreeNode<T>* ptr = root;

            q.enQueue(root);

            while(!q.isEmpty()){
                ptr = q.deQueue();
                if(ptr){
                    std::cout<<ptr->data<<" ";
                    if(ptr->left) q.enQueue(ptr->left);
                    if(ptr->right) q.enQueue(ptr->right);
                } 
            }
            std::cout<<"\n";
        }

        void levelOrderTraversalInReverse(){
            if(!root) return;

            Stack<T> s;
            Queue<BinaryTreeNode<T>*> q;

            BinaryTreeNode<T>* ptr = root;

            q.enQueue(root);

            while(!q.isEmpty()){
                ptr = q.deQueue();

                if(ptr){
                    if(ptr->right) q.enQueue(ptr->right); // enqueue in reverse so that the stack corrects it
                    if(ptr->left) q.enQueue(ptr->left);

                    s.push(ptr->data);
                }

            }
            s.display();
        }

        void display() const{ 
    
            displayHelper(root);
        }

        bool search(T value) const{
            return searchHelper(root, value);
        }

        int depth() const{
            return depthHelper(root);
        }

        int size() const{
            return sizeHelper(root);
        }

        void clear(){
            clearHelper(root);
            root = nullptr;
        }

        
};

template<typename T>
class BST{
    private:
        BinaryTreeNode<T>* root;

    public:
        BST(){
            root = nullptr;
        }

        void insertNode(T data){
            BinaryTreeNode<T>* node(data);

            if(!root){
                root = node;
                return;
            } 

           
        }
};
