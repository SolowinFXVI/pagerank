CXX			:=	gcc
CXX_FLAGS	:=	-O3	-Wall	-Wextra	-std=c17	

BIN		:=	bin
SRC		:=	src
INCLUDE	:=	include
LIB		:=	lib

LIBRARIES	:=
EXECUTABLE	:=	main


all:	clean	$(BIN)/$(EXECUTABLE)

run:	clean	all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE):	$(SRC)/*.c
	$(CXX)	$(CXX_FLAGS)	-I$(INCLUDE)	-L$(LIB)	$^	-o	$@	$(LIBRARIES)

test:	clean	all
	valgrind	--vgdb=no	./$(BIN)/$(EXECUTABLE)


testdeep:	clean	all
	valgrind	--leak-check=full	--show-leak-kinds=all	--track-origins=yes	--leak-resolution=med	--vgdb=no	./$(BIN)/$(EXECUTABLE)


clean:
	-rm	$(BIN)/*
