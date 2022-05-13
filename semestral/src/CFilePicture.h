#ifndef SEMESTRAL_CFILEPICTURE_H
#define SEMESTRAL_CFILEPICTURE_H

#include "CFile.h"
#include <utility>

class CFilePicture : public CFile{
public:
    /**
     * Constructor
     * @param url File URL
     * @param file_ending extension for filename representing picture format
     * @param relative_path File relative path for saving
     */
    CFilePicture(CUrl url, const std::string & file_ending, const std::string & relative_path = "pictures");

    /**
     * Destructor
     */
    virtual ~CFilePicture() = default;

    /**
     * In Picture file are no links at all. Override PURE VIRTUAL method.
     * @return empty list of links
     */
    std::list<CUrl> readLinks() override;

    /**
     * In Picture file are no links at all. Override PURE VIRTUAL method.
     */
    void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map) override;

    /**
     * @brief Increment count of downloaded pictures
     * @param stats Struct of statistic data.
     */
    void notch(CStats & stats) override;
};


#endif //SEMESTRAL_CFILEPICTURE_H
