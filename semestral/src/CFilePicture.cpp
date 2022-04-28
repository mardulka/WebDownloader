#include "CFilePicture.h"

using namespace std;

CFilePicture::CFilePicture(const string & name, const string & file_ending, const string & relative_path)
        : CFile(name, relative_path, file_ending, CFileType::PICTURE){}

