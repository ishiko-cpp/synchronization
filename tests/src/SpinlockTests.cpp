// SPDX-FileCopyrightText: 2005-2025 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "SpinlockTests.hpp"
#include "Ishiko/Synchronization/Spinlock.hpp"
#include <Ishiko/Concurrency.hpp>

using namespace Ishiko;

SpinlockTests::SpinlockTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Spinlock tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("acquire test 1", AcquireTest1);
    append<HeapAllocationErrorsTest>("acquire test 2", AcquireTest2);
}

void SpinlockTests::ConstructorTest1(Test& test)
{
    Spinlock spinlock;

    ISHIKO_TEST_PASS();
}

void SpinlockTests::AcquireTest1(Test& test)
{
    Spinlock spinlock;
    spinlock.acquire();
    spinlock.release();

    ISHIKO_TEST_PASS();
}

static Spinlock AcquireTest2Spinlock;

static unsigned long SpinlockAcquireTest2Helper(void* data)
{
    // Take the current result, play a bit with it and then put back the modified value
    // Voluntarily lengthy so the 2 threads will interrupt eachother and cause the result to
    // be invalid if critical section is not used
    int i = 0;
    while (i < 20000)
    {
        AcquireTest2Spinlock.acquire();
        int result = *((int*)data);
        int j = 0;
        while (j < 100000)
        {
            j++;
        }
        result++;
        *((int*)data) = result;
        AcquireTest2Spinlock.release();
        i++;
    }
    return 0;
}

void SpinlockTests::AcquireTest2(Test& test)
{
    int result = 0;

    Thread thread1(SpinlockAcquireTest2Helper, &result);
    Thread thread2(SpinlockAcquireTest2Helper, &result);
    thread1.resume();
    thread2.resume();
    thread1.join();
    thread2.join();

    ISHIKO_TEST_FAIL_IF_NEQ(result, 40000);
    ISHIKO_TEST_PASS();
}
