
mysrclist="src/mjdyd.cpp src/coord-fun_x.cpp src/double-vec.cpp src/hermite-gmp.cpp src/Arr2.cpp src/Rec3.cpp  src/filerw_x.cpp src/primit-fun.cpp src/troprf2c.cpp src/sod_to_hms.cpp " 
myobjlist="  ./mjdyd.o     ./coord-fun_x.o     ./double-vec.o     ./hermite-gmp.o     ./Arr2.o     ./Rec3.o      ./filerw_x.o     ./primit-fun.o     ./troprf2c.o     ./sod_to_hms.o   " 

g++ -c ${mysrclist}

ld -r ${myobjlist} -o myfunlib.o

g++ -g main.cpp libsofa_c.a myfunlib.o  -lgmp

./a CPF10chunk_LARETS.txt chan7237dat.txt 56383 1 > out.tmp