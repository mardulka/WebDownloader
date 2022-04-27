#include "CFileCss.h"

using namespace std;

CFileCss::CFileCss(const string & name, const string & relative_path)
        : CFile(name, relative_path, "css", CFileType::CSS){}
