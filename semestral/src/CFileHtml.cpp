#include "CFileHtml.h"

using namespace std;

CFileHtml::CFileHtml(const string & name, int level, const string & relative_path)
        : CFile(name, relative_path, "html", CFileType::HTML), m_level(level){}
