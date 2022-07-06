#ifndef SEMESTRAL_CFILEHTML_H
#define SEMESTRAL_CFILEHTML_H

#include "CFile.h"
#include "CStats.h"

/**
 * @class CFileHtml
 * @extends CFile
 * @brief Class representing HTML file.
 */
class CFileHtml: public CFile{

public:

    /**
     * @brief Constructor
     * @param url File URL
     * @param relative_path File relative path for saving
     */
    explicit CFileHtml(CUrl url, const std::string & relative_path = "subpages");

    /**
     * @brief Destructor
     */
    ~CFileHtml() override = default;

    /**
     * @brief Parses file and reads all links.
     * @note All links are also modified to absolute type.
     * @return list of all links
     */
    std::list<CUrl> readLinks() override;


    /**
     * @brief Parses file and replace all links with path from map, if there record exists.
     * @param replacing_map Map containing information about links and their path replacements
     */
    void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map) override;

    /**
     * @brief Setting content into file. Used mostly for testing.
     * @param content String of new content
     */
    void setContent(std::string content) override;

    /**
     * @brief Increments count of downloaded HTML files in statistics. Increases statistics level if necessary as well.
     */
    void notch() override;

public:

    /**
     * @brief Reserves names for disk saving.
     * @param targetFolder Folder where the file should be stored
     * @param used_names Set of already used names
     */
    void generateName(const std::filesystem::path & targetFolder, std::set<std::filesystem::path> & used_names) override;

private:

    /**
     * @brief Finds link in string of tag with given expected attr name with link.
     * @note In tag is searching for attributes "href" or "src".
     * @param tag string of tag content without <,>, and tag name
     * @param attr_name_check string of expected attr name with link
     * @return optional pair of link limits, empty if no link is present
     */
    std::optional<std::pair<size_t , size_t>> findLinkInTag (const std::string & tag, const std::string & attr_name_check);

    /**
     * @brief Finds link in string of tag for linking css.
     * @note "link" tag + "href" + rel="stylesheet".
     * @param tag string of tag content without <,>, and tag name
     * @return optional pair of link limits, empty if no link is present
     */
    std::optional<std::pair<size_t , size_t>> findLinkCss (const std::string & tag);


};


#endif //SEMESTRAL_CFILEHTML_H
