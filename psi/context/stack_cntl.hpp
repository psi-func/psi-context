#pragma once

#include <cstdint>

class args_list_builder
{
public:
    args_list_builder(void *top) : top_((uintptr_t *)top) {}

    void push(void *arg)
    {
        ++top_;
        *top_ = (uintptr_t)arg;
    }

private:
    uintptr_t *top_;
};

/**
 * @brief Stack growth down tha is why top decreased per push
 *
 */
class stack_cntl
{
    using word = std::uintptr_t;
    static const std::size_t kWordSize = sizeof(word);

public:
    stack_cntl(char *bottom) : top_(bottom) {}

    void align_rsp(std::size_t alignment)
    {
        std::size_t shift = (std::size_t)(top_ - kWordSize) % alignment;
        top_ -= shift;
    }

    void *top()
    {
        return top_;
    }

    stack_cntl &push(word value)
    {
        top_ -= kWordSize;
        *(word *)top_ = value;
        return *this;
    }

    stack_cntl &allocate(std::size_t bytes)
    {
        top_ -= bytes;
        return *this;
    }

private:
    char *top_;
};