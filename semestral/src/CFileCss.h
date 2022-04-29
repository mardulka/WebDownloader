#ifndef SEMESTRAL_CFILECSS_H
#define SEMESTRAL_CFILECSS_H

#include "CFile.h"

class CFileCss : public CFile{
public:
    CFileCss(CUrl url, const std::string & name, const std::string & relative_path = "css");

    /**
     * Go through file and read all links.
     * @return list of all links
     */
    std::list<CUrl> readLinks() override;

protected:

    /**
     * Go through file and replace all links with path from map.
     */
    void replaceLinks() override;
};


#endif //SEMESTRAL_CFILECSS_H
