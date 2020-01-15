#include "memcheck.h"
//#include <afx.h>
#include <new>                  // std::bad_alloc/nothrow_t
#undef new

void* operator new(size_t size, const char* file, int line)
{
    //return ::operator new(size, _NORMAL_BLOCK, fileName, line);
    return malloc(size);
}
