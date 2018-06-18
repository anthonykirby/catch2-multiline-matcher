$(info default $$CXX is [${CXX}])
CXX ?= g++
$(info using $$CXX=[${CXX}])

$(info default $$CXXFLAGS is [${CXXFLAGS}])
CXXFLAGS := -std=c++14
$(info using $$CXXFLAGS=[${CXXFLAGS}])


RM := rm -f

our_includefiles := ../catch2-multiline-matcher.hpp
srcfiles := catch_main.cpp catch2-multiline-matcher.t.cpp catch2-multiline-matcher_demo.cpp
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: catch2_testing

catch2_testing: $(objects) Makefile
	$(CXX) $(CXXFLAGS) -o catch2_testing $(objects)

%.o: %.cpp Makefile 
	$(CXX) -c $(CXXFLAGS) $< -o $@

depend: .depend

.depend: $(srcfiles) | $(our_includefiles)
	$(RM) ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	$(RM) ./.depend
	$(RM) $(objects)
	
test: catch2_testing
	./catch2_testing -s


include .depend
