#include <psi/context/stack.hpp>

#include <utility>

namespace psi::context
{
    stack stack::allocate_pages(std::size_t count)
    {
        auto allocation = mmap_allocation::allocate_pages(count + 1);
        allocation.protect_pages(0, 1); // protect first page
        return stack(std::move(allocation));
    }

    char *stack::bottom() const
    {
        return (char *)((std::uintptr_t *)allocation_.end() - 1);
    }

    stack::stack(mmap_allocation allocation) : allocation_(std::move(allocation)) {}

}