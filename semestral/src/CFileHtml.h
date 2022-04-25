#ifndef SEMESTRAL_CFILEHTML_H
#define SEMESTRAL_CFILEHTML_H

#include "CFile.h"

class CFileHtml: public CFile{

public:
    CFileHtml(const std::string & name, const std::string & relative_path);
};


#endif //SEMESTRAL_CFILEHTML_H
