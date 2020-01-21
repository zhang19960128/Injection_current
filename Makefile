CXX=icpc
CXXFLAGS+=-I./include
LIBPATH+=
vpath %.cpp src
vpath %.h include
vpath %.o obj
INJECTION: main.o constant.o
	mkdir -p obj bin
	$(CXX) -o INJECTION $(LIBPATH) main.o constant.o
	mv *o bin/
%.o:%.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $^
clean:
	rm -rf bin obj *.o
