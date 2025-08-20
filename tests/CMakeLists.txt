find_package(GTest REQUIRED)

add_executable(test_main test_main.cpp)
target_link_libraries(test_main PRIVATE libsha256 GTest::gtest GTest::gtest_main)

add_test(NAME SHA256Test COMMAND test_main)
