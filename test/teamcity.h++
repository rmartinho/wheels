/*
 *  Created by Martinho Fernandes on 27/11/2013.
 *  Copyright 2013 Martinho Fernandes. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_REPORTER_TEAMCITY_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_REPORTER_TEAMCITY_HPP_INCLUDED

#define CATCH_CONFIG_RUNNER
#include <catch.h++>

#include <string>
#include <iostream>

namespace Catch {

    struct TeamCityReporter : SharedImpl<IStreamingReporter> {
        TeamCityReporter( ReporterConfig const& ) {}

        static std::string getDescription() {
            return "Reports test results to TeamCity interactively";
        }
        virtual ReporterPreferences getPreferences() const {
            ReporterPreferences prefs;
            prefs.shouldRedirectStdOut = false;
            return prefs;
        }

        virtual void noMatchingTestCases( std::string const& spec ) {
            std::cout << "##teamcity[buildProblem description='No test cases matched |'" << spec << "|''" << std::endl;
        }

        // TODO escaping
        void teamCityTestSuiteStarted( std::string const& name ) {
            std::cout << "##teamcity[testSuiteStarted name='" << name << "']" << std::endl;
        }
        void teamCityTestStarted( std::string const& name ) {
            std::cout << "##teamcity[testStarted name='" << name << "']" << std::endl;
        }
        void teamCityTestSuiteFinished( std::string const& name ) {
            std::cout << "##teamcity[testSuiteFinished name='" << name << "']" << std::endl;
        }
        void teamCityTestFinished( std::string const& name ) {
            std::cout << "##teamcity[testFinished name='" << name << "']" << std::endl;
        }
        void teamCityTestFailed( std::string const& name, std::string const& message, std::vector<MessageInfo> const& messages) {
            std::cout << "##teamcity[testFailed name='" << name << "' message='" << message << "' detail='";
            for(auto&& info : messages) {
                std::cout << info.message << "|n";
            }
            std::cout << "']" << std::endl;
        }

        virtual void testRunStarting( TestRunInfo const& testInfo ) {
            teamCityTestSuiteStarted(testInfo.name);
        }
        virtual void testGroupStarting( GroupInfo const& ) {}
        virtual void testCaseStarting( TestCaseInfo const& testInfo ) {
            teamCityTestStarted(testInfo.name);
            currentTestName = testInfo.name;
        }
        virtual void sectionStarting( SectionInfo const& ) {}

        virtual void assertionStarting( AssertionInfo const& ) {}

        virtual bool assertionEnded( AssertionStats const& _assertionStats ) {
            if(_assertionStats.assertionResult.isOk()) return false;
            teamCityTestFailed(currentTestName, "something bad happened", _assertionStats.infoMessages);
            return true;
        }

        virtual void sectionEnded( SectionStats const& ) {}

        virtual void testCaseEnded( TestCaseStats const& _testCaseStats ) {
            teamCityTestFinished(_testCaseStats.testInfo.name);
        }
        virtual void testGroupEnded( TestGroupStats const& ) {}
        virtual void testRunEnded( TestRunStats const& _testRunStats ) {
            teamCityTestSuiteFinished(_testRunStats.runInfo.name);
        }
    private:
        std::string currentTestName;

    };
    REGISTER_REPORTER( "teamcity", TeamCityReporter )

} // end namespace Catch

#endif // TWOBLUECUBES_CATCH_REPORTER_CONSOLE_HPP_INCLUDED
