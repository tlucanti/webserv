
SRC		= src/WEBserver.cpp src/main.cpp
INCLUDE = -I include -I router -I webcore
DEFINE 	= -D__cpp23

all:
	clang++ -fdiagnostics-color=always -std=c++2a -O0 -g3 ${DEFINE} ${INCLUDE} ${SRC} -o webserv


