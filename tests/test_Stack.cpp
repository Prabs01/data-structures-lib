#include"Stack.h"

int main(){
    Stack<int> s;

    std::cout<<"Is Empty? "<<s.isEmpty()<<std::endl;
    std::cout<<"Size = "<<s.size()<<std::endl;

    s.push(1);
    s.push(2);
    s.display();

    std::cout<<"Size = "<<s.size()<<std::endl;

    std::cout<<"Top = "<<s.peek()<<std::endl;

    std::cout<<s.pop()<<std::endl;
    std::cout<<"Top = "<<s.peek()<<std::endl;


    s.pop();
    s.pop();
    try{
        s.pop();
    }catch(const std::underflow_error& e){
        
    }
    

}