CXX=g++
LD=g++
AR=ar
BDIR=build
CXXFLAGS=-std=c++17 -Wall -pedantic -O2
SHELL:=/bin/bash


all: webdownloader

deps:
	$(CXX) -MM */*.cpp > $(BDIR)/Makefile.d

webdownloader: $(BDIR)/CDownloader.o $(BDIR)/CCli.o $(BDIR)/CConnection.o
	$(CXX) $(CXXFLAGS) -o $(BDIR)/$@ $^

$(BDIR)/%.o: */%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<

clean:
	rm -f $(BDIR)/Makefile.d $(BDIR)/*.o $(BDIR)/webdownloader

.PHONY: doc
doc:
	@doxygen

cleandoc:
	rm -rf ./doc/*


-include $(BDIR)/Makefile.d
