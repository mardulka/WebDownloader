#ifndef SEMESTRAL_CFILECSS_H
#define SEMESTRAL_CFILECSS_H

#include "CFile.h"

class CFileCss : public CFile{
public:
    CFileCss(const std::string & name, const std::string & relative_path, const std::string & file_ending);
};


#endif //SEMESTRAL_CFILECSS_H
