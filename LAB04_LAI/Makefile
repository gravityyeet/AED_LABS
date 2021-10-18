#
#  File name: makefile
#
#  Author: 2021 Fall Semester P1 AED Team
#
#  Release date: 2021/10/12
#
#  Description: Makefile for LAI P2 and P3
#
#  Usage:
#     1) To generate the executable file for the program p2-pub, run
#         $ make p2
#
#        To generate the executable file for the program p3-pub, run
#         $ make p3
#
#     2) To clean all object files and the executable file, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall

#  Sources
SOURCES2 =  p2.c
SOURCES3 =  VecDynList.c p3.c

#  Objects
OBJECTS2 = p2.o
OBJECTS3 = VecDynList.o p3.o

p3: $(OBJECTS3)
	gcc -g -o $@ $(OBJECTS3)

VecDynList-pub.o: VecDynList.h VecDynList.c

p2: $(OBJECTS2)
	gcc -g -o $@ $(OBJECTS2)

clean::
	rm -f *.o core a.out p3 p2 *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
