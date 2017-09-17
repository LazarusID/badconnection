
.PHONY: all clean mock test src

all: mock test src


clean:
	make -C mock clean
	make -C test clean
	make -C src clean


mock:
	make -C mock

test:
	make -C test

src:
	make -C src