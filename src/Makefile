CC=gcc
CFLAGS=-I$(IDIR) -Wall

IDIR=../include
ODIR=obj

_DEPS = jcutils_common.h arraylist.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR):
	mkdir -p $(ODIR)

_OBJ = arraylist.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: jcutils

jcutils: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

