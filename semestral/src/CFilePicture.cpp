#include "CFilePicture.h"



using namespace std;

CFilePicture::CFilePicture(CUrl url, const string & file_ending, const string & relative_path)
        : CFile(move(url), relative_path, file_ending, CFileType::PICTURE){}

list<CUrl> CFilePicture::readLinks(){
    return {};
}

void CFilePicture::notch(CStats & stats){
    ++stats.pictures;
}
