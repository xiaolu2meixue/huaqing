EXE = stack
Filename = $(wildcard *.c)
Objs = $(patsubst %.c,%.o,$(Filename))
CC = gcc
CFlags = -c -o
.PHONY: clean
all: $(EXE)
$(EXE): $(Objs)
	$(CC) $^ -o $@
%.o: %.c
	$(CC) $^ $(CFlags) $@
clean:
	rm $(EXE) $(Objs)