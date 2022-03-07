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
    unsigned char bt;

public:
    explicit cbitset(char btIn) : bt{static_cast<unsigned char>(btIn)}{};

    //get requested bit
    bool operator [](int pos) const{
        auto mask = static_cast<unsigned char>(128);
        mask = mask >> pos;
        if ((bt & mask) == mask)
            return true;
        return false;
    }

};

/**
 * Clas of binary file. Allow to use it bits by bits.
 */
class binFile{
    vector<cbitset> content;
    size_t currentByte = 0;
    int currentBit = 0;
    bool end = false;

public:
    binFile(){}

    bool last(){
        if (currentByte + 1 == content.size() && currentBit == 7) return true;
        return false;
    }

    /**
     * Read all file into vector of cbitsets
     */
    void readFile(ifstream & file){
        while (file.peek() != EOF){
            char c;
            file.get(c);
            cbitset bt(c);
            content.push_back(bt);
        }
    }

    cbitset curByte() const{
        return content[currentByte];
    }

    cbitset nextByte(){
        return content[currentByte + 1];
    }

    bool curBit() const{
        return curByte()[currentBit];
    }

    bool nextBit(){
        if (!last()){
            ++currentBit;
            currentBit %= 8;
            if (currentBit == 0) ++currentByte;
        } else{
            end = true;
        }
        return true;
    }

    bool readBit(bool & bit){
        if (end) return false;
        bit = curBit();
        nextBit();
        return true;
    }

    char readSymbol(){
        auto sym = static_cast<unsigned char>(0);
        auto mask = static_cast<unsigned char>(128);

        for (int i = 0 ; i < 8 ; ++i){
            bool bit;
            if (!readBit(bit)) throw out_of_range("Read error before decoding tree is complete");
            if (!bit) continue;
            unsigned char cmask = mask >> i;
            sym = sym | cmask;
        }
        return sym;
    }

    bool readChunkLen(unsigned int & len){
        len = 0;
        auto mask = static_cast<unsigned int>(2048);

        for (int i = 0 ; i < 12 ; ++i){
            bool bit;
            if (!readBit(bit)) return false;
            if (!bit) continue;
            unsigned int cmask = mask >> i;
            len = len | cmask;
        }
        return true;
    }


};

/**
 * Class of decompressing tree
 */
class decTree{
    /**
     * Class of tree element
     */
    struct celem{
        char symbol;
        celem * link_0;
        celem * link_1;

        celem(celem * link_0 = nullptr, celem * link_1 = nullptr) : link_0{link_0}, link_1{link_1}{}

        celem(char symbol, celem * link_0 = nullptr, celem * link_1 = nullptr) : symbol{symbol}, link_0{link_0},
                                                                                 link_1{link_1}{}

        bool isLeaf() const{
            if (link_0 == nullptr && link_1 == nullptr)
                return true;
            return false;
        }

    };

    celem * treeRoot;

private:
    celem * createTreeRec(binFile & file){
        bool bit;
        if (!file.readBit(bit)) throw out_of_range("Read error before decoding tree is complete");
        if (bit){
            celem * elem = new celem(file.readSymbol());
            return elem;
        }
        celem * elem = new celem();
        elem->link_0 = createTreeRec(file);
        elem->link_1 = createTreeRec(file);
        return elem;
    }

public:

    decTree(celem * tree_root = nullptr) : treeRoot(tree_root){}

    void createTree(binFile & file){
        bool bit;
        if (!file.readBit(bit)) throw out_of_range("Read error before decoding tree is complete");
        if (bit){
            treeRoot = new celem(file.readSymbol());
            return;
        }
        treeRoot = new celem();
        treeRoot->link_0 = createTreeRec(file);
        treeRoot->link_1 = createTreeRec(file);
    }

    bool decodeRec(char & decChar, binFile & content, celem * elem){
        if (elem->isLeaf()){
            decChar = elem->symbol;
            return true;
        }

        bool bit;
        if (!content.readBit(bit)) return false;

        if (bit){
            if (!decodeRec(decChar, content, elem->link_1)) return false;
        } else{
            if (!decodeRec(decChar, content, elem->link_0)) return false;
        }

        return true;
    }

    bool decode(char & decChar, binFile & content){
        if (!decodeRec(decChar, content, treeRoot)) return false;
        return true;
    }


};

/**
 * Function finding symbol and print it into file
 * @param outFile ouptut file stream
 * @param tree decoding tree
 * @param content content ready for decoding
 * @return
 */
bool decode(ofstream & outFile, decTree & tree, binFile & content){

    while (1){
        bool bit;
        if (!content.readBit(bit)) return false;
        if (!bit){ //last chunk
            unsigned int len;
            if (!content.readChunkLen(len)) return false;
            for (size_t i = 0 ; i < len ; ++i){
                char decChar;
                if (!tree.decode(decChar, content)) return false;
                outFile.put(decChar);
                if(outFile.fail()){
                    return false;
                }
            }
            break;

        } else{ //not last chunk
            for (int i = 0 ; i < 4096 ; ++i){
                char decChar;
                if (!tree.decode(decChar, content)) return false;
                outFile.put(decChar);
                if(outFile.fail()){
                    return false;
                }
            }
        }
    }
    return true;
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
    if (!inFile.is_open() || !outFile.is_open()) return false;

    //read file
    binFile content;
    content.readFile(inFile);

    //read tree definition and set tree
    decTree tree;
    try{tree.createTree(content);}
    catch (...){return false;}

    //decode
    if (!decode(outFile, tree, content)) return false;

    //close files
    inFile.close();
    outFile.close();

    return true;
}

[[maybe_unused]] bool compressFile([[maybe_unused]] const char * inFileName, [[maybe_unused]] const char * outFileName){
    // keep this dummy implementation (no bonus) or implement the compression (bonus)
    return false;
}

#ifndef __PROGTEST__

bool identicalFiles(const char * fileName1, const char * fileName2){
    //open files in proper mods and check opening
    ifstream File1(fileName1, ios::binary | ios::ate);
    ifstream File2(fileName2, ios::binary | ios::ate);
    if (!File1.is_open() || !File2.is_open()) return false;

    //read byte by byte and compare
    // mismatch --> return false
    // one ends earlier --> return false

    if (File1.tellg() != File2.tellg()){
        return false; //size mismatch
    }

    File1.seekg(0, std::ifstream::beg);
    File2.seekg(0, std::ifstream::beg);

    char c1, c2;
    while (File1.get(c1) && File2.get(c2)){
        if (c1 != c2) return false;
    }
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

/*
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
*/
    return 0;
}

#endif /* __PROGTEST__ */
