SRC=$(wildcard *.c)
BASE=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASE))

badconnection: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)