#include "CFileHtml.h"

using namespace std;

CFileHtml::CFileHtml(const string & name, int level, const string & relative_path)
        : CFile(name, relative_path, "html", CFileType::HTML){
    if(level <=0){
        m_relative_path = "";
    }
}
