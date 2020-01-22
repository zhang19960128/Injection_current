CXX=g++
CXXFLAGS+=-I./include
LIBPATH+=
vpath %.cpp src
vpath %.h include
vpath %.o obj
INJECTION: main.o constant.o indexref.o readqebands.o banddot.o
	mkdir -p obj bin
	$(CXX) -o injection $(LIBPATH) main.o constant.o indexref.o readqebands.o banddot.o
	mv *o bin/
%.o:%.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $^
clean:
	rm -rf bin obj *.o
