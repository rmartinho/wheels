// Wheels - various C++ utilities
//
// Written in 2013 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// TeamCity reporter for Catch

#ifndef WHEELS_TEST_CATCH_TEAMCITY_HPP
#define WHEELS_TEST_CATCH_TEAMCITY_HPP

#include <catch.hpp>

#include <string>
#include <iostream>

namespace wheels {
    struct teamcity_reporter : Catch::SharedImpl<Catch::IStreamingReporter> {
        teamcity_reporter( Catch::ReporterConfig const& ) {}

        static std::string getDescription() {
            return "Reports test results to TeamCity interactively";
        }
        virtual Catch::ReporterPreferences getPreferences() const {
            Catch::ReporterPreferences prefs;
            prefs.shouldRedirectStdOut = false;
            return prefs;
        }

        virtual void noMatchingTestCases( std::string const& spec ) {
            std::cout << "##teamcity[buildProblem description='No test cases matched |'" << spec << "|''" << std::endl;
        }

        // TODO escaping
        void teamcity_test_suite_started( std::string const& name ) {
            std::cout << "##teamcity[testSuiteStarted name='" << name << "']" << std::endl;
        }
        void teamcity_test_started( std::string const& name ) {
            std::cout << "##teamcity[testStarted name='" << name << "']" << std::endl;
        }
        void teamcity_test_suite_finished( std::string const& name ) {
            std::cout << "##teamcity[testSuiteFinished name='" << name << "']" << std::endl;
        }
        void teamcity_test_finished( std::string const& name ) {
            std::cout << "##teamcity[testFinished name='" << name << "']" << std::endl;
        }
        void teamcity_test_failed( std::string const& name, std::string const& message, std::vector<Catch::MessageInfo> const& messages) {
            std::cout << "##teamcity[testFailed name='" << name << "' message='" << message << "' detail='";
            for(auto&& info : messages) {
                std::cout << info.message << "|n";
            }
            std::cout << "']" << std::endl;
        }

        virtual void testRunStarting( Catch::TestRunInfo const& testInfo ) {
            teamcity_test_suite_started(testInfo.name);
        }
        virtual void testGroupStarting( Catch::GroupInfo const& ) {}
        virtual void testCaseStarting( Catch::TestCaseInfo const& testInfo ) {
            teamcity_test_started(testInfo.name);
            current_test_name = testInfo.name;
        }
        virtual void sectionStarting( Catch::SectionInfo const& ) {}

        virtual void assertionStarting( Catch::AssertionInfo const& ) {}

        virtual bool assertionEnded( Catch::AssertionStats const& _assertionStats ) {
            if(_assertionStats.assertionResult.isOk()) return false;
            teamcity_test_failed(current_test_name, "something bad happened", _assertionStats.infoMessages);
            return true;
        }

        virtual void sectionEnded( Catch::SectionStats const& ) {}

        virtual void testCaseEnded( Catch::TestCaseStats const& _testCaseStats ) {
            teamcity_test_finished(_testCaseStats.testInfo.name);
        }
        virtual void testGroupEnded( Catch::TestGroupStats const& ) {}
        virtual void testRunEnded( Catch::TestRunStats const& _testRunStats ) {
            teamcity_test_suite_finished(_testRunStats.runInfo.name);
        }
    private:
        std::string current_test_name;

    };

    REGISTER_REPORTER( "teamcity", teamcity_reporter )
} // namespace wheels

#endif // LOUNGECPP_CATCH_REPORTER_TEAMCITY_HPP

