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

    //TODO Message to CLI or log
    cout << "Saving file: " << absolute(m_file_path).string() << setw(10) << setfill('.') << "" << flush;
    output << m_content;
    output.close();
    cout << "File saved." << endl;
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

void CFile::setContent(std::string content){
    m_content = std::move(content);
}

void CFile::process(const std::unordered_map<std::string, std::filesystem::path> & links_paths){
    try{
        replaceLinks();
        save();
    } catch (const invalid_argument & e){
        throw invalid_argument("FILE: Cannot process file:"s + e.what());
    }
}

void CFile::generateName(const filesystem::path & targetFolder, set<filesystem::path> & used_names){

    //generate filename from path with cut first "/"
    m_file_name = m_url.getPath().substr(1, m_url.getPath().size() - 1);
    for (auto & item: m_file_name){
        if (item == '/')
            item = '_';
    }

    // if file is top level, it shouldn't be in sub-folder
    if (m_level == 0)
        m_relative_path = "";

    //create path, check if exists, if so give first free number behind name
    auto tmp_path = targetFolder / m_relative_path / (m_file_name + '.' + m_file_ending);
    for (int dist = 0 ; used_names.find(tmp_path) != used_names.end() ; ++dist){
        tmp_path = targetFolder / m_relative_path / (m_file_name + to_string(dist) + '.' + m_file_ending);
    }

    //save path in file
    m_file_path = tmp_path;

    //reserve name
    used_names.insert(m_file_path);

}

optional<std::string> CFile::makeLinkAbsolute(const string & link){
    cout << "Making absolut link from link: " << link << endl; //TODO debug

    if (link.empty())
        return nullopt;

    auto iter = link.begin();
    if (link.front() == '.')
        ++iter;

    if (*iter == '/' && *(iter + 1) == '/')
        return m_url.getScheme().append(":").append(link);
    if (*iter == '/' && isalnum(*(iter + 1)))
        return m_url.getScheme().append("://").append(m_url.getHost()).append(link);
    if ((link.size() >= 7 && string(iter, iter + 7) == "http://")
        || (link.size() >= 8 && string(iter, iter + 8) == "https://"))
        return link;
    else
        return m_url.getScheme().append("://").append(m_url.getHost()).append("/").append(link);

}
