EXE = yanghui
Objs += mymain.o
Objs += yanghui.o
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