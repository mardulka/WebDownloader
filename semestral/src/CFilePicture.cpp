#include "CFilePicture.h"

using namespace std;

CFilePicture::CFilePicture(const string & name, const string & file_ending, const string & relative_path)
        : CFile(name, relative_path, file_ending, CFileType::PICTURE){}

void CFilePicture::save(const filesystem::path & targetFolder){
    filesystem::path target_path = targetFolder / m_relative_path;

    checkDirectory(target_path); //throws exception for not being a directory

    //saving by stream from content
    ofstream output;
    output.open(target_path.string() + '/' + m_file_name + '.' + m_file_ending, ios_base::out | ios_base::binary);
    if (!output.is_open()){
        throw invalid_argument("FILE: File cannot be created.");
    }


    cout << "Saving file: " << target_path.string() + '/' + m_file_name + '.' + m_file_ending << endl;
    output << m_content;
    output.close();
}
