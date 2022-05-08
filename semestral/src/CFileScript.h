#ifndef SEMESTRAL_CFILESCRIPT_H
#define SEMESTRAL_CFILESCRIPT_H

#include "CFile.h"

class CFileScript : public CFile{
public:
    /**
     * Constructor
     * @param url File URL
     * @param relative_path File relative path for saving
     */
    explicit CFileScript(CUrl url, const std::string & relative_path = "js");

    /**
     * Destructor
     */
    virtual ~CFileScript() = default;

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


#endif //SEMESTRAL_CFILESCRIPT_H
