TEST_SRC=$(wildcard test_*.c)
TEST_BASE=$(basename $(TEST_SRC))
TEST_OBJ=$(addsuffix .o, $(TEST_BASE))

VPATH=../src

MOCK_LIB=-L../mock -lmocksystem

CHECK_FLAGS = `pkg-config --cflags check`
CHECK_LIBS = `pkg-config --libs check`

LIBS=$(MOCK_LIB) $(CHECK_LIBS)
CFLAGS=$(CHECK_FLAGS) -I../src -I../mock

SUT=server.o

all: unit_tests
	./unit_tests

unit_tests: $(TEST_OBJ) $(SUT) testmain.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)