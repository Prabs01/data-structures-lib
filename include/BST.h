#include"BinaryTree.h"


template<typename T>
class BST{
    private:
        BinaryTreeNode<T>* root;

        void insertHelper(BinaryTreeNode<T>*& node, int val){
            if(!node){
                node = new BinaryTreeNode<T>(val);
            }else{
                if(val < node->data){
                    insertHelper(node->left,val);
                }else{
                    insertHelper(node->right,val);
                }
            }
        }

        BinaryTreeNode<T>* searchHelper(BinaryTreeNode<T>* node, int val){
            if(!node || node->data == val) return node;

            if(val < node->data){
                searchHelper(node->left, val);
            }else{
                searchHelper(node->right, val);
            }
        }

        int heightHelper(BinaryTreeNode<T>* node){
            if(!node) return 0;
            int leftHeight = heightHelper(node->left);
            int rightHeight = heightHelper(node->right);

            if(leftHeight > rightHeight){
                return leftHeight + 1;
            }
            else{
                return rightHeight + 1;
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

        void removeHelper(BinaryTreeNode<T>*& node, int val){
            if(!node){
                throw std::underflow_error("value not found");
            }
            else if(val < node->data){
                removeHelper(node->left, val);
            }else if(val > node->data){
                removeHelper(node->right, val);
            }   
            else if(node->right && node->left){
                BinaryTreeNode<T>* temp = findLargestHelper(node->left);
                node->data = temp->data;
                removeHelper(node->left,temp->data);
            }
            else{
                BinaryTreeNode<T>* temp = node;
                if(!node->left && !node->right){
                    node = nullptr;
                }
                else if(node->left){
                    node = node->left;
                }else{
                    node = node->right;
                }

                delete temp;
            }
        }

        BinaryTreeNode<T>* findLargestHelper(BinaryTreeNode<T>* node){
            if(!node -> right){
                return node;
            }
            return findLargestHelper(node->right);
            
        }

    public:
        BST(){
            root = nullptr;
        }

        void insert(int val){
            insertHelper(root, val);
        }

        BinaryTreeNode<T>* search(int val){
            return searchHelper(root, val);
        }

        void display() const{
            displayHelper(root);
        }

        void remove(int val){
            removeHelper(root, val);
        }

};