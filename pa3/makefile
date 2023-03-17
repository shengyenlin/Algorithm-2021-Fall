CC = g++
CFLAGS = -c # -c option ask g++ to compile the source files, but do not link.
AR = ar
ARFLAGS = rcv
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

bin/cb			: cb.o main.o lib
			$(CC) $(OPTFLAGS) cb.o main.o -ltm_usage -Llib -o bin/cb
main.o 	   	: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
cb.o			: src/CycleBreaker.cpp src/CycleBreaker.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

clean:
		rm -rf *.o lib/*.a lib/*.o bin/*