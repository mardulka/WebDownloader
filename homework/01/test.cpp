#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

/**
 * Class representing one byte and grant access to specific bit
 */
class cbitset{
    char bt;

public:
    explicit cbitset(char bt) : bt{bt}{};

    //get requested bit
    bool operator [](unsigned short pos) const{
        char mask = (128 >> pos);
        if ((bt & mask) == mask)
            return true;
        return false;
    }

    // get requested bit wih bound check
    bool test(unsigned short pos) const{
        if (pos > 7) throw out_of_range("Position out of byte");
        char mask = (128 >> pos);
        return bt & mask;
    }


};

/**
 * Class of decompressing tree
 */
class decompTree{
    /**
     * Class of tree element
     */
    class celem{
        wchar_t symbol;
        celem * link_0;
        celem * link_1;
        bool filled = false;

    public:
        bool isLeaf() const{
            if (link_0 == nullptr && link_1 == nullptr)
                return true;
            return false;
        }

        bool isFilled() const{
            return filled;
        }

        void addChild(celem * child, bool position){
            position? link_1 = child : link_0 = child;
        }

    };

    celem * treeRoot;

public:
    void createTree(){

    }

};

/**
 * Read all file into vector of cbitsets
 * @param file input file
 * @param content vector of bitsets
 */
void readFileBinary(ifstream & file, vector<cbitset> & content){
    while (file.peek() != EOF){
        char c;
        file.get(c);
        cbitset bt(c);
        content.push_back(bt);
    }
}

/**
 * Function for decompressing file
 * @param inFileName Input file name
 * @param outFileName Output file name
 * @return false if error, true if ok
 */
bool decompressFile(const char * inFileName, const char * outFileName){

    //open files in proper mods and check opening
    ifstream inFile(inFileName, ios::binary);
    ofstream outFile(outFileName);
    if (!inFile.is_open()) return false;
    if (!outFile.is_open()) return false;

    //vector of bits
    vector<cbitset> content;
    readFileBinary(inFile, content);

    //read tree definition and set tree

    //decode

    return true;
}

[[maybe_unused]] bool compressFile([[maybe_unused]] const char * inFileName, [[maybe_unused]] const char * outFileName){
    // keep this dummy implementation (no bonus) or implement the compression (bonus)
    return false;
}

#ifndef __PROGTEST__

bool identicalFiles(const char * fileName1, const char * fileName2){
    //open files in proper mods and check opening
    ifstream File1(fileName1, ios::binary);
    ifstream File2(fileName2, ios::binary);
    if (!File1.is_open()) return false;
    if (!File2.is_open()) return false;

    //read byte by byte and compare
    // mismatch --> return false
    // one ends earlier --> return false

    char b1, b2;
    while (File1.get(b1) && File1.get(b2)){
        if (b1 != b2) return false;
    }
    if ((File1 && !File2) || (!File1 && File2)) return false;
    return true;
}

int main(void){
    assert (decompressFile("tests/test0.huf", "tempfile"));
    assert (identicalFiles("tests/test0.orig", "tempfile"));

    assert (decompressFile("tests/test1.huf", "tempfile"));
    assert (identicalFiles("tests/test1.orig", "tempfile"));

    assert (decompressFile("tests/test2.huf", "tempfile"));
    assert (identicalFiles("tests/test2.orig", "tempfile"));

    assert (decompressFile("tests/test3.huf", "tempfile"));
    assert (identicalFiles("tests/test3.orig", "tempfile"));

    assert (decompressFile("tests/test4.huf", "tempfile"));
    assert (identicalFiles("tests/test4.orig", "tempfile"));

    assert (!decompressFile("tests/test5.huf", "tempfile"));


    assert (decompressFile("tests/extra0.huf", "tempfile"));
    assert (identicalFiles("tests/extra0.orig", "tempfile"));

    assert (decompressFile("tests/extra1.huf", "tempfile"));
    assert (identicalFiles("tests/extra1.orig", "tempfile"));

    assert (decompressFile("tests/extra2.huf", "tempfile"));
    assert (identicalFiles("tests/extra2.orig", "tempfile"));

    assert (decompressFile("tests/extra3.huf", "tempfile"));
    assert (identicalFiles("tests/extra3.orig", "tempfile"));

    assert (decompressFile("tests/extra4.huf", "tempfile"));
    assert (identicalFiles("tests/extra4.orig", "tempfile"));

    assert (decompressFile("tests/extra5.huf", "tempfile"));
    assert (identicalFiles("tests/extra5.orig", "tempfile"));

    assert (decompressFile("tests/extra6.huf", "tempfile"));
    assert (identicalFiles("tests/extra6.orig", "tempfile"));

    assert (decompressFile("tests/extra7.huf", "tempfile"));
    assert (identicalFiles("tests/extra7.orig", "tempfile"));

    assert (decompressFile("tests/extra8.huf", "tempfile"));
    assert (identicalFiles("tests/extra8.orig", "tempfile"));

    assert (decompressFile("tests/extra9.huf", "tempfile"));
    assert (identicalFiles("tests/extra9.orig", "tempfile"));

    return 0;
}

#endif /* __PROGTEST__ */
