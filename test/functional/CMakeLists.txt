enable_testing()

#TODO: move to different directory?
include_directories(../../src)
include_directories(../../test)

add_executable(testPolynomial testPolynomial.cpp)
target_link_libraries(testPolynomial functional)
add_test(NAME testPolynomial COMMAND testPolynomial)
