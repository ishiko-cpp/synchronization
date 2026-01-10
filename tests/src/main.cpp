// SPDX-FileCopyrightText: 2005-2025 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "SpinlockTests.hpp"
#include "Ishiko/Synchronization/linkoptions.hpp"
#include <Ishiko/TestFramework/Core.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification command_line_spec;
        Configuration configuration = command_line_spec.createDefaultConfiguration();
        CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        TestHarness the_test_harness("Ishiko/C++ Synchronization Library Tests", configuration);

        TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<SpinlockTests>();

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
