CC=gcc
CFLAGS=-Wall -O2
LDFLAGS=-lm
EXEC=DCC
SRC= main.c $(wildcard */*.c)
SRCDIR = $(wildcard */)
OBJDIR = bin/
OBJ = $(SRC:.c=.o)
OBJPATH = $(foreach o, $(OBJ), $(OBJDIR)$(o))

all: prep $(EXEC)

DCC: $(OBJ)
	$(CC) -o $@ $(OBJPATH) $(LDFLAGS)

$(OBJDIR): $(SRCDIR)
	mkdir -p $(OBJDIR)$(SRCDIR)

%.o: %.c
	$(CC) -o $(OBJDIR)$@ -c $< $(CFLAGS)

prep: dir

dir : $(SRCDIR)
	$(foreach f,$^,mkdir -p $(OBJDIR)$(f);)

main.o: struct/blockchain.h cheater/cheat.h

clean:
	rm -rf *.o
	rm -rf */*.o
	rm -rf bin

mrproper: clean
	rm -rf $(EXEC)
