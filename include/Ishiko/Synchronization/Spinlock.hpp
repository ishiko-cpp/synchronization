// SPDX-FileCopyrightText: 2005-2025 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_SYNCHRONIZATION_SPINLOCK_HPP
#define GUARD_ISHIKO_CPP_SYNCHRONIZATION_SPINLOCK_HPP

#include <atomic>

namespace Ishiko
{
    class Spinlock
    {
    public:
        Spinlock();
        Spinlock(const Spinlock& other) = delete;

        void acquire();
        void release();

    private:
        std::atomic_flag m_lock = ATOMIC_FLAG_INIT;
    };

}

#endif
