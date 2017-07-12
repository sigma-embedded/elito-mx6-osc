bindir =	/usr/bin

all:		osc

install:	osc
	install -D -p -m 0755 osc ${DESTDIR}${bindir}/osc
