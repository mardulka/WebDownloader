CXX=g++
LD=g++
AR=ar
SDIR=src
BDIR=build
TDIR=test
DDIR=doc
GDIR=debug
LOGIN=cermam22
NAME=webdownloader
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long -O2
LIBS=-lstdc++fs
SHELL:=/bin/bash

#lists -----------------------------------------------------------------------------------------------------------------

HEADERS = $(wildcard $(SDIR)/*.h)
SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SDIR)/%.cpp=$(BDIR)/%.o)
TESTS = $(wildcard $(TDIR)/*.test.cpp)
BTESTS= $(TESTS:$(TDIR)/%.cpp=$(GDIR)/%)
RTESTS= $(TESTS:$(TDIR)/%.cpp=%)
TOBJECTS := $(filter-out $(BDIR)/CDownloader.o, $(OBJECTS))
ZIPOBJ = src test examples Makefile Doxyfile prohlaseni.txt zadani.txt

#general targets -------------------------------------------------------------------------------------------------------

.PHONY: all
all: compile compiletests doc

.PHONY: compile
compile: deps $(LOGIN)

.PHONY: run
run:
	./$(LOGIN) -h

.PHONY: test
test: compiletests runtests

.PHONY: runtests
runtests: $(RTESTS)

.PHONY: compiletests
compiletests: $(BTESTS)

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

#compilations ----------------------------------------------------------------------------------------------------------

.PHONY: deps
deps:
	mkdir -p $(BDIR)
	$(CXX) -MM $(SDIR)/*.cpp > $(BDIR)/Makefile.src.d
	$(CXX) -MM $(TDIR)/*.cpp > $(BDIR)/Makefile.test.d

$(LOGIN): $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LIBS)

$(BDIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -g -c -o $@

$(GDIR)/%: $(GDIR)/%.o $(TOBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@ $(LIBS)

$(GDIR)/%.o: $(TDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -g -c -o $@

$(RTESTS):
	$(GDIR)/$@

.PHONY: clean
clean:
	rm -rf  $(BDIR)/ $(DDIR)/ $(GDIR)/
	rm -f $(LOGIN)

#include deps ----------------------------------------------------------------------------------------------------------

-include $(BDIR)/Makefile.src.d
-include $(BDIR)/Makefile.test.d


#zip file --------------------------------------------------------------------------------------------------------------
.PHONY: zipfolder
zipfolder:
	mkdir -p $(BDIR)/$(LOGIN)
	cp -r $(ZIPOBJ) $(BDIR)/$(LOGIN)