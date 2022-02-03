#include <psi/context/context.hpp>
#include <psi/context/stack.hpp>

#include <iostream>

using psi::context::exec_context;
using psi::context::stack;

exec_context main_ctx;
auto stack = stack::allocate_pages(8);

exec_context child_ctx;

void child_routine()
{
    std::cout << "child_ctx" << std::endl;

    child_ctx.switch_to(main_ctx);

    std::cout << "child_ctx" << std::endl;

    child_ctx.switch_to(main_ctx);
}

int main()
{
    child_ctx.setup(stack.view(), child_routine);

    std::cout << "Parent" << std::endl;

    main_ctx.switch_to(child_ctx);

    std::cout << "Parent" << std::endl;
    main_ctx.switch_to(child_ctx);
    std::cout << "Parent" << std::endl;

    return 0;
}