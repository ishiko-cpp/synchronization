// SPDX-FileCopyrightText: 2005-2026 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "Barrier.hpp"

using namespace Ishiko;

Barrier::Barrier(size_t count)
    : m_impl(count)
{
}

bool Barrier::wait()
{
    return m_impl.wait();
}
