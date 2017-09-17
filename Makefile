
.PHONY: all clean mock test src package

VERSION=0.3

all: src

package: clean
	zip -r badconnection-$(VERSION).zip . -x .git/\*

clean:
	make -C mock clean
	make -C test clean
	make -C src clean
	rm -f *.zip

mock:
	make -C mock

test: mock
	make -C test

src: test
	make -C src