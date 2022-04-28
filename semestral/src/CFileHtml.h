#ifndef SEMESTRAL_CFILEHTML_H
#define SEMESTRAL_CFILEHTML_H

#include "CFile.h"

class CFileHtml: public CFile{

    int m_level{};

public:
    CFileHtml(const std::string & name, int level, const std::string & relative_path = "subpages");
};


#endif //SEMESTRAL_CFILEHTML_H
