#include "CFileCss.h"

#include <utility>

using namespace std;

CFileCss::CFileCss(CUrl url, const string & name, const string & relative_path)
        : CFile(std::move(url), name, relative_path, "css", CFileType::CSS){}

void CFileCss::replaceLinks(){
    //TODO parse html to get links
    //TODO for every link replace from map with path (absolute / relative?)
}

list<CUrl> CFileCss::readLinks(){
    return std::list<CUrl>();
}
