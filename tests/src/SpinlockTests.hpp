// SPDX-FileCopyrightText: 2005-2025 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_SYNCHRONIZATION_TESTS_SPINLOCKTESTS_HPP
#define GUARD_ISHIKO_CPP_SYNCHRONIZATION_TESTS_SPINLOCKTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class SpinlockTests : public Ishiko::TestSequence
{
public:
    SpinlockTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void AcquireTest1(Ishiko::Test& test);
    static void AcquireTest2(Ishiko::Test& test);
};

#endif
