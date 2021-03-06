CFLAGS = -c -g -Wall -std=gnu99
GL_INCLUDE = -I/usr/include/GL
GL_LIBDIR = -L. -L/usr/X11R6/lib
GL_LIBRARIES = -lglut -lGL -lm -lGLU # -lXmu -lXext -lXi -lX11
CC = gcc
OS = "unknown"

# Add objectiveC library for MacOSX.
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Apple")),)
 GL_INCLUDE    = -I/usr/X11R6/include
 GL_LIBRARIES += -lobjc
 BROWSER = dillo
 OS = "osx"
endif
# Nothing to be done for Linux :o)
ifneq ($(strip $(shell $(CC) -v 2>&1 | grep -i "Linux")),)
 OS = "linux"
 BROWSER = mozilla
endif
#

job: tpga4 #dox
	#one -c4 && two -n100 && $(BROWSER) DOX/html/index.html &
	#tpga4 -2 && tpga4 -3 && tpga4 -4 && tpga4 -5 && $(BROWSER) DOX/html/index.html &

tpga4: 	vertex.o \
	vertex_links.o \
	vertex_fusion_sorting.o \
	int_list.o \
	int_stack.o \
	triFusion.o \
	tpga4.o \
	tpga4_ex1.o \
	tpga4_ex2.o \
	tpga4_ex3.o \
	tpga4_ex4.o

	$(CC) $(GL_LIBDIR) \
		vertex.o \
		vertex_links.o \
		vertex_fusion_sorting.o \
		int_list.o \
		int_stack.o \
		triFusion.o \
		tpga4.o \
		tpga4_ex1.o \
		tpga4_ex2.o \
		tpga4_ex3.o \
		tpga4_ex4.o \
	$(GL_LIBRARIES) -o $@

tpga4.o: tpga4.c tpga4.h
	$(CC) $(GL_INCLUDE) $(CFLAGS) $<

clean:
	@echo "operating system = $(OS)"
	rm -rf *.o tpga4 DOX

################################################################################
# Generate doxygen documentation of file two.c using command file two.dox.
#dox: two.c two.h
#	rm -rf DOX
#	doxygen two.dox
#

