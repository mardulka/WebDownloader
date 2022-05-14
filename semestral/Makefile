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
SHELL:=/bin/bash

#lists -----------------------------------------------------------------------------------------------------------------

HEADERS = $(wildcard $(SDIR)/*.h)
SOURCES = $(wildcard $(SDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SDIR)/%.cpp=$(BDIR)/%.o)
TESTS = $(wildcard $(TDIR)/*.test.cpp)
BTESTS= CUrl.test CHttpResponse.test CFileHtml.test CFileCss.test
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
runtests:
		$(GDIR)/CUrl.test
		$(GDIR)/CHttpResponse.test
		$(GDIR)/CFileHtml.test
		$(GDIR)/CFIleCss.test

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
	g++ $^ -o $@ -lstdc++fs

$(BDIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -g -c -o $@

$(GDIR)/%.o: $(TDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -g -c -o $@

.PHONY: compiletests
compiletests: $(BTESTS)


.PHONY: clean
clean:
	rm -rf $(BDIR) $(DDIR)
	rm -f $(LOGIN)

#include deps ----------------------------------------------------------------------------------------------------------

-include $(BDIR)/Makefile.src.d
-include $(BDIR)/Makefile.test.d


#zip file --------------------------------------------------------------------------------------------------------------
.PHONY: zipfolder
zipfolder: $(BDIR)/$(LOGIN).zip

$(BDIR)/$(LOGIN).zip:
	mkdir -p $(BDIR)/$(LOGIN)
	cp -r $(ZIPOBJ) $(BDIR)/$(LOGIN)


#tests -----------------------------------------------------------------------------------------------------------------
CUrl.test: $(GDIR)/CUrl.test.o $(BDIR)/CUrl.o $(BDIR)/CStats.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^ -lstdc++fs

CHttpResponse.test: $(GDIR)/CHttpResponse.test.o $(BDIR)/CHttpResponse.o $(BDIR)/CStats.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^ -lstdc++fs

CFileHtml.test: $(GDIR)/CFileHtml.test.o $(BDIR)/CFileHtml.o $(BDIR)/CFile.o $(BDIR)/CUrl.o $(BDIR)/CStats.o $(BDIR)/CCli.o $(BDIR)/CSettings.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^ -lstdc++fs

CFileCss.test: $(GDIR)/CFileCss.test.o $(BDIR)/CFileCss.o $(BDIR)/CFile.o $(BDIR)/CUrl.o $(BDIR)/CStats.o $(BDIR)/CCli.o $(BDIR)/CSettings.o
	$(CXX) $(CXXFLAGS) -o $(GDIR)/$@ $^ -lstdc++fs