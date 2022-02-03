#pragma once

#include <psi/context/cpu_context.hpp>
#include <psi/context/stack_cntl.hpp>

#include <psi/memory_view.hpp>

#include <cstddef>
#include <cstdint>

namespace psi::context
{
    struct exec_context
    {
        cpu_context cpu_ctx_;

        exec_context();
        ~exec_context();

        void setup(mutable_memory_view stack, trampoline trampoline, void *arg);

        void setup(mutable_memory_view stack, trampoline_without_args trampoline);

        void switch_to(exec_context &target);
    };
}
