#include <psi/context/cpu_context.hpp>
#include <psi/context/stack_cntl.hpp>

namespace psi::context
{

    extern "C" void SwitchContext(void *from_rsp, void *to_rsp);

    struct stack_calle_saved_context
    {
        void *rbp;
        void *rbx;

        void *r12;
        void *r13;
        void *r14;
        void *r15;

        void *rip;
    };

    // https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/
    static void cpu_trampoline(void *, void *, void *, void *, void *, void *, void *arg1, void *arg2)
    {
        trampoline t = (trampoline)arg1;
        t(arg2);
    }

    static void *setup_stack(mutable_memory_view stack, trampoline trampoline, void *arg)
    {
        // https://eli.thegreenplace.net/2011/02/04/where-the-top-of-the-stack-is-on-x86/
        stack_cntl builder(stack.back());

        builder.allocate(sizeof(uintptr_t) * 3);

        builder.align_rsp(16);

        args_list_builder args(builder.top());
        args.push((void *)trampoline);
        args.push(arg);

        builder.allocate(sizeof(stack_calle_saved_context));

        auto *stack_saved_context = (stack_calle_saved_context *)builder.top();
        stack_saved_context->rip = (void *)cpu_trampoline;

        return stack_saved_context;
    }

    void cpu_context::setup(mutable_memory_view stack, trampoline trampoline, void *arg)
    {
        rsp_ = setup_stack(stack, trampoline, arg);
    }

    void cpu_context::switch_to(cpu_context &target)
    {
        SwitchContext(&rsp_, &target.rsp_);
    }
}
