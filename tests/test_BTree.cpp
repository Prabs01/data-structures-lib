#include"BTree.h"

int main(){
    BTree<int> tree(3); // min degree t = 3

    std::vector<int> values = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int v : values) {
        tree.insert(v);
        tree.display();
    }




    return 0;
}