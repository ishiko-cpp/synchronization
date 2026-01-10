// SPDX-FileCopyrightText: 2005-2026 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BarrierTests.hpp"
#include "Ishiko/Synchronization/Barrier.hpp"

using namespace Ishiko;

BarrierTests::BarrierTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Barrier tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void BarrierTests::ConstructorTest1(Test& test)
{
    Barrier barrier(1);

    ISHIKO_TEST_PASS();
}
