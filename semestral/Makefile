CXX=g++
LD=g++
AR=ar
DIR=build
CXXFLAGS=-std=c++17 -Wall -pedantic -O2
SHELL:=/bin/bash

all: downloader

deps:
	$(CXX) -MM *.cpp > $(DIR)/Makefile.d

downloader: CDownloader.o
	$(CXX) $(CXXFLAGS) -o $@ $(DIR)/$^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(DIR)/$@ $<

clean:
	rm -f $(DIR)/Makefile.d $(DIR)/*.o $(DIR)/downloader

-include $(DIR)/Makefile.d
