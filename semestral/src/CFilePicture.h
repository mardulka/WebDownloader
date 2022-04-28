#ifndef SEMESTRAL_CFILEPICTURE_H
#define SEMESTRAL_CFILEPICTURE_H

#include "CFile.h"

class CFilePicture : public CFile{
public:
    CFilePicture(const std::string & name, const std::string & file_ending, const std::string & relative_path = "pictures");
};


#endif //SEMESTRAL_CFILEPICTURE_H
