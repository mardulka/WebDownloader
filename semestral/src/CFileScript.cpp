#include "CFileScript.h"

#include <utility>

using namespace std;

CFileScript::CFileScript(CUrl url,  const string & relative_path)
        : CFile(std::move(url), relative_path, "js", CFileType::JS){}

list<CUrl> CFileScript::readLinks(){
    return {};
}

void CFileScript::replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map){
    //TODO parse html to get links
    //TODO for every link replace from map with path
}
