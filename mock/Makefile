SRC=$(wildcard *.c)
BASES=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASES))

libmocksystem.a: $(OBJS)
	ar rc $@ $^