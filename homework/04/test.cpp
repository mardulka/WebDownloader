#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>

using namespace std;
#endif /* __PROGTEST__ */

class CFile{
public:
    CFile(void);
    // copy cons, dtor, op=
    bool seek(uint32_t offset);
    uint32_t read(uint8_t * dst, uint32_t bytes);
    uint32_t write(const uint8_t * src, uint32_t bytes);
    void truncate(void);
    uint32_t fileSize(void) const;
    void addVersion(void);
    bool undoVersion(void);
private:
    // todo
};

