#pragma once

#include<iostream>
#include <stdexcept> 

template <typename T>
struct Node{
    T data;
    Node* next;
    Node(T val):data(val),next(nullptr){}
};

template <typename T>
class LinkedList{
    Node<T>* head;


    Node<T>* mergeSort(Node<T>* head1){

        if (!head1 || !head1->next) return head1;

        Node<T>* mid = getMid(head1);
        Node<T>* rightHead1 = mid->next;
        mid->next = nullptr;  // break list

        Node<T>* leftSorted = mergeSort(head1);
        Node<T>* rightSorted = mergeSort(rightHead1);

        return merge(leftSorted, rightSorted);

    }

    Node<T>* merge(Node<T>* left,Node<T>* right){
        if (!left) return right;
        if (!right) return left;

        Node<T>* result = nullptr;
        if (left->data < right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }
        return result;
    }

    Node<T>* getMid(Node<T>* head1) {
        if (!head1 || !head1->next) return head1;
        Node<T>* slow = head1;
        Node<T>* fast = head1->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    public:
        LinkedList():head(nullptr){}

        ~LinkedList(){
            clear();
        }

        void insert(T data){
            Node<T>* temp = new Node<T>(data);

            if(!temp){
                std::cout<<"Error allocating memory"<<std::endl;
                return;
            }
            
            if(head == nullptr){
                head = temp;
                return;
            }
            Node<T>* ptr = head;

            while(ptr->next){
                ptr = ptr->next;
            }
            ptr ->next = temp;
        }

        void insertAtHead(T data){
            Node<T>* temp = new Node<T>(data);

            if(!temp){
                std::cout<<"Error allocating memory"<<std::endl;
                return;
            }

            if(head == nullptr){
                head = temp;
                return;
            }

            temp -> next = head;
            head = temp;
        }

        void sort(){
            head = mergeSort(head);
        }

        bool search(T value){
            //to be implemented
            return false;
        }

        bool deleteValue(T value){
            // to be implemented
            return false;
        }

        Node<T>* getHead(){
            return head;
        }

        T removeFromFront(){
            if(isEmpty()){
                throw std::underflow_error("List empty");
            }
            T data = head->data;
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return data;
        }

        T getFront() const{
            return head->data;
        }

        bool isEmpty() const{
            return (head == nullptr);
        }

        void display() const{
            Node<T>* ptr = head;
            while(ptr){
                std::cout<<ptr->data<<" ";
                ptr = ptr->next;
            }
            std::cout<<"\n";
        }
        
        int size() const{
            Node<T>* ptr = head;
            int size = 0;
            while(ptr){
                ptr= ptr->next;
                size++;
            }
            return size;
        }

        void clear(){
            while(!isEmpty()){
                removeFromFront();
            }
        }


};