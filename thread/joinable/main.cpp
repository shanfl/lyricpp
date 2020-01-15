#include<thread>
#include<chrono>
#include<iostream>

void fn()
{
    std::cout<<"-------------fn in"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<<"-------------fn exit"<<std::endl;
}

int main()
{
    int n = std::thread::hardware_concurrency();
    
    std::thread th(fn);
    std::cout<<"fn joinable is :" << th.joinable() << std::endl;
    th.join();
    std::cout<<"fn joinable is :" << th.joinable() << std::endl;
}