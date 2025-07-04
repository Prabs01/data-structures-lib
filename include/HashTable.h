#pragma once

#include<iostream>
#include"LinkedList.h"

template<typename K, typename V>
struct ChainNode{
    K key;
    V data;
    ChainNode *next;
    ChainNode(K k, V val):key(k), data(val), next(nullptr){};
};

template<typename K, typename V>
struct HashTableNode{
    int bcount; //Number of elements in block
    ChainNode<K, V> *next;
    HashTableNode(int bcnt):bcount(bcnt),next(nullptr){};
};

template<typename K>
struct Hash;

template<>
struct Hash<int>{
    static int get(int key, int tsize) {
        return key % tsize;
    }
};

template<>
struct Hash<std::string>{
    static int get(const std::string& key, int tsize) {
        int groupSize = 2;  // Let's group every 2 characters
        int sum = 0;

        for (size_t i = 0; i < key.length(); i += groupSize) {
            int groupValue = 0;

            // Process each group of size 2
            for (size_t j = 0; j < groupSize && (i + j) < key.length(); ++j) {
                groupValue = (groupValue * 100) + static_cast<int>(key[i + j]);
                // Multiply by 100 to preserve character positions in the group
            }

            sum += groupValue;
        }

        return sum % tsize;
    }
};

template<>
struct Hash<char>{
    static int get(char key, int tsize){
        return key % tsize;
    }
};

template<typename K, typename V> //type of key(K) and value(V)
class HashTable{
    int tsize; 
    int count;
    HashTableNode<K,V>** table;

    const float LOADFACTOR;
    
    public:
        HashTable(int size, float LoadFactor = 0.8):LOADFACTOR(LoadFactor){
            tsize = size / LOADFACTOR;
            count = 0;

            table = new HashTableNode<K,V>*[tsize];
            if(!table){
                std::cout<<"Memory error";
                exit(1);
            }

            for(int i =0; i<tsize; i++){
                table[i] = new HashTableNode<K,V>(0);
            }
        }

        ~HashTable(){
            for(int i =0;i<tsize;i++){
                HashTableNode<K,V>* bucket = table[i];

                if(bucket -> bcount == 0){
                    continue;
                }

                ChainNode<K,V>* ptr = bucket->next;

                while(ptr){
                    ChainNode<K,V>* temp = ptr;
                    ptr = ptr->next;
                    delete temp;
                }

                delete bucket;
            }
            delete[] table;
        }

        bool search(K key, V& data){
            int index = Hash<K>::get(key, tsize);

            ChainNode<K,V>* temp = table[index]->next;

            if(!temp){
                return false;
            }

            while(temp){
                if(temp -> key == key){
                    data = temp->data;
                    return true;
                }
                temp = temp->next;
            }

            return false;
        }

        void insert(K key, V data){
            int index = Hash<K>::get(key, tsize);

            HashTableNode<K,V>* bucket = table[index];

            ChainNode<K,V>* temp = new ChainNode<K,V>(key, data);

            if(bucket->bcount == 0){
                bucket->next = temp;
                bucket->bcount = 1;
                count += 1;
                return;
            }

            ChainNode<K,V>* ptr = bucket->next;

            while(ptr->next){
                if(ptr -> key == key){
                    ptr->data = data;
                    delete temp;
                    return;
                }
                ptr = ptr->next;
            }

            temp -> next = bucket -> next;
            bucket -> next = temp;
            bucket->bcount += 1;
            count ++;
        }

        bool remove(K key){
            int index = Hash<K>::get(key, tsize);

            HashTableNode<K,V>* bucket = table[index];

            if(bucket -> bcount == 0){
                std::cout<<"Key does not exist"<<std::endl;
                return false;
            }

            ChainNode<K,V>* ptr = table[index]->next;

            if(ptr->key == key){
                bucket ->next = ptr->next;
                delete ptr;
                bucket ->bcount -= 1;
                count --;
                return true;
            }

            while(ptr->next){
                if(ptr->next->key == key){
                    ChainNode<K,V>* temp = ptr->next;
                    ptr->next = temp ->next;
                    bucket->bcount--;
                    count--;
                    delete temp;
                    return true;
                }
                ptr = ptr->next;
            }

            std::cout<<"Key does not exist"<<std::endl;
            return false;
        }



        void display() const{
            for(int i = 0; i<tsize -1 ; i++){
                std::cout<<"Bucket "<< i <<"("<<table[i]->bcount<<"elements): ";

                if(table[i] -> bcount == 0){
                    std::cout<<"Empty"<<std::endl;
                    continue;
                }

                ChainNode<K,V>* ptr = table[i]->next;
                while(ptr){
                    std::cout<<"("<<ptr->key<<","<<ptr->data<<") -> ";
                    ptr = ptr->next;
                }
                std::cout<<"nullptr"<<std::endl;

            }
        }
 


};