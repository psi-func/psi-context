#include <psi/mmap_allocator.hpp>

#include <iostream>

#include <sys/mman.h>

namespace psi
{

    // some defaults
    static const std::size_t kPageSize = 4096;

    static std::size_t PAGES_TO_BYTES(std::size_t count)
    {
        return kPageSize * count;
    }

    //////////////////////////////////////////////////////
    /////////// MMAP_ALLOCATION //////////////////////////
    std::size_t mmap_allocation::page_size()
    {
        return kPageSize;
    }

    mmap_allocation mmap_allocation::allocate_pages(std::size_t count)
    {
        std::size_t size = PAGES_TO_BYTES(count);

        void *start = mmap(/*adr*/ nullptr,
                           /*length*/ size,
                           /*protections*/ PROT_READ | PROT_WRITE,
                           /*flags */ MAP_PRIVATE | MAP_ANONYMOUS,
                           /*fd*/ -1, /*ofset*/ 0);

        if (start == MAP_FAILED)
        {
            // crush program
            std::cerr << "Cannot allocate " << count << " pages" << std::endl;
            exit(-1);
        }

        return mmap_allocation((char *)start, size);
    }

    void mmap_allocation::protect_pages(std::size_t offset, std::size_t count)
    {
        // full deny access
        int ret = mprotect(/*addr*/ (void *)(start_ + PAGES_TO_BYTES(offset)),
                           /*size*/ PAGES_TO_BYTES(count),
                           /*prot*/ PROT_NONE);

        if (ret == -1)
        {
            std::cerr << "Cannot protect pages [ " << offset << "," << offset + count << " ]" << std::endl;
            exit(-1);
        }
    }

    void mmap_allocation::release()
    {
        if (start_ != nullptr)
        {
            int ret = munmap(start_, size_);
            if (ret == -1)
            {
                std::cerr << "Cannot release mapped pages" << std::endl;
                exit(-1);
            }
        }
    }

    void mmap_allocation::init()
    {
        start_ = nullptr;
        size_ = 0;
    }

    ////////////////////////////////////////////////////////////////////////
    //////////////////////// MOVE SEMANTICS ////////////////////////////////
    mmap_allocation::mmap_allocation(mmap_allocation &&that) noexcept
    {
        start_ = that.start_;
        size_ = that.size_;
        that.init();
    }

    mmap_allocation &mmap_allocation::operator=(mmap_allocation &&that)
    {
        release();
        start_ = that.start_;
        size_ = that.size_;
        that.init();
        return *this;
    }

}