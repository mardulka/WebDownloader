#include "CFileHtml.h"

using namespace std;

CFileHtml::CFileHtml(const string & name, const string & relative_path = "/subpages")
        : CFile(name, relative_path, "html", CFileType::HTML){}
