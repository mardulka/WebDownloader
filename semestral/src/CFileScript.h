#ifndef SEMESTRAL_CFILESCRIPT_H
#define SEMESTRAL_CFILESCRIPT_H

#include "CFile.h"
#include "CStats.h"

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
     * @brief Increment count of downloaded JS files
     */
    void notch() override;
};


#endif //SEMESTRAL_CFILESCRIPT_H
