#include"HashTable.h"

int main(){
    // Small table size to force collisions
    HashTable<std::string, int> ht(4);

    // Insert keys that will likely collide
    ht.insert("apple", 10);
    ht.insert("elppa", 15);  // Same letters, different order → good chance of collision with basic hash
    ht.insert("banana", 20);
    ht.insert("ananab", 22); // Reversed → try to collide
    ht.insert("orange", 30);

    // Update existing key
    ht.insert("banana", 25);

    // Search for keys
    int value;

    if (ht.search("apple", value)) {
        std::cout << "apple: " << value << std::endl;
    } else {
        std::cout << "apple not found" << std::endl;
    }

    if (ht.search("elppa", value)) {
        std::cout << "elppa: " << value << std::endl;
    } else {
        std::cout << "elppa not found" << std::endl;
    }

    if (ht.search("banana", value)) {
        std::cout << "banana: " << value << std::endl;
    } else {
        std::cout << "banana not found" << std::endl;
    }

    if (ht.search("ananab", value)) {
        std::cout << "ananab: " << value << std::endl;
    } else {
        std::cout << "ananab not found" << std::endl;
    }

    if (ht.search("orange", value)) {
        std::cout << "orange: " << value << std::endl;
    } else {
        std::cout << "orange not found" << std::endl;
    }

    if (ht.search("grape", value)) {
        std::cout << "grape: " << value << std::endl;
    } else {
        std::cout << "grape not found" << std::endl;
    }

    // Display the full hash table to visually check chains
    ht.display();

    if(ht.remove("banana")){
        std::cout<<"banana removed"<<std::endl;
    }

    if(ht.remove("orange")){
        std::cout<<"orange removed"<<std::endl;
    }

    ht.remove("mango");

    ht.display();


    return 0;

}