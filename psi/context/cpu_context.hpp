#pragma once

#include <psi/memory_view.hpp>
#include <psi/context/trampoline.hpp>

namespace psi::context
{
    struct cpu_context
    {
        void *rsp_; // stack pointer

        void setup(mutable_memory_view stack, trampoline trampoline, void *arg);

        void switch_to(cpu_context &target);
    };
}
