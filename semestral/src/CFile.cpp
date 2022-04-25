//
// Created by marek on 17.04.2022.
//

#include "CFile.h"

using namespace std;

CFileType CFile::getType(){
    return m_type;
}

void CFile::save(std::filesystem::path targetFolder){
    filesystem::path target_path = filesystem::path(targetFolder / m_relative_path);

    checkDirectory(target_path); //throws exception for not being a directory

    //saving by stream from content
    fstream output;
    output.open(target_path.string() + m_file_name + '.' + m_file_ending, ios_base::out);
    if (!output.is_open()){
        throw new invalid_argument("FILE: File cannot be created.");
    }

    output << m_content;
    output.close();
}

void CFile::checkDirectory(std::filesystem::path targetPath){
    if (!filesystem::exists(targetPath)){
        create_directory(targetPath);
    } else if (!filesystem::is_directory(targetPath)){
        throw new invalid_argument("FILE: Target for saving is not a directory.");
    }
}

const std::string CFile::getFileName() const{
    return m_file_name + "." + m_file_ending;
}
