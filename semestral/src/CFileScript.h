#ifndef SEMESTRAL_CFILESCRIPT_H
#define SEMESTRAL_CFILESCRIPT_H

#include "CFile.h"
#include "CStats.h"

/**
 * @class CFileScript
 * @extends CFile
 * @brief Class representing javascript file.
 */
class CFileScript : public CFile{
public:
    /**
     * @brief Constructor
     * @param url File URL
     * @param relative_path File relative path for saving
     */
    explicit CFileScript(CUrl url, const std::string & relative_path = "js");

    /**
     * @brief Destructor
     */
    virtual ~CFileScript() = default;

    /**
     * @brief Read links from file. Scripts are not intended for obtaining links, so for script does it nothing.
     * @note Only overrides pure virtual method.
     * @return empty list of links
     */
    std::list<CUrl> readLinks() override;

    /**
     * @brief Increments count of downloaded JS files in statistics.
     */
    void notch() override;
};


#endif //SEMESTRAL_CFILESCRIPT_H
