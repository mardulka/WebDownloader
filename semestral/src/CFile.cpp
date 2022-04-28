//
// Created by marek on 17.04.2022.
//

#include "CFile.h"

#include <utility>

using namespace std;

CFileType CFile::getType(){
    return m_type;
}

void CFile::save(const std::filesystem::path & targetFolder){
    filesystem::path target_path = targetFolder / m_relative_path;
    filesystem::path file_path = target_path / (m_file_name + '.' + m_file_ending);

    checkDirectory(target_path); //throws exception for not being a directory

    //saving by stream from content
    ofstream output;
    output.open(file_path.string(), ios_base::out | ios_base::binary);
    if (!output.is_open()){
        throw invalid_argument("FILE: File cannot be created.");
    }

    cout << "Saving file: " << file_path.string() << endl;
    output << m_content;
    output.close();
}

void CFile::checkDirectory(const std::filesystem::path & targetPath){
    if (!filesystem::exists(targetPath)){
        create_directory(targetPath);
    } else if (!filesystem::is_directory(targetPath)){
        throw invalid_argument("FILE: Target for saving is not a directory.");
    }
}

string CFile::getFileName() const{
    return m_file_name + "." + m_file_ending;
}

void CFile::setContent(std::string content){
    m_content = std::move(content);
}

CFileType CFile::getType() const{
    return m_type;
}
