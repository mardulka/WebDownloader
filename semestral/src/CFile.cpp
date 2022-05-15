//
// Created by marek on 17.04.2022.
//

#include "CFile.h"

#include <utility>

using namespace std;

CFileType CFile::getType() const{
    return m_type;
}

void CFile::save() const{
    checkDirectory(m_file_path.parent_path()); //throws exception for not being a directory

    //saving by stream from content
    ofstream output;
    output.open(m_file_path.string(), ios_base::out | ios_base::binary);
    if (!output.is_open()){
        throw invalid_argument("FILE: File cannot be created.");
    }
    CCli::logInfoLineStart("Saving file"s, absolute(m_file_path).string());
    output << m_content;
    output.close();
    CCli::logInfoLineEnd("File saved"s);
}

void CFile::checkDirectory(const std::filesystem::path & targetPath) const{
    if (!filesystem::exists(targetPath)){
        create_directory(targetPath);
    } else if (!filesystem::is_directory(targetPath)){
        throw invalid_argument("FILE: Target for saving is not a directory.");
    }
}

string CFile::getFileName() const{
    return m_file_path.filename();
}

const filesystem::path & CFile::getFilePath() const{
    return m_file_path;
}

void CFile::setContent(std::string content){
    m_content = std::move(content);
}

void CFile::generateName(const filesystem::path & targetFolder, set <filesystem::path> & used_names){

    //generate filename from host
    string filename_host = m_url.getHost();
    for (auto & item: filename_host){
        if (item == '.')
            item = '_';
    }

    //generate filename from path with cut first "/"
    auto filename_path = m_url.getPath().substr(1, m_url.getPath().size() - 1);
    for (auto & item: filename_path){
        if (item == '/')
            item = '_';
    }

    m_file_name = filename_host + "_" + filename_path;

    // if file is top level, it shouldn't be in sub-folder
    if (m_level == 0)
        m_relative_path = "";

    //create path, not checking if exists
    m_file_path = targetFolder / m_relative_path / m_file_name;

    //reserve name
    used_names.insert(m_file_path);

}

const string & CFile::getContent() const{
    return m_content;
}
