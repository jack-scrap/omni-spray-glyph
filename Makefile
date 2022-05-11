CXX=g++

STATIC=main disp prog util
OBJ_STATIC=$(patsubst %, %.o, $(STATIC))

GL=-lGLEW -lGL
SDL=-lSDL2
PNG=-lpng
LDFLAGS+=$(SDL)
LDFLAGS+=$(GL)
LDFLAGS+=$(PNG)

.PHONY: clean

all: make

%.o: %.cpp %.h
	$(CXX) -c $< -o $@ $(LDFLAGS)

main.o: main.cpp
	$(CXX) -c $< -o $@ $(LDFLAGS)

make: $(OBJ_STATIC) $(HDR)
	$(CXX) $^ $(LDFLAGS)

clean:
	rm *.o a.out
