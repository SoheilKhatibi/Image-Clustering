CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp util.cpp k-means.cpp em.cpp
PROG = mat

OPENCV = `pkg-config opencv4 --cflags --libs`
ARMADILLO = -llapack -lblas -larmadillo
LIBS = $(OPENCV) $(ARMADILLO)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm $(PROG)
