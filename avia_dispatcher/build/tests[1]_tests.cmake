add_test( Flight.CreateFlight [==[/home/igor/Programming/C++/training/projects/avia_dispatcher/build/tests]==] [==[--gtest_filter=Flight.CreateFlight]==] --gtest_also_run_disabled_tests)
set_tests_properties( Flight.CreateFlight PROPERTIES WORKING_DIRECTORY [==[/home/igor/Programming/C++/training/projects/avia_dispatcher/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( tests_TESTS Flight.CreateFlight)
