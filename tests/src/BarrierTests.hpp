// SPDX-FileCopyrightText: 2005-2026 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_SYNCHRONIZATION_TESTS_BARRIERTESTS_HPP
#define GUARD_ISHIKO_CPP_SYNCHRONIZATION_TESTS_BARRIERTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class BarrierTests : public Ishiko::TestSequence
{
public:
    BarrierTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
