#ifndef SEMESTRAL_CFILEPICTURE_H
#define SEMESTRAL_CFILEPICTURE_H

#include "CFile.h"

class CFilePicture : public CFile{
public:
    CFilePicture(const string & name, const string & relative_path, const string & file_ending);
    virtual void save(std::filesystem::path targetFolder);

};


#endif //SEMESTRAL_CFILEPICTURE_H
