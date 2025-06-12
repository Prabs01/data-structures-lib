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

        bool search(T value){
            //to be implemented
            return false;
        }

        bool deleteValue(T value){
            // to be implemented
            return false;
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