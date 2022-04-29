//
// Created by marek on 17.04.2022.
//

#include "CFile.h"

#include <utility>

using namespace std;

CFileType CFile::getType(){
    return m_type;
}

void CFile::save(){
    checkDirectory(m_file_path.parent_path()); //throws exception for not being a directory

    //saving by stream from content
    ofstream output;
    output.open(m_file_path.string(), ios_base::out | ios_base::binary);
    if (!output.is_open()){
        throw invalid_argument("FILE: File cannot be created.");
    }

    cout << "Saving file: " << m_file_path.string() << endl;
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
    return m_file_path.filename();
}

void CFile::setContent(std::string content){
    m_content = std::move(content);
}

CFileType CFile::getType() const{
    return m_type;
}

void CFile::process(const std::unordered_map<CUrl, std::filesystem::path> & links_paths){
    try{
        replaceLinks();
        save();
    } catch (const invalid_argument & e){
        throw invalid_argument("FILE: Cannot process file:"s + e.what());
    }
}

void CFile::generateName(const filesystem::path & targetFolder, set<filesystem::path> & used_names){

    //generate filename
    m_file_name = m_url.getPath();
    for (auto item: m_file_name){
        if (item == '/')
            item = '_';
    }

    auto tmp_path = targetFolder / m_relative_path / (m_file_name + '.' + m_file_ending);

    for (int dist = 0 ; used_names.find(tmp_path) != used_names.end() ; ++dist){
        tmp_path = targetFolder / m_relative_path / (m_file_name + to_string(dist) + '.' + m_file_ending);
    }

    //save path in file
    m_file_path = tmp_path;

    //reserve name
    used_names.insert(m_file_path);


}
