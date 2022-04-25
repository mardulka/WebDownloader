#ifndef SEMESTRAL_CFILECSS_H
#define SEMESTRAL_CFILECSS_H

#include "CFile.h"

class CFileCss : public CFile{
public:
    CFileCss(const string & name, const string & relative_path, const string & file_ending);
    virtual void save(std::filesystem::path targetFolder);

};


#endif //SEMESTRAL_CFILECSS_H
