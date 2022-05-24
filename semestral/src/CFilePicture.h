#ifndef SEMESTRAL_CFILEPICTURE_H
#define SEMESTRAL_CFILEPICTURE_H

#include "CFile.h"
#include "CStats.h"

/**
 * @class CFilePicture
 * @extends CFile
 * @brief Class representing picture file.
 */
class CFilePicture : public CFile{
public:
    /**
     * @brief Constructor
     * @param url File URL
     * @param file_ending extension for filename representing picture format
     * @param relative_path File relative path for saving
     */
    CFilePicture(CUrl url, const std::string & file_ending, const std::string & relative_path = "pictures");

    /**
     * @brief Destructor
     */
    virtual ~CFilePicture() = default;

    /**
     * @brief Read links from file. But for picture does it nothing.
     * @note Only overrides pure virtual method.
     * @return empty list of links
     */
    std::list<CUrl> readLinks() override;

    /**
     * @brief Increments count of downloaded pictures in statistics.
     */
    void notch() override;
};


#endif //SEMESTRAL_CFILEPICTURE_H
