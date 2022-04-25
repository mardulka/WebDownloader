#ifndef SEMESTRAL_CFILE_H
#define SEMESTRAL_CFILE_H

#include <string>
#include <filesystem>
#include <fstream>
#include "CFileType.h"

class CFile{
protected:
    std::string m_file_name;
    std::filesystem::path m_relative_path;
    std::string m_file_ending;
    CFileType m_type;
    std::string m_content;

public:
    /**
     * Constructor
     * @param url Url of
     */
    CFile(const std::string & name, const std::string & relative_path, const std::string & file_ending, const CFileType & type = CFileType::NO_TYPE)
            : m_file_name(name), m_relative_path(relative_path), m_file_ending(file_ending), m_type(type){}

    /**
     * Getter for type attribute.
     * @return File type.
     */
    CFileType getType();

    /**
     * Getter for getting file name - compound of name and ending
     * @return
     */
    const std::string getFileName() const;

    /**
     * Save content.
     * @return
     */
    virtual void save(std::filesystem::path targetFolder);

protected:

    /**
     * Checking if directory exists, if no it is created, it exists and is not a directory, throws INVALID ARGUMENT EXCEPTION.
     * @param targetPath Path which should be checked for existence and being directory.
     */
    void checkDirectory(std::filesystem::path targetPath);
};


#endif //SEMESTRAL_CFILE_H
