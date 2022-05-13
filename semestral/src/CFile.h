#ifndef SEMESTRAL_CFILE_H
#define SEMESTRAL_CFILE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <utility>
#include <list>
#include <set>
#include <unordered_map>
#include "CFileType.h"
#include "CUrl.h"
#include "CStats.h"

class CFile{
protected:
    /**
     * File type represented by enum class value
     */
    CFileType m_type;

    /**
     * File URL where was downloaded from
     */
    CUrl m_url;

    /**
     * Relative filesystem path in folder for download
     */
    std::filesystem::path m_relative_path;

    /**
     * File name
     */
    std::string m_file_name;

    /**
     * File type extension
     */
    std::string m_file_ending;

    /**
     * Absolute filesystem path of file
     */
    std::filesystem::path m_file_path;

    /**
     * File content
     */
    std::string m_content;

public:

    /**
     * File level in links from starting URL
     */
    int m_level = 0;

    /**
     * Constructor
     * @param url Url of
     */
    CFile(CUrl m_url, const std::string & relative_path, std::string file_ending, const CFileType & type = CFileType::NO_TYPE)
            : m_type(type), m_url(std::move(m_url)), m_relative_path(relative_path),
              m_file_ending(std::move(file_ending)){}

    /**
     * Destructor
     */
    virtual ~CFile() = default;

    /**
     * Getter for type attribute.
     * @return File type.
     */
    [[nodiscard]] virtual CFileType getType() const;

    /**
     * Getter for getting file name - compound of name and ending
     * @return
     */
    [[nodiscard]] virtual std::string getFileName() const;

    /**
     * Method returns file path including filename
     * @return file name with path
     */
    [[nodiscard]] const std::filesystem::path & getFilePath() const;

    /**
     * Helping method for getting content. Used only for testing now.
     * @return reference on string of content
     */
    [[nodiscard]] const std::string & getContent() const;

    /**
     * Method for assigning content. If any is present, is deleted.
     * @param content
     */
    virtual void setContent(std::string content);

    /**
     * Method for reserving names
     * @param targetFolder
     * @param used_names
     */
    virtual void generateName(const std::filesystem::path & targetFolder, std::set<std::filesystem::path> & used_names);

    /**
     * Method for parsing links in content. PURE VIRTUAL
     * @return list of all links
     */
    virtual std::list<CUrl> readLinks() = 0;

    /**
     * Method for replacing links in content. PURE VIRTUAL
     */
    virtual void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map) = 0;

    /**
     * Method providing file saving. VIRTUAL
     */
    virtual void save() const;

    /**
     * @brief Increase count of downloaded file into proper field in statistics.
     * @param stats Struct of statistic data.
     */
    virtual void notch(CStats & stats) = 0;

protected:

    /**
     * Checking if directory exists, if no it is created, it exists and is not a directory, throws INVALID ARGUMENT EXCEPTION.
     * @param targetPath Path which should be checked for existence and being directory.
     */
    void checkDirectory(const std::filesystem::path & targetPath) const;

    /**
     * Method for complete link to absolute based on the file URL
     * @param link link to be made absolute
     * @return Link if is absolute or was converted, nullopt for another link types
     */
    std::optional<std::string> makeLinkAbsolute(const std::string & link);

};


#endif //SEMESTRAL_CFILE_H