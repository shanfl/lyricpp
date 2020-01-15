#if 0
#include <iostream>
//#include "memcheck.h"

int main()
{
    int* p = new int[20];
    delete []p;
}
#endif

#include <iostream>
using namespace std;

class Test
{
public:
    Test(int n) : n_(n)
    {
        cout << "构造函数 ： Test(int n) : n_(n)" << endl;
    }
    Test(const Test& other)
    {
        cout << "Test(const Test& other)" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
    void* operator new(size_t size)//普通情况调用，标注为0
    {
        cout << "mark 0 : void* operator new(size_t size)" << endl;
        void* p = malloc(size);
        return p;
    }
    void operator delete(void* p)
    {
        cout << "void operator delete(void* p)" << endl;
        free(p);
    }
    void operator delete(void* p, size_t size)//如果上面那个和这个delete都有，那么调用上面的。
    {
        cout << "void operator delete(void* p, size_t size)" << endl;
        free(p);
    }

    void* operator new(size_t size, void* p)//另一种情况调用，标注为2
    {
        cout << "mark 2 : run" << endl;
        return p;
    }

    int n_;
};

void* operator new[](size_t size) {
    cout << "operator new[] , 全局非test类调用这个" << endl;
    void* p = malloc(size);
    return p;
}

void* operator new(size_t size) {
    cout << "operator new , 全局非test类调用这个" << endl;
    void* p = malloc(size);
    return p;
}

void operator delete[](void* p) {
    cout << "operator delete[] , 全局非test类调用这个 " << endl;
    free(p);
}

void operator delete(void* p) {
    cout << "operator delete , 全局非test类调用这个 " << endl;
    free(p);
}

int main(void)
{
    //第一个知识点
    Test* p1 = new Test(100);    // new operator = operator new + 构造函数的调用 调用标注0
    delete p1;                  //delete = 析构函数的调用+operator delete

    //第二个知识点
    char* str = new char[100]; //调用标注3
    delete[] str;

    char* str2 = new char;
    delete str2;


    //第三个知识点
    char chunk[10];
    Test* p2 = new (chunk) Test(200);    //operator new(size_t, void *_Where)+构造函数的调用
                                         // placement new，不分配内存+ 构造函数的调用
                                         //调用标注2
    cout << p2->n_ << endl;
    p2->~Test();                        // 显式调用析构函数，因为没有分配内存，所以直接调用析构函数
    return 0;
}