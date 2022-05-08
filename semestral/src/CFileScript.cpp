#include "CFileScript.h"

#include <utility>

using namespace std;

CFileScript::CFileScript(CUrl url,  const string & relative_path)
        : CFile(std::move(url), relative_path, "js", CFileType::JS){}

void CFileScript::replaceLinks(){
    //TODO parse html to get links
    //TODO for every link replace from map with path (absolute / relative?)
}

list<CUrl> CFileScript::readLinks(){
    return {};
}
