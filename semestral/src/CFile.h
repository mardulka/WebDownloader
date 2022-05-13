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
#include "CCli.h"

/**
 * @class CFile
 * @brief Class representing any type of file. Every file type is derived from this class.
 */
class CFile{
protected:

    /**
     * @brief File type represented by enum class value
     */
    CFileType m_type;

    /**
     * @brief File URL where was downloaded from
     */
    CUrl m_url;

    /**
     * @brief Relative filesystem path in folder for download
     */
    std::filesystem::path m_relative_path;

    /**
     * @brief File name
     */
    std::string m_file_name;

    /**
     * @brief File type extension
     */
    std::string m_file_ending;

    /**
     * @brief Absolute filesystem path of file
     */
    std::filesystem::path m_file_path;

    /**
     * @brief File content
     */
    std::string m_content;

public:

    /**
     * @brief Smallest file level in HTML links from starting URL
     */
    int m_level = 0;

    /**
     * @brief Constructor
     * @param m_url Original url of this file
     * @param relative_path Relative path for this file type
     * @param file_ending file extension
     * @param type File type value
     */
    CFile(CUrl m_url, const std::string & relative_path, std::string file_ending, const CFileType & type = CFileType::NO_TYPE)
            : m_type(type), m_url(std::move(m_url)), m_relative_path(relative_path),
              m_file_ending(std::move(file_ending)){}

    /**
     * @brief Destructor
     */
    virtual ~CFile() = default;

    /**
     * @brief Getter for type attribute.
     * @return File type.
     */
    [[nodiscard]] virtual CFileType getType() const;

    /**
     * @brief Getter for getting file name - compound of name and ending
     * @return
     */
    [[nodiscard]] virtual std::string getFileName() const;

    /**
     * @brief Returns file path including filename
     * @return file name with path
     */
    [[nodiscard]] const std::filesystem::path & getFilePath() const;

    /**
     * @brief Getter for content.
     * @note Used only for testing now.
     * @return reference on string of content
     */
    [[nodiscard]] const std::string & getContent() const;

    /**
     * @brief Setting content. If any is present, is deleted.
     * @param content String of content
     */
    virtual void setContent(std::string content);

    /**
     * @brief Reserves names for disk saving
     * @param targetFolder Folder where the file should be stored
     * @param used_names Set of already used names
     */
    virtual void generateName(const std::filesystem::path & targetFolder, std::set<std::filesystem::path> & used_names);

    /**
     * @brief Parses links in content.
     * @return list of all links
     */
    virtual std::list<CUrl> readLinks() = 0;

    /**
     * @brief Parses file and replace all links with path from map, if there record exists.
     * @param replacing_map Map containing information about links and their path replacements
     */
    virtual void replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map){};

    /**
     * @brief Provides file saving.
     * @throws invalid_argument if file cannot be created
     */
    virtual void save() const;

    /**
     * @brief Increases count of downloaded file into proper field in statistics.
     */
    virtual void notch() = 0;

protected:

    /**
     * @brief Checks if directory exists, if no is created
     * @param targetPath Path which should be checked for existence and being directory.
     * @throws invalid_argument if file exists and is not a directory
     */
    void checkDirectory(const std::filesystem::path & targetPath) const;

    /**
     * @brief Method for complete link to absolute based on the file URL
     * @param link link to be made absolute
     * @return Link if is absolute or was converted, nullopt for another link types
     */
    std::optional<std::string> makeLinkAbsolute(const std::string & link);

};


#endif //SEMESTRAL_CFILE_H