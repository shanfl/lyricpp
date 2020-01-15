#ifndef _MEM_CHECK_H_
#define _MEM_CHECK_H_

#include <new>                  // size_t/std::bad_alloc
#include <stdio.h>              // FILE



void* operator new(size_t size, const char* file, int line);
void* operator new[](size_t size, const char* file, int line);
void operator delete(void* ptr, const char* file, int line);
void operator delete[](void* ptr, const char* file, int line);

#ifdef _DEBUG
#define DEBUG_NEW1 new( __FILE__, __LINE__)
#define new DEBUG_NEW1

#endif

#endif