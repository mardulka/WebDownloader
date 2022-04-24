#ifndef SEMESTRAL_CFILE_H
#define SEMESTRAL_CFILE_H

#include <string>
#include <filesystem>
#include <fstream>
#include "CFileType.h"

class CFile{
    CFileType m_type;

    std::filesystem::path m_relative_path = "/";
    std::string m_file_name = "";
    std::string m_file_ending = "file";

    std::string m_url;
    std::string m_content;

public:
    /**
     * Constructor
     * @param url Url of
     */
    CFile(const std::string & url) : m_url(url){}

    /**
     * Getter for type attribute.
     * @return File type.
     */
    CFileType getType();

    /**
     * Save content.
     * @return
     */
    void save(std::filesystem::path targetFolder);
};


#endif //SEMESTRAL_CFILE_H
