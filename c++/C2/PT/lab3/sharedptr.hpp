#ifndef SHAREDPTR_H
#define SHAREDPTR_H
#include <stdint.h>
#include <stddef.h>
#include "log.hpp"


template<typename T>
class SharedPtr {
public:
    explicit SharedPtr()
        : pptr(nullptr), ref_cnt(nullptr)
    {
        TRACE() << "Created new shared pointer";
    }

    explicit SharedPtr(T ptr[])
        : pptr(ptr), ref_cnt(new int32_t)
    {
        (*ref_cnt) = 1;
        TRACE() << "Created new shared pointer with assignment constructor";
        LOG3() << ((pptr) ? pptr : "0x0") << ": " << *ref_cnt;
    }

    explicit SharedPtr(const SharedPtr& b)
        : pptr(b.pptr), ref_cnt(b.ref_cnt)
    {
        (*ref_cnt)++;
        TRACE() << "Created new shared pointer with copy constructor";
        LOG3() << ((pptr) ? pptr : "0x0") << ": " << *ref_cnt;
    }

   ~SharedPtr() {
        release();
    }

    void release() {
        if(!pptr && !ref_cnt) return;

        TRACE() << "Released shared pointer, " << (*ref_cnt)-1 << " references";
        LOG3() << ((pptr) ? pptr : "0x0") << ": " << (*ref_cnt) - 1;

        (*ref_cnt) -= 1;
        if(*ref_cnt <= 0) {
            drop();
        } else {
            pptr    = nullptr;
            ref_cnt = nullptr;
        }
    }

    void drop() {
        if(!pptr && !ref_cnt) return;
        TRACE() << "No references to memory at address "
                << std::hex << (uintptr_t) pptr << ", freing"
                << std::dec;
        LOG3() << pptr << ": free";

        if(pptr)    delete[] pptr;
        if(ref_cnt) delete   ref_cnt;
        pptr    = nullptr;
        ref_cnt = nullptr;
    }

    SharedPtr& operator = (const SharedPtr& b) {
        if(this == &b) return *this;
        LOG3() << "Assigning " << b.pptr << " instead of " << ((pptr) ? pptr : "0x0");

        release();

        ref_cnt = b.ref_cnt;
        pptr    = b.pptr;

        (*ref_cnt)++;

        LOG3() << ((pptr) ? pptr : "0x0") << ": " << *ref_cnt;
        return *this;
    }

    SharedPtr& operator = (T ptr[]) {
        set(ptr);
        return *this;
    }

    void set(T ptr[]) {
        TRACE() << "Assigning "
                << std::hex << (uintptr_t) ptr
                << " instead of " << (uintptr_t) pptr
                << std::dec;

        release();

        pptr    = ptr;
        ref_cnt = new int32_t;
        (*ref_cnt) = 1;

        LOG3() << ((pptr) ? pptr : "0x0") << ": " << *ref_cnt;
    }

    T* get() {
        return pptr;
    }

    const T* get() const {
        return pptr;
    }

    T& operator*() {
        return *pptr;
    }

    const T& operator*() const {
        return *pptr;
    }

    T& operator[](size_t index) {
        return pptr[index];
    }

    const T& operator[](size_t index) const {
        return pptr[index];
    }

    int32_t refs() const {
        return *ref_cnt;
    }

private:
    T*         pptr;
    int32_t*   ref_cnt;
};

#endif // SHAREDPTR_H
