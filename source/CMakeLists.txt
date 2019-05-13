add_library(skena
               interpreter.cpp
               astimpl.cpp
               parser.cpp
               demangle.cpp)

add_executable(skena_repl main.cpp)

target_link_libraries(skena_repl PRIVATE skena Readline::Readline)

target_link_libraries(skena PRIVATE Threads::Threads)

target_compile_features(skena PUBLIC cxx_std_17)


add_library(stdlib stdlib.cpp)
target_compile_features(stdlib PUBLIC cxx_std_17)

set_property(TARGET stdlib PROPERTY OUTPUT_NAME skena_stdlib)

target_link_libraries(skena PUBLIC stdlib fmt::fmt)
