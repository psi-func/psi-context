#pragma once

#include <psi/mmap_allocator.hpp>
#include <psi/memory_view.hpp>

namespace psi::context
{

    class stack
    {
    public:
        stack() = default;

        static stack allocate_pages(std::size_t count);

        stack(stack &&that) = default;
        stack &operator=(stack &&that) = default;

        char *bottom() const;

        std::size_t size() const
        {
            return allocation_.size();
        }

        mutable_memory_view view()
        {
            return allocation_.view();
        }

    private:
        stack(mmap_allocation allocation);

    private:
        mmap_allocation allocation_;
    };
}
