cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(PseudoEngine2 VERSION 0.1)

add_executable(PseudoEngine2)

target_include_directories(PseudoEngine2 PRIVATE src)

if(MSVC)
    string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    target_compile_options(PseudoEngine2 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_precompile_headers(PseudoEngine2 PRIVATE src/pch.h)

target_sources(PseudoEngine2 PRIVATE 
    src/lexer/symbolLexer.cpp
    src/lexer/lexer.cpp
    src/lexer/tokens.cpp

    src/nodes/eval/arithmetic.cpp
    src/nodes/eval/comparison.cpp
    src/nodes/eval/stringcat.cpp
    src/nodes/eval/logic.cpp
    src/nodes/loop/while.cpp
    src/nodes/loop/for.cpp
    src/nodes/loop/repeatUntil.cpp
    src/nodes/loop/control.cpp
    src/nodes/functions/procedure.cpp
    src/nodes/functions/function.cpp
    src/nodes/selection/ifStatement.cpp
    src/nodes/selection/case.cpp
    src/nodes/variable.cpp
    src/nodes/array.cpp
    src/nodes/cast.cpp
    src/nodes/io.cpp
    src/nodes/nodeResult.cpp
    src/nodes/base.cpp

    src/parser/evalExprParser.cpp
    src/parser/variableExprParser.cpp
    src/parser/arrayOperationParser.cpp
    src/parser/procedureParser.cpp
    src/parser/functionParser.cpp
    src/parser/selectionParser.cpp
    src/parser/loopParser.cpp
    src/parser/ioParser.cpp
    src/parser/parser.cpp

    src/psc/types/numeric.cpp
    src/psc/types/boolean.cpp
    src/psc/types/character.cpp
    src/psc/scope/block.cpp
    src/psc/scope/context.cpp
    src/psc/variable.cpp
    src/psc/array.cpp
    src/psc/procedure.cpp
    src/psc/builtinFunctions/string.cpp
    src/psc/builtinFunctions/char.cpp
    src/psc/builtinFunctions/numeric.cpp
    src/psc/builtinFunctions/math.cpp
    src/psc/error.cpp
    
    src/launch/repl.cpp
    src/launch/runFile.cpp

    src/main.cpp
)
