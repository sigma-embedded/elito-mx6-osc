bindir =	/usr/bin

all:		osc

install:	osc
	install -p -m 0755 osc ${DESTDIR}${bindir}/osc
