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
        cout << "���캯�� �� Test(int n) : n_(n)" << endl;
    }
    Test(const Test& other)
    {
        cout << "Test(const Test& other)" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
    void* operator new(size_t size)//��ͨ������ã���עΪ0
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
    void operator delete(void* p, size_t size)//��������Ǹ������delete���У���ô��������ġ�
    {
        cout << "void operator delete(void* p, size_t size)" << endl;
        free(p);
    }

    void* operator new(size_t size, void* p)//��һ��������ã���עΪ2
    {
        cout << "mark 2 : run" << endl;
        return p;
    }

    int n_;
};

void* operator new[](size_t size) {
    cout << "operator new[] , ȫ�ַ�test��������" << endl;
    void* p = malloc(size);
    return p;
}

void* operator new(size_t size) {
    cout << "operator new , ȫ�ַ�test��������" << endl;
    void* p = malloc(size);
    return p;
}

void operator delete[](void* p) {
    cout << "operator delete[] , ȫ�ַ�test�������� " << endl;
    free(p);
}

void operator delete(void* p) {
    cout << "operator delete , ȫ�ַ�test�������� " << endl;
    free(p);
}

int main(void)
{
    //��һ��֪ʶ��
    Test* p1 = new Test(100);    // new operator = operator new + ���캯���ĵ��� ���ñ�ע0
    delete p1;                  //delete = ���������ĵ���+operator delete

    //�ڶ���֪ʶ��
    char* str = new char[100]; //���ñ�ע3
    delete[] str;

    char* str2 = new char;
    delete str2;


    //������֪ʶ��
    char chunk[10];
    Test* p2 = new (chunk) Test(200);    //operator new(size_t, void *_Where)+���캯���ĵ���
                                         // placement new���������ڴ�+ ���캯���ĵ���
                                         //���ñ�ע2
    cout << p2->n_ << endl;
    p2->~Test();                        // ��ʽ����������������Ϊû�з����ڴ棬����ֱ�ӵ�����������
    return 0;
}