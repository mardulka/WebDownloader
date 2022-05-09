#ifndef SEMESTRAL_CFILECSS_H
#define SEMESTRAL_CFILECSS_H

#include "CFile.h"

class CFileCss : public CFile{
public:
    /**
     * Constructor
     * @param url File URL
     * @param relative_path File relative path for saving
     */
    explicit CFileCss(CUrl url, const std::string & relative_path = "css");

    /**
     * Destructor
     */
    ~CFileCss() override = default;

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


#endif //SEMESTRAL_CFILECSS_H
