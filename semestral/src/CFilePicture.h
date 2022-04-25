#ifndef SEMESTRAL_CFILEPICTURE_H
#define SEMESTRAL_CFILEPICTURE_H

#include "CFile.h"

class CFilePicture : public CFile{
public:
    CFilePicture(const std::string & name, const std::string & relative_path, const std::string & file_ending);
    virtual void save(std::filesystem::path targetFolder);

};


#endif //SEMESTRAL_CFILEPICTURE_H
