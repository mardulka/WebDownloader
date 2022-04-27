CXX=g++
LD=g++
AR=ar
BDIR=build
TDIR=test
CXXFLAGS=-std=c++17 -Wall -pedantic -O2
SHELL:=/bin/bash


all: webdownloader

.PHONY: doc deps

deps:
	$(CXX) -MM */*.cpp > $(BDIR)/Makefile.d

webdownloader: $(BDIR)/CDownloader.o $(BDIR)/CCli.o $(BDIR)/CConnection.o $(BDIR)/CDownEngine.o $(BDIR)/CFile.o $(BDIR)/CFileHtml.o $(BDIR)/CFileCss.o $(BDIR)/CFilePicture.o $(BDIR)/CUrl.o $(BDIR)/CHttpResponse.o
	$(CXX) $(CXXFLAGS) -o $(BDIR)/$@ $^

$(BDIR)/%.o: */%.cpp
	$(CXX) $(CXXFLAGS) -g -c -o $@ $<

clean:
	rm -f $(BDIR)/Makefile.d $(BDIR)/*.o $(BDIR)/webdownloader

#include deps ----------------------------------------------------------------------------------------------------------

-include $(BDIR)/Makefile.d

#documentation ---------------------------------------------------------------------------------------------------------
doc:
	@doxygen

cleandoc:
	rm -rf ./doc/*

#tests -----------------------------------------------------------------------------------------------------------------
CURLtest: $(BDIR)/CURL_test.o $(BDIR)/CUrl.o
	$(CXX) $(CXXFLAGS) -o $(BDIR)/$@ $^

CHttpResponsetest: $(BDIR)/CHttpResponse_test.o $(BDIR)/CHttpResponse.o
	$(CXX) $(CXXFLAGS) -o $(BDIR)/$@ $^
