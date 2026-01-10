// SPDX-FileCopyrightText: 2005-2026 Xavier Leclercq
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

static unsigned long SpinlockAcquireTest2Helper1(void* data)
{
    // Take the current result, play a bit with it and then put back the modified value
    // Voluntarily lengthy so the 2 threads will interrupt eachother and cause the result to
    // be invalid if critical section is not used
    int i = 0;
    while (i < 20000)
    {
        int result = *((int*)data);
        int j = 0;
        while (j < 100000)
        {
            j++;
        }
        result++;
        *((int*)data) = result;
        i++;
    }
    return 0;
}

static unsigned long SpinlockAcquireTest2Helper2(void* data)
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
    // First run without the spinlock to be sure that the race condition is severe enough to cause the result to be
    // incorrect because if it is not then the next test wouldn't be significant
    int result_without_spinlock = 0;

    Thread thread1(SpinlockAcquireTest2Helper1, &result_without_spinlock);
    Thread thread2(SpinlockAcquireTest2Helper1, &result_without_spinlock);
    thread1.resume();
    thread2.resume();
    thread1.join();
    thread2.join();

    ISHIKO_TEST_FAIL_IF_EQ(result_without_spinlock, 40000);

    // Now test with the spinlock and make sure the result is now correct.
    int result_with_spinlock = 0;

    Thread thread3(SpinlockAcquireTest2Helper2, &result_with_spinlock);
    Thread thread4(SpinlockAcquireTest2Helper2, &result_with_spinlock);
    thread3.resume();
    thread4.resume();
    thread3.join();
    thread4.join();

    ISHIKO_TEST_FAIL_IF_NEQ(result_with_spinlock, 40000);
    ISHIKO_TEST_PASS();
}
