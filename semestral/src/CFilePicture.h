#ifndef SEMESTRAL_CFILEPICTURE_H
#define SEMESTRAL_CFILEPICTURE_H

#include "CFile.h"

class CFilePicture : public CFile{
public:
    CFilePicture(CUrl url, const std::string & file_ending, const std::string & relative_path = "pictures");

    /**
     * In Picture file are no links at all. Override PURE VIRTUAL method.
     * @return empty list of links
     */
    std::list<CUrl> readLinks() override;

protected:

    /**
     * In Picture file are no links at all. Override PURE VIRTUAL method.
     */
    void replaceLinks() override;

};



#endif //SEMESTRAL_CFILEPICTURE_H
