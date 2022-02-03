#pragma once

#include <cstddef>
#include <cassert>

namespace psi
{

    /*
    SOME METAPROGRAMMING
    */
    template <bool isTrue, typename T, typename F>
    struct condition
    {
        using value_type = F;
    };

    template <typename T, typename F>
    struct condition<true, T, F>
    {
        using value_type = T;
    };

    template <bool isTrue, typename T, typename F>
    using condition_t = typename condition<isTrue, T, F>::value_type;

    /*
    memory view class
    */
    template <bool is_const>
    struct memory_view
    {
        using pointer = condition_t<is_const, const char *, char *>;

        memory_view(pointer start, std::size_t size) : start_(start),
                                                       size_(size)
        {
        }

        pointer data() const noexcept
        {
            return begin();
        }

        std::size_t size() const noexcept
        {
            return size_;
        }

        pointer begin() const noexcept
        {
            return start_;
        }

        pointer end() const noexcept
        {
            return start_ + size_;
        }

        pointer back() const noexcept
        {
            assert(size_ > 0);
            return end() - 1;
        }

        bool has_space() const noexcept
        {
            return size_ > 0;
        }

        bool is_valid() const noexcept
        {
            return start_ != nullptr;
        }

        void operator+=(std::size_t offset) noexcept
        {
            assert(offset <= size_);
            start_ += offset;
            size_ -= offset;
        }

    private:
        pointer start_;
        std::size_t size_;
    };

    using const_memory_view = memory_view<true>;
    using mutable_memory_view = memory_view<false>;

}