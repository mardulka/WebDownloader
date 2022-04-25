#include "CFilePicture.h"

CFilePicture::CFilePicture(const string & name, const string & relative_path, const string & file_ending)
        : CFile(name, relative_path, file_ending){
    m_type = CFileType::PICTURE;
}

void CFilePicture::save(std::filesystem::path targetFolder){
    filesystem::path target_path = filesystem::path(targetFolder / m_relative_path);

    checkDirectory(target_path); //throws exception for not being a directory

    //saving by stream from content
    fstream output;
    output.open(target_path.string() + m_file_name + '.' + m_file_ending, ios_base::out | ios_base::binary);
    if (!output.is_open()){
        throw new invalid_argument("FILE: File cannot be created.");
    }

    output << m_content;
    output.close();
}
