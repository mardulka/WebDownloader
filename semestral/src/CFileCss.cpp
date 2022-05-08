#include "CFileCss.h"

#include <utility>

using namespace std;

CFileCss::CFileCss(CUrl url,  const string & relative_path)
        : CFile(std::move(url), relative_path, "css", CFileType::CSS){}

void CFileCss::replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map){
    //TODO parse html to get links
    //TODO for every link replace from map with path
}

list<CUrl> CFileCss::readLinks(){
    return {};
}
