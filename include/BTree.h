#include<iostream>
#include<vector>

template<typename T>
struct BTreeNode{
    std::vector<T> keys;
    std::vector<BTreeNode<T>*> children;
    bool isLeaf;

    BTreeNode(bool leaf):isLeaf(leaf){}

    void insert(T key){
        auto it = std::lower_bound(keys.begin(), keys.end(), key);

        keys.insert(it, key);
    }

    bool isFull(int t){
        return (keys.size() == (2*t)+1);
    }
};

template<typename T>
class BTree{
    int t;
    BTreeNode<T>* root;

    void displayHelper(BTreeNode<T>* node, int level) const {
        if (!node) return;

        std::cout << std::string(level * 4, ' ') << "|- ";

        for (const auto& key : node->keys)
            std::cout << key << " ";
        std::cout << "\n";

        for (BTreeNode<T>* childNode : node->children) {
            displayHelper(childNode, level + 1);
        }
    }
    void splitChild(BTreeNode<T>* parent, int i, BTreeNode<T>* y) {
        BTreeNode<T>* z = new BTreeNode<T>(y->isLeaf);

        for(int j = t; j < y->keys.size(); ++j)
            z->keys.push_back(y->keys[j]);

        T middleKey = y->keys[t-1];

        y->keys.resize(t-1);

        if (!y->isLeaf) {
            for (int j = t; j < y->children.size(); ++j)
                z->children.push_back(y->children[j]);
            y->children.resize(t);
        }

        parent->children.insert(parent->children.begin() + i + 1, z);
        parent->keys.insert(parent->keys.begin() + i, middleKey);
    }


    void insertNonFull(BTreeNode<T>* node, T val){
        if (node->isLeaf) {
            node->insert(val);
        } else {
            // Find child to recurse
            int i = 0;
            while (i < node->keys.size() && val > node->keys[i]) i++;

            if (node->children[i]->isFull(t)) {
                splitChild(node, i, node->children[i]);
                if (val > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], val);
        }
        
    }

    public:
        BTree(int min_degree = 5):root(nullptr),t(min_degree){}

        void insert(T val){
            if (!root) {
                root = new BTreeNode<T>(true);
                root->keys.push_back(val);
                return;
            }

            if (root->isFull(t)) {
                BTreeNode<T>* s = new BTreeNode<T>(false);
                s->children.push_back(root);
                splitChild(s, 0, root);
                root = s;
            }
            insertNonFull(root, val);

        }

        void display() const{
            displayHelper(root, 0);
        }

};