// SPDX-FileCopyrightText: 2005-2026 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_SYNCHRONIZATION_BARRIER_HPP
#define GUARD_ISHIKO_CPP_SYNCHRONIZATION_BARRIER_HPP

#include <boost/thread/barrier.hpp>
#include <atomic>

namespace Ishiko
{
    class Barrier
    {
    public:
        Barrier(size_t count);
        Barrier(const Barrier& other) = delete;

        bool wait();

    private:
        boost::barrier m_impl;
    };

}

#endif
