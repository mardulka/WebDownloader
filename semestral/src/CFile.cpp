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

    if (!filesystem::exists(target_path)){
        create_directory(target_path);
    } else if (!filesystem::is_directory(target_path)){
        throw new invalid_argument("FILE: Target for saving is not a directory.");
    }

    //saving by stream from content
    fstream output;
    output.open(target_path.string() + m_file_name + '.' + m_file_ending, ios_base::out);
    if (!output.is_open()){
        throw new invalid_argument("FILE: File cannot be created.");
    }

    output << m_content;
    output.close();


}
