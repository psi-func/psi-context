#pragma once

#include <cstddef>
#include <cstdint>

#include <psi/memory_view.hpp>

namespace psi
{
    class mmap_allocation
    {
    public:
        mmap_allocation()
        {
            init();
        }

        ~mmap_allocation()
        {
            release();
        }

        static std::size_t page_size();

        static mmap_allocation allocate_pages(std::size_t count);

        //  MOVING constructors
        mmap_allocation(mmap_allocation &&that) noexcept;
        mmap_allocation &operator=(mmap_allocation &&that);

        /**
         * @brief Protect range of pages (cannot be modified/readed/executed)
         *
         * @param offset
         * @param count pages count
         */
        void protect_pages(std::size_t offset, std::size_t count);

        void release();

        const_memory_view view() const noexcept
        {
            return {start_, size_};
        }

        mutable_memory_view view() noexcept
        {
            return {start_, size_};
        }

        std::size_t size() const noexcept
        {
            return size_;
        }

        char *begin() const noexcept
        {
            return start_;
        }

        char *end() const noexcept
        {
            return start_ + size_;
        }

        mmap_allocation(const mmap_allocation &) = delete;
        mmap_allocation &operator=(const mmap_allocation &) = delete;

    private:
        mmap_allocation(char *start, std::size_t size) : start_(start), size_(size) {}

        void init();

    private:
        char *start_;
        std::size_t size_;
    };
}
