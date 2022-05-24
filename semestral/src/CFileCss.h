#ifndef SEMESTRAL_CFILECSS_H
#define SEMESTRAL_CFILECSS_H

#include "CFile.h"
#include "CStats.h"

/**
 * @class CFileCss
 * @extends CFile
 * @brief Class representing CSS file
 */
class CFileCss : public CFile{
public:

    /**
     * @brief Constructor
     * @param url File URL
     * @param relative_path File relative path for saving with default value.
     */
    explicit CFileCss(CUrl url, const std::string & relative_path = "css");

    /**
     * @brief Destructor
     */
    ~CFileCss() override = default;

    /**
     * @brief Parses file and reads all links.
     * @note All links are also modified to absolute type.
     * @return list of all links
     */
    std::list<CUrl> readLinks() override;

    /**
     * @brief Parses file and replace all links with path from map, if there record exists.
     * @param replacing_map Map containing information about links and their path replacements.
     */
    void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map) override;

    /**
     * @brief Increments count of downloaded CSS files in statistics.
     */
    void notch() override;
};


#endif //SEMESTRAL_CFILECSS_H
