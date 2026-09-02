# you can put include files in this directory
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

# directory where object files will be created
ODIR=obj
# you can put library files in this directory
LDIR =../lib
# looks for library libm.so or libm.a
LIBS=-lm

# create string with ../include/<header filename> in our case ../include/myheader.h
_DEPS = myheader.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# create string with obj/<object filename> in our case obj/add.o and obj/sub.o  (obj folder will be created under current i.e. source directory)
_LIBOBJ = add.o sub.o
LIBOBJ = $(patsubst %,$(ODIR)/%,$(_LIBOBJ))
LIBSRC = add.c sub.c
_APPOBJ = call_lib_function.o
APPOBJ = $(patsubst %,$(ODIR)/%,$(_APPOBJ))

$(ODIR)/add.o: add.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

$(ODIR)/sub.o: sub.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

$(LDIR)/libmymath.so:$(LIBOBJ)
	$(CC) -shared -o $@ $^

$(APPOBJ): call_lib_function.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
call_lib_function.out: $(APPOBJ) $(LDIR)/libmymath.so
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDIR)/libmymath.so
	
.PHONY: clean

# removes object files and temporary files created with ~ at the end of file name in current i.e. source and include directory
clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f call_lib_function.out $(LDIR)/libmymath.so
	
.PHONY: all
all: $(LDIR)/libmymath.so call_lib_function.out
