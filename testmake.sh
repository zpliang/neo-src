
mysrclist="src/mjdyd.cpp src/coord-fun_x.cpp src/double-vec.cpp src/sod_to_hms.cpp "
myobjlist="  ./mjdyd.o     ./coord-fun_x.o     ./double-vec.o     ./sod_to_hms.o "

g++ -c ${mysrclist}

ld -r ${myobjlist} -o myfunlib.o

g++ test.cpp libsofa_c.a myfunlib.o



