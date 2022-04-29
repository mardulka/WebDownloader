#include "CFileHtml.h"

#include <utility>

using namespace std;

CFileHtml::CFileHtml(CUrl url,const string & name, const string & relative_path)
        : CFile(std::move(url), name, relative_path, "html", CFileType::HTML){}

void CFileHtml::replaceLinks(){
    //TODO parse html to get links
    //TODO for every link replace from map with path (absolute / relative?)
}

list<CUrl> CFileHtml::readLinks(){
    return std::list<CUrl>();
}
