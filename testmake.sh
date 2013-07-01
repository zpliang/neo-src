mysrclist="src/mjdyd.cpp "

g++ -c ${mysrclist}

ld -r mjdyd.o -o myfunlib.o

g++ test.cpp libsofa_c.a myfunlib.o
