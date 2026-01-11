
LEXLIB = -lfl

INCLUDE=../includes
#CFLAGS+= -O2 -I${INCLUDE}
CFLAGS+= -g -I${INCLUDE}
RM=rm
#CC=cc
#CC=gcc
CXX=g++34
CPPFLAGS= ${CFLAGS}
LEX=flex

ENDLIB=../gkends/gkends.a
GREEKLIB=../greeklib/greeklib.a
MORPHLIB=../morphlib/morphlib.a
GENERLIB=../gener/gener.a
DICTLIB=../gkdict/gkdict.a
ANALLIB=anal.a
PHILLIB=libphilolog.a
LIBS=${GENERLIB} ${ENDLIB} ${DICTLIB} ${MORPHLIB} ${GREEKLIB}

LSJDIR=/local/text/lsj
ANALOBJ= checkcrasis.o \
checkdict.o \
checkgenwds.o \
checkhalf1.o \
checkindecl.o \
checkirreg.o \
checknom.o \
checkpreverb.o \
checkstem.o \
checkstring.o \
checkverb.o \
checkword.o \
dictstems.o \
prntanal.o \
prvb.o

PHILOBJ= checkcrasis.o \
checkdict.o \
checkgenwds.o \
checkhalf1.o \
checkindecl.o \
checkirreg.o \
checknom.o \
checkpreverb.o \
checkstem.o \
checkstring.o \
checkverb.o \
checkword.o \
dictstems.o \
prntanal.o \
prvb.o \
philolog.o \
prntalph.o \
../morphlib/sprntGkflags.o

${ANALLIB}: ${ANALOBJ}
	ar rv ${ANALLIB} ${ANALOBJ}
	ranlib ${ANALLIB}

${PHILLIB}: ${PHILOBJ} ${LIBS}
	rm -f ${PHILLIB}
	rm -rf tmp_objs
	mkdir tmp_objs
	for lib in ${LIBS}; do (cd tmp_objs && ar x ../$$lib); done
	ar q ${PHILLIB} ${PHILOBJ} tmp_objs/*.o
	ranlib ${PHILLIB}
	rm -rf tmp_objs

ALL=cruncher morpheus pname findbase deverbal ${ANALLIB} ${PHILLIB}

all: ${ALL}

install: all
	cp ${ALL} ../../bin


lcnt: lcnt.o ${ANALLIB} ${LIBS}
	${CC} -o lcnt lcnt.o ../gener/genwd.o ${ANALLIB} ${LIBS}

cruncher:stdiomorph.o ${ANALLIB} ${LIBS}
	${CC} -o cruncher stdiomorph.o ../gener/genwd.o ${ANALLIB} ${LIBS}

morpheus:morpheus.o prntalph.o ${ANALLIB} ${LIBS}
	${CC} -g -o morpheus morpheus.o prntalph.o ../gener/genwd.o \
		${ANALLIB} ${LIBS}

morphcheck:morphcheck.o ${LSJDIR}/MDBlib.o ${LSJDIR}/flen.o ${ANALOBJ} ${LIBS}
	${CC} -o morphcheck morphcheck.o ${LSJDIR}/MDBlib.o ${LSJDIR}/flen.o ../gener/genwd.o ${ANALOBJ} ${LIBS} ${LEXLIB}

pname:propname.o ${ANALOBJ} ${LIBS}
	${CC} -o pname propname.o ${ANALOBJ} ${LIBS}

findbase:	findbase.o ${ANALOBJ} ${LIBS}
	${CC} -o findbase findbase.o ${ANALOBJ} ${LIBS}

deverbal: deverb.o   ${ANALOBJ} ${LIBS}
	${CC} -o deverbal deverb.o ${ANALOBJ} ${LIBS}

clean:
	rm -f cruncher *.o anal.a morpheus pname findbase deverbal lcnt morphcheck proclems libphilolog.a

proclems: proclems.o
	${CC} -o proclems proclems.o
