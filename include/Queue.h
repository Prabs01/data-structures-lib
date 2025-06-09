#pragma once

#include<iostream>
#include"LinkedList.h"

template <typename T>
class Queue{
    Node<T>* front;
    Node<T>* rear;

    public:
        Queue():front(nullptr),rear(nullptr){}

        ~Queue(){
            while(!isEmpty()){
                deQueue();
            }
        }

        void enQueue(T data){
            if(isEmpty()){
                rear = new Node<T>(data);
                front = rear;
                return;
            }
            Node<T>* temp = new Node<T>(data);
            rear->next = temp;
            rear = rear->next;
        }

        T deQueue(){
            if(isEmpty()){
                throw std::underflow_error("Queue empty");
            }
            T data = front -> data;
            Node<T>* temp = front;
            front = front->next;

            if(!front){
                rear = nullptr;
            }

            delete temp;
            return data;
        }

        T getFront(){
            if(isEmpty()){
                throw std::underflow_error("Queue empty");
            }
            return front->data;
        }

        int size(){
            Node<T>* ptr = front;
            int size = 0;
            while(ptr){
                ptr = ptr->next;
                size++;
            }
            return size;
        }

        bool isEmpty(){
            return (!front && !rear);
        }
};