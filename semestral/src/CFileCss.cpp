#include "CFileCss.h"

using namespace std;

CFileCss::CFileCss(const string & name, const string & relative_path, const string & file_ending)
        : CFile(name, relative_path, file_ending, CFileType::CSS){}
