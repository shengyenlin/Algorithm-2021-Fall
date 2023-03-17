CC = g++
CFLAGS = -c # -c option ask g++ to compile the source files, but do not link.
AR = ar
ARFLAGS = rcv
OPTFLAGS = -O2 # -O2 option is for optimized version

all	: bin/mps utilities/resultChecker
	@echo -n ""

bin/mps			: MPS.o main.o lib
			$(CC) $(OPTFLAGS) MPS.o main.o -ltm_usage -Llib -o bin/mps
main.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
MPS.o			: src/MPS.cpp src/MPS.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

utilities/resultChecker: utilities/resultChecker.cpp
	$(CC) $< -o utilities/resultChecker

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*