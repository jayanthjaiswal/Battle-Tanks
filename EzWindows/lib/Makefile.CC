#
# EzWindows Library Makefile
# Time-stamp: <97/01/28 18:18:04 dcl3a>
# Author: Devon Lockwood
#


#
# You may have to set the directories so that are appropiate for 
# your system.
#

CCC      = CC
AR       = ar -r
RANLIB   = ranlib
X11DIR   = /X11.6/include
EZWINDIR = ../include
TARGET   = ../../../Student/EzWindows

CHAP3   = ../../../Student/chap03/lawn
CHAP6   = ../../../Student/chap06/stock
CHAP7   = ../../../Student/chap07/trainer
CHAP8K  = ../../../Student/chap08/kaleido
CHAP8T  = ../../../Student/chap08/trainer
CHAP10P = ../../../Student/chap10/poker
CHAP11F = ../../../Student/chap11/flip
CHAP11H = ../../../Student/chap11/hello1
CHAP11M = ../../../Student/chap11/mevent
CHAP11P = ../../../Student/chap11/photo
CHAP11S = ../../../Student/chap11/simon
CHAP11T = ../../../Student/chap11/timer
CHAP13  = ../../../Student/chap13
CHAP13B = $(CHAP13)/bignum
CHAP14  = ../../../Student/chap14/kaleido
CHAP15  = ../../../Student/chap15/house
CHAP16  = ../../../Student/chap16


#
# The CPPFLAGS macro lets the compiler know where to find include files 
#

CPPFLAGS=-I$(X11DIR) -I$(EZWINDIR)


#
# The OBJS macro tells the compiler which object files need to be present
# prior to archiving the library. 
#

EZOBJS=GraphicPosition.o position.o Miscellaneous.o Graphic.o \
	MessageGraphic.o EllipseGraphic.o ray.o \
	ButtonGraphic.o X11BitmapGraphic.o \
	GraphicManager.o Alert.o WindowManager.o \
	wobject.o shape.o rect.o label.o circle.o ellipse.o \
	random.o square.o triangle.o bitmap.o lellipse.o \
	uniform.o End.o


RANSOURCE=random.cc


RANOBJS=random.o


#
# The following sequence of commands defines the target for creating
# all of the library files
#

default:
	make clean
	make all
	make install


all:
	make ezwin
	make ezwinv
	make random
	make PokerObj
	make BigNumObj

usingG++:
	cp ../include/UsingG++.h ../include/Constants.h
	cp Makefile.g++ Makefile
	cp pokerlib/Makefile.g++ pokerlib/Makefile
	cp bignumlib/Makefile.g++ bignumlib/Makefile
	cp ./Makefiles/Chap03.g++ $(CHAP3)/Makefile
	cp ./Makefiles/Chap06.g++ $(CHAP6)/Makefile
	cp ./Makefiles/Chap07.g++ $(CHAP7)/Makefile
	cp ./Makefiles/Chap08Kal.g++ $(CHAP8K)/Makefile
	cp ./Makefiles/Chap08Train.g++ $(CHAP8T)/Makefile
	cp ./Makefiles/Chap10Poker.g++ $(CHAP10P)/Makefile
	cp ./Makefiles/Chap11Flip.g++ $(CHAP11F)/Makefile
	cp ./Makefiles/Chap11Hello.g++ $(CHAP11H)/Makefile
	cp ./Makefiles/Chap11MEvent.g++ $(CHAP11M)/Makefile
	cp ./Makefiles/Chap11Photo.g++ $(CHAP11P)/Makefile
	cp ./Makefiles/Chap11Simon.g++ $(CHAP11S)/Makefile
	cp ./Makefiles/Chap11Timer.g++ $(CHAP11T)/Makefile
	cp ./Makefiles/Chap13Bignum.g++ $(CHAP13B)/Makefile
	cp ./Makefiles/Chap14.g++ $(CHAP14)/Makefile
	cp ./Makefiles/Chap15.g++ $(CHAP15)/Makefile
	cp ./Makefiles/Chap16.g++ $(CHAP16)/Makefile


usingCC:
	cp ../include/UsingCC.h ../include/Constants.h
	cp Makefile.CC Makefile
	cp pokerlib/Makefile.CC pokerlib/Makefile
	cp bignumlib/Makefile.CC bignumlib/Makefile
	cp ./Makefiles/Chap03.CC $(CHAP3)/Makefile
	cp ./Makefiles/Chap06.CC $(CHAP6)/Makefile
	cp ./Makefiles/Chap07.CC $(CHAP7)/Makefile
	cp ./Makefiles/Chap08Kal.CC $(CHAP8K)/Makefile
	cp ./Makefiles/Chap08Train.CC $(CHAP8T)/Makefile
	cp ./Makefiles/Chap10Poker.CC $(CHAP10P)/Makefile
	cp ./Makefiles/Chap11Flip.CC $(CHAP11F)/Makefile
	cp ./Makefiles/Chap11Hello.CC $(CHAP11H)/Makefile
	cp ./Makefiles/Chap11MEvent.CC $(CHAP11M)/Makefile
	cp ./Makefiles/Chap11Photo.CC $(CHAP11P)/Makefile
	cp ./Makefiles/Chap11Simon.CC $(CHAP11S)/Makefile
	cp ./Makefiles/Chap11Timer.CC $(CHAP11T)/Makefile
	cp ./Makefiles/Chap13Bignum.CC $(CHAP13B)/Makefile
	cp ./Makefiles/Chap14.CC $(CHAP14)/Makefile
	cp ./Makefiles/Chap15.CC $(CHAP15)/Makefile
	cp ./Makefiles/Chap16.CC $(CHAP16)/Makefile

usingLinux:
	cp ../include/UsingG++.h ../include/Constants.h
	cp Makefile.g++ Makefile
	cp pokerlib/Makefile.linux pokerlib/Makefile
	cp bignumlib/Makefile.linux bignumlib/Makefile
	cp ./Makefiles/Chap03.linux $(CHAP3)/Makefile
	cp ./Makefiles/Chap06.linux $(CHAP6)/Makefile
	cp ./Makefiles/Chap07.linux $(CHAP7)/Makefile
	cp ./Makefiles/Chap08Kal.linux $(CHAP8K)/Makefile
	cp ./Makefiles/Chap08Train.linux $(CHAP8T)/Makefile
	cp ./Makefiles/Chap10Poker.linux $(CHAP10P)/Makefile
	cp ./Makefiles/Chap11Flip.linux $(CHAP11F)/Makefile
	cp ./Makefiles/Chap11Hello.linux $(CHAP11H)/Makefile
	cp ./Makefiles/Chap11MEvent.linux $(CHAP11M)/Makefile
	cp ./Makefiles/Chap11Photo.linux $(CHAP11P)/Makefile
	cp ./Makefiles/Chap11Simon.linux $(CHAP11S)/Makefile
	cp ./Makefiles/Chap11Timer.linux $(CHAP11T)/Makefile
	cp ./Makefiles/Chap13Bignum.linux $(CHAP13B)/Makefile
	cp ./Makefiles/Chap14.linux $(CHAP14)/Makefile
	cp ./Makefiles/Chap15.linux $(CHAP15)/Makefile
	cp ./Makefiles/Chap16.linux $(CHAP16)/Makefile


#
# Install the libraries by copying them to the appropriate target
# directory
#

#
# Install all libraries
#

install:
	cp *.a $(TARGET)/lib
	cp ../include/*.h $(TARGET)/include


#
# Install ezwin library only
#
installezwin:
	cp libezwin.a $(TARGET)/lib


#
# Install ezwinv library only
#
installezwinv:
	cp libezwinv.a $(TARGET)/lib


#
# Install random library only
#
installrandom:
	cp librandom.a $(TARGET)/lib


#
# The following sequence of commands defines the target for creating
# each of the library files
#

ezwin:: $(EZOBJS)
	$(AR) libezwin.a $(EZOBJS)
	$(RANLIB) libezwin.a
	rm -f *.o *~


compileEzSource: $(EZOBJS)


ezwinv::
	cp $(EZWINDIR)/vshape.h $(EZWINDIR)/shape.h
	make compileEzSource
	$(AR) libezwinv.a $(EZOBJS)
	$(RANLIB) libezwinv.a
	cp $(EZWINDIR)/oshape.h $(EZWINDIR)/shape.h
	rm -f *.o *~


random:: $(RANOBJS)
	$(AR) librandom.a $(RANOBJS)
	$(RANLIB) librandom.a
	rm -f *.o *~

# Make the poker object file that should
# be included in the chap10 directory

PokerObj:
	(cd pokerlib; make)


# Make the bignum object file that should
# be included in the chap13 directory

BigNumObj:
	(cd bignumlib; make)


#
# As a standard practice, a clean target is included in most make files.
# By executing 'make clean', all object files, backup files, and the
# library file is deleted.
#

clean:
	rm -f *.o *~ libezwin.a libezwinv.a librandom.a
	(cd bignumlib; make clean)
	(cd pokerlib; make clean)

cleanlib:
	rm -f libezwin.a libezwinv.a librandom.a


