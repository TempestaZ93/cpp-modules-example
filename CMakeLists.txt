CMAKE_MINIMUM_REQUIRED ( VERSION 3.11 )

PROJECT ( cpp_modules )

SET ( MAIN_SRC "src/main-program/main.cpp" )
SET ( MAIN_HDR "include/main-program/main.hpp" "include/shared/interface.hpp" )

SET ( MOD1_SRC "src/module-1/mod1.cpp" )
SET ( MOD2_HDR "include/module-1/mod1.hpp" "include/shared/interface.hpp" )

SET ( MOD2_SRC "src/module-2/mod2.cpp" )
SET ( MOD2_HDR "include/module-2/mod2.hpp" "include/shared/interface.hpp" )

SET ( MOD3_SRC "src/module-3/mod3.cpp" )
SET ( MOD3_HDR "include/module-3/mod3.hpp" "include/shared/interface.hpp" )

ADD_EXECUTABLE ( cppmods ${MAIN_SRC} ${MAIN_HDR} )
TARGET_INCLUDE_DIRECTORIES ( cppmods PRIVATE "include/main-program" PUBLIC "include/shared" )
TARGET_COMPILE_FEATURES ( cppmods PRIVATE cxx_std_20 )

ADD_LIBRARY ( mod1 SHARED ${MOD1_SRC} ${MOD1_HDR} )
TARGET_INCLUDE_DIRECTORIES ( mod1 PRIVATE "include/module-1" PUBLIC "include/shared" )

ADD_LIBRARY ( mod2 SHARED ${MOD2_SRC} ${MOD2_HDR} )
TARGET_INCLUDE_DIRECTORIES ( mod2 PRIVATE "include/module-2" PUBLIC "include/shared" )

ADD_LIBRARY ( mod3 SHARED ${MOD3_SRC} ${MOD3_HDR} )
TARGET_INCLUDE_DIRECTORIES ( mod3 PRIVATE "include/module-3" PUBLIC "include/shared" )

SET_TARGET_PROPERTIES ( mod1 mod2 mod3 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/modules )
