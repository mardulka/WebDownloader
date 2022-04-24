#include "CDownEngine.h"

using namespace std;

CDownEngine::CDownEngine(const shared_ptr <CSettings> & settings) : m_settings(settings){
    //Create starting file
    auto rFile = m_connection.getFile(settings->url);
    if (rFile.has_value()){
        m_queue.push(rFile.value());
        m_files.insert({m_settings->url, rFile.value()});
    } else{
        throw new invalid_argument("URL is not valid.");
    }
}

void CDownEngine::start(){

    while (!m_queue.empty()){
        auto file = m_queue.front();
        m_queue.pop();

        if (file->getType() == CFileType::HTML){
            //TODO - if file could have links, parse links, download files, replace links;
        }

        file->save(m_settings->targetFolder); // TODO - some exception?
    }
}