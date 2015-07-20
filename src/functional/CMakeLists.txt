set(SOURCE_FILES Polynomial.cpp)
add_library(functional SHARED ${SOURCE_FILES})
add_dependencies(functional eigen)
