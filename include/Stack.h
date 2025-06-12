#pragma once

#include"LinkedList.h"


template<typename T>
class Stack{
    LinkedList<T> container;

    public:
        Stack() = default;

        ~Stack() = default;

        void push(T data){
            container.insertAtHead(data);
        }

        T pop(){
            try{
                return container.removeFromFront();
            } catch(const std::underflow_error& e){
                std::cout<<"Stack underflow: "<<e.what()<<std::endl;
                throw;
            }
        }

        T peek() const{
            return container.getFront();
        }

        bool isEmpty() const{
            return container.isEmpty();
        }

        int size() const{
            return container.size();
        }

        void clear(){
            container.clear();
        }

        void display() const{
            container.display();
        }

};