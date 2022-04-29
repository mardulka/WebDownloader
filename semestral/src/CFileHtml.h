#ifndef SEMESTRAL_CFILEHTML_H
#define SEMESTRAL_CFILEHTML_H

#include "CFile.h"

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
    virtual ~CFileHtml() = default;

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

private:
    /**
     * Finds link in string of <a> html tag given by <) limits of file content.
     * @param start first position behind <a tag start
     * @param end position of > at end of tag
     * @return optional pair of link limits, empty if no link is present
     */
    std::optional<std::pair<size_t , size_t>> findLinkA (const size_t & start, const size_t & end);

    /**
     * Finds link in string of <img> or <script> html tag given by <) limits of file content.
     * @param start first position behind "<img" or "<script" tag start
     * @param end position of > at end of tag
     * @return optional pair of link limits, empty if no link is present
     */
    std::optional<std::pair<size_t , size_t>> findLinkSrc (const size_t & start, const size_t & end);

    /**
     * Finds link in string of <link> html tag given by <) limits of file content.
     * @param start first position behind <link tag start
     * @param end position of > at end of tag
     * @return optional pair of link limits, empty if no link is present or is not type "stylesheet"
     */
    std::optional<std::pair<size_t , size_t>> findLinkCss (const size_t & start, const size_t & end);


};


#endif //SEMESTRAL_CFILEHTML_H
