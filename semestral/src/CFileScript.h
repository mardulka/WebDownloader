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


    /**
     * Go through file and replace all links with path from map.
     */
    void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map) override;
};


#endif //SEMESTRAL_CFILESCRIPT_H
