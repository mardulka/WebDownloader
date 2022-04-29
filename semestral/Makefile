CXX=g++
LD=g++
AR=ar
SDIR=src
BDIR=build
TDIR=test
DDIR=doc
GDIR=debug
CXXFLAGS=-std=c++17 -Wall -pedantic -O2
SHELL:=/bin/bash

#lists -----------------------------------------------------------------------------------------------------------------

HEADERS = $(wildcard $(SDIR)/*.h)
SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SDIR)/%.cpp=$(BDIR)/%.o)
TESTS = $(wildcard $(TDIR)/*.test.cpp)

#general targets -------------------------------------------------------------------------------------------------------

.PHONY: all
all: compile doc

.PHONY: compile
compile: deps $(BDIR)/webdownloader

#compilations ----------------------------------------------------------------------------------------------------------

.PHONY: deps
deps:
	mkdir -p $(BDIR)
	$(CXX) -MM $(SDIR)/*.cpp > $(BDIR)/Makefile.src.d
	$(CXX) -MM $(TDIR)/*.cpp > $(BDIR)/Makefile.test.d

$(BDIR)/webdownloader: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@

$(BDIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -g -c -o $@

$(GDIR)/%.o: $(TDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -g -c -o $@

.PHONY: clean
clean:
	rm -rf $(BDIR) $(DDIR)

#include deps ----------------------------------------------------------------------------------------------------------

-include $(BDIR)/Makefile.src.d
-include $(BDIR)/Makefile.test.d

#documentation ---------------------------------------------------------------------------------------------------------
.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile


#tests -----------------------------------------------------------------------------------------------------------------
CUrl.test: $(GDIR)/CUrl.test.o $(BDIR)/CUrl.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^

CHttpResponse.test: $(GDIR)/CHttpResponse.test.o $(BDIR)/CHttpResponse.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^

CFileHtml.test: $(GDIR)/CFileHtml.test.o $(BDIR)/CFileHtml.o $(BDIR)/CFile.o $(BDIR)/CUrl.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^