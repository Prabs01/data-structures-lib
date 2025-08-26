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
        return (keys.size() == (2*t - 1));
    }
};

template<typename T>
class BTree{
    int t;
    BTreeNode<T>* root;

    void displayHelper(BTreeNode<T>* node, int level) const {
        if (!node) return;

        std::cout << std::string(level * 4, ' ')
          << (node->isLeaf ? "[Leaf] " : "[Internal] ")
          << "|- ";
        for (const auto& key : node->keys)
            std::cout << key << " ";
        
        std::cout << " (" << node->children.size() << " children)";
        std::cout << "\n";
       

        if (!node->isLeaf) {
            for (BTreeNode<T>* childNode : node->children) {
                displayHelper(childNode, level + 1);
            }
        }
    }
    void splitChild(BTreeNode<T>* parent, int i, BTreeNode<T>* fullChild) {

        // fullChild has 2*t - 1 keys before split
        BTreeNode<T>* z = new BTreeNode<T>(fullChild->isLeaf);

        // Move last t-1 keys to z
        for (int j = 0; j < t - 1; j++)
            z->keys.push_back(fullChild->keys[j + t]);

        // Move last t children to z if not leaf
        if (!fullChild->isLeaf) {
            for (int j = 0; j < t; j++)
                z->children.push_back(fullChild->children[j + t]);
        }

        // Reduce size of fullChild
        fullChild->keys.resize(t - 1);
        if (!fullChild->isLeaf)
            fullChild->children.resize(t);

        // Insert new child into parent
        parent->children.insert(parent->children.begin() + i + 1, z);

        // Move median key up to parent
        parent->keys.insert(parent->keys.begin() + i, fullChild->keys[t - 1]);
    }

    void insertNonFull(BTreeNode<T>* node, T key) {
        int i = node->keys.size() - 1;

        if (node->isLeaf) {
            // Insert key into leaf at correct position
            node->keys.insert(
                std::upper_bound(node->keys.begin(), node->keys.end(), key),
                key
            );
        } else {
            // Find child to insert into
            while (i >= 0 && key < node->keys[i])
                i--;

            i++; // Move to correct child index

            // If child is full, split first
            if (node->children[i]->isFull(t)) {
                splitChild(node, i, node->children[i]);
                // After split, decide which child to descend into
                if (key > node->keys[i])
                    i++;
            }

            insertNonFull(node->children[i], key);
        }
    }


    public:
        BTree(int min_degree):root(nullptr),t(min_degree){}

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