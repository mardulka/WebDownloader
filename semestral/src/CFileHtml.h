#ifndef SEMESTRAL_CFILEHTML_H
#define SEMESTRAL_CFILEHTML_H

#include "CFile.h"

class CFileHtml: public CFile{


public:
    CFileHtml(CUrl url, const std::string & name, const std::string & relative_path = "subpages");

    /**
     * Go through file and read all links..
     * @return
     */
    std::list<CUrl> readLinks() override;

protected:

    /**
     * Go through file and replace all links with path from map.
     */
    void replaceLinks() override;
};


#endif //SEMESTRAL_CFILEHTML_H
