CXX=g++
LD=g++
AR=ar
BDIR=build
SDIR=src
CXXFLAGS=-std=c++17 -Wall -pedantic -O2
SHELL:=/bin/bash

all: downloader

deps:
	$(CXX) -MM $(SDIR)/*.cpp > $(BDIR)/Makefile.d

downloader: CDownloader.o
	$(CXX) $(CXXFLAGS) -o $(BDIR)/$@ $(BDIR)/$^

%.o: $(SDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $(BDIR)/$@ $<

clean:
	rm -f $(BDIR)/Makefile.d $(BDIR)/*.o $(BDIR)/downloader

-include $(BDIR)/Makefile.d
