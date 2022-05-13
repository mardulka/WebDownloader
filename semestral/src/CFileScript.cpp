#include "CFileScript.h"

using namespace std;

CFileScript::CFileScript(CUrl url,  const string & relative_path)
        : CFile(move(url), relative_path, "js", CFileType::JS){}

list<CUrl> CFileScript::readLinks(){
    return {};
}

void CFileScript::replaceLinks(const unordered_map<string, filesystem::path> & replacing_map){
    //TODO parse html to get links
    //TODO for every link replace from map with path
}

void CFileScript::notch(CStats & stats){
    ++stats.script_files;
}
