#include "CFilePicture.h"

#include <utility>

using namespace std;

CFilePicture::CFilePicture(CUrl url, const string & file_ending, const string & relative_path)
        : CFile(std::move(url), relative_path, file_ending, CFileType::PICTURE){}

list<CUrl> CFilePicture::readLinks(){
    return {};
}

void CFilePicture::replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map){}

