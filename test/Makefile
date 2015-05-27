CXXFLAGS=-fPIC -g -finline-functions -Wall -W -Winline -pipe -Wreturn-type -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wno-unused-parameter -D_GNU_SOURCE  
CFLAGS=$(CXXFLAGS)
INCPATH= -I../output/include -I. 

DEP_LDFLAGS= -L../output/lib -L. 

DEP_LDLIBS= -lpthread 
CXX=g++
CC = gcc
########################
SRCPATTERN=../src/*.cpp
SRCFILES=$(wildcard $(SRCPATTERN))
########################
PATTERN=test_main.cpp
#PATTERN=test_data_backup.cpp test_fifo_queue.cpp test_pri_queue.cpp
TESTFILES=$(wildcard $(PATTERN))
EXE=$(basename $(TESTFILES))
all : $(EXE)
$(EXE) : % : %.cpp $(SRCFILES)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(CFLAGS) $(INCPATH) $(DEP_LDFLAGS) $(DEP_LDLIBS)
.PHONY: list clean
list:
	@echo $(EXE)
clean:
	rm -f $(EXE)



