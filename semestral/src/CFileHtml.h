#ifndef SEMESTRAL_CFILEHTML_H
#define SEMESTRAL_CFILEHTML_H

#include "CFile.h"
#include <utility>

class CFileHtml: public CFile{

public:

    /**
     * Constructor
     * @param url File URL
     * @param relative_path File relative path for saving
     */
    explicit CFileHtml(CUrl url, const std::string & relative_path = "subpages");

    /**
     * Destructor
     */
    ~CFileHtml() override = default;

    /**
     * Go through file and read all links..
     * @return
     */
    std::list<CUrl> readLinks() override;


    /**
     * Go through file and replace all links with path from map.
     */
    void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map) override;

    /**
     * @brief Setting content into file. Used mostly for testing.
     * @param content String of new content.
     */
    void setContent(std::string content) override;

    /**
     * @brief Increment count of downloaded HTML files. Check max level.
     * @param stats Struct of statistic data.
     */
    void notch(CStats & stats) override;

public:

    /**
     * Generates filename. HTML files unlike others must have added file extension.
     * @param targetFolder
     * @param used_names
     */
    void generateName(const std::filesystem::path & targetFolder, std::set<std::filesystem::path> & used_names) override;

private:

    /**
     * Finds link in string of tag with given expected attr name with link (href / src).
     * @param tag string of tag content without <,>, and tag name
     * @param attr_name_check string of expected attr name with link
     * @return optional pair of link limits, empty if no link is present
     */
    std::optional<std::pair<size_t , size_t>> findLinkInTag (const std::string & tag, const std::string & attr_name_check);

    /**
     * Finds link in string of tag for linking css (link tag + href + rel="stylesheet").
     * @param tag string of tag content without <,>, and tag name
     * @return optional pair of link limits, empty if no link is present
     */
    std::optional<std::pair<size_t , size_t>> findLinkCss (const std::string & tag);


};


#endif //SEMESTRAL_CFILEHTML_H
