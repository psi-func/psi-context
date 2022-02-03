#pragma once

namespace psi::context
{
    using trampoline = void (*)(void *arg);
    using trampoline_without_args = void (*)();
}