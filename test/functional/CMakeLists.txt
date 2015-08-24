enable_testing()

macro(add_functional_test arg)
  add_executable(${arg} ${arg}.cpp)
  target_link_libraries(${arg} functional)
  add_test(NAME ${arg} COMMAND ${arg})
endmacro()

add_functional_test(testPolynomial)
add_functional_test(testPiecewise)
add_functional_test(testTraits)
