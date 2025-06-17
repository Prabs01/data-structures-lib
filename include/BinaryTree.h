#pragma once

#include<iostream>
#include"Queue.h"
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

    BinaryTreeNode<T>* insertHelper(BinaryTreeNode<T>* node , int val){
        if(!node) return new BinaryTreeNode<T>(val);
        
        if(val < node->data){
            node->left = insertHelper(node->left, val);
        }else{
            node->right = insertHelper(node->right, val);
        }
        return node;
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


    public:
        BinaryTree():root(nullptr){}

        ~BinaryTree(){
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
            root = insertHelper(root, data);
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

            Queue<BinaryTreeNode<T>*> nextLevel;
            BinaryTreeNode<T>* ptr = root;

            nextLevel.enQueue(root);

            while(!nextLevel.isEmpty()){
                ptr = nextLevel.deQueue();
                if(ptr){
                    std::cout<<ptr->data<<" ";
                    if(ptr->left) nextLevel.enQueue(ptr->left);
                    if(ptr->right) nextLevel.enQueue(ptr->right);
                } 
            }
            std::cout<<"\n";
        }


        void display() const{ 
    
            displayHelper(root);
        }

        
};
