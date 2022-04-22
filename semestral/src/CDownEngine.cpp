#include "CDownEngine.h"

using namespace std;

CDownEngine::CDownEngine(const shared_ptr <CSettings> & settings)
        : m_settings(settings){
    shared_ptr<CFile> file = make_shared<CFileHtml>(m_settings->url);
    m_queue.push(file);
    m_files.insert({m_settings->url, file});
}

bool CDownEngine::connect(){
    try{
        m_connection.connect(m_settings->url);
    } catch (const exception & e){
        return false;
    }
    return true;
}

void CDownEngine::start(){

}