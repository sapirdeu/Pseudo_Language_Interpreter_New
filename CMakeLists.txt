cmake_minimum_required(VERSION 3.17)
project(Pseudo_Language_Interpreter)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(Pseudo_Language_Interpreter main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h Commands/PrintCommand.cpp Commands/PrintCommand.h Tools/SymbolTable.cpp Tools/SymbolTable.h Tools/VarType.cpp Tools/VarType.h Commands/Command.h Commands/SleepCommand.cpp Commands/SleepCommand.h Expression/Expression.h Expression/AllExpressions.cpp Expression/AllExpressions.h Tools/Structs.h Commands/PrintCommand.h Commands/ConnectCommand.cpp Commands/ConnectCommand.h Commands/DefineVarCommand.cpp Commands/DefineVarCommand.h Commands/IfCommand.cpp Commands/IfCommand.h Commands/OpenServerCommand.cpp Commands/OpenServerCommand.h Commands/WhileCommand.cpp Commands/WhileCommand.h Commands/SetCommand.cpp Commands/SetCommand.h)
