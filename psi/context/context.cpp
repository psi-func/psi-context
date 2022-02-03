#include <psi/context/context.hpp>

#include <cstdint>

namespace psi::context
{
    exec_context::exec_context()
    {
    }

    exec_context::~exec_context()
    {
    }

    void exec_context::setup(mutable_memory_view stack, trampoline trampoline, void *arg)
    {
        cpu_ctx_.setup(stack, trampoline, arg);
    }

    static void trampoline_adaptor(void *arg)
    {
        trampoline_without_args t = (trampoline_without_args)arg;
        t();
    }

    void exec_context::setup(mutable_memory_view stack, trampoline_without_args trampoline)
    {
        setup(stack, trampoline_adaptor, (void *)trampoline);
    }

    void exec_context::switch_to(exec_context &target)
    {
        cpu_ctx_.switch_to(target.cpu_ctx_);
    }
}
