// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "Spinlock.hpp"

using namespace Ishiko;

Spinlock::Spinlock()
{
}

void Spinlock::acquire()
{
    while (m_lock.test_and_set(std::memory_order_acquire))
    {
    }
}

void Spinlock::release()
{
    m_lock.clear(std::memory_order_release);
}
