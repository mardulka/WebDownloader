#include "CFileScript.h"

using namespace std;

CFileScript::CFileScript(CUrl url,  const string & relative_path)
        : CFile(move(url), relative_path, "js", CFileType::JS){}

list<CUrl> CFileScript::readLinks(){
    return {};
}

void CFileScript::notch(CStats & stats){
    ++stats.script_files;
}
