
SRC		= src/WEBserver.cpp src/main.cpp
INCLUDE = -I include -I router -I webcore
DEFINE 	= -D__cpp23 -DDO_VERBOSE
FLAGS	= -Wall -Wextra -fdiagnostics-color=always -std=c++2a -O0 -g3

all:
	clang++ ${FLAGS} ${DEFINE} ${INCLUDE} ${SRC} -o webserv


