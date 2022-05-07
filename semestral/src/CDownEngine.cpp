#include "CDownEngine.h"

using namespace std;

CDownEngine::CDownEngine(const shared_ptr<CSettings> & settings) : m_settings(settings),
                                                                   m_connection(make_shared<CConnectionHttp>()){}

void CDownEngine::start(){

    //Create starting file
    cout << ">> Downloading starting file." << endl; //TODO log
    auto optFile = m_connection->getFile(m_settings->url);
    if (!optFile.has_value())
        throw invalid_argument("URL is not valid.");
    auto start_file = optFile.value();

    //check starting file type
    if (start_file->getType() != CFileType::HTML){
        throw invalid_argument("Starting URL must be a web page, not resource.");
    }

    //generate filename and reserve it in given set
    start_file->generateName(m_settings->targetFolder, m_used_filenames);

    //store in map of downloaded files
    m_links_to_paths.insert({m_settings->url.getUrl(), "Filename"}); //TODO filename

    //parse links from first file
    auto links_list = start_file->readLinks();
    for (const auto & link: links_list)
        m_queue_download.push({link, 1});
    //put first file into queue for processing
    m_queue_process.push(start_file);

    //download files from links queue
    downloadFiles();

    //process all files in process queue
    processFiles();

    //TODO log of CLI output
    cout << "All done!" << endl; //TODO log
}

void CDownEngine::downloadFiles(){
    cout << ">> Starting downloading linked files." << endl; //TODO log
    while (!m_queue_download.empty()){

        //get URL from queue
        auto link = m_queue_download.front();
        m_queue_download.pop();

        //Check https - not supported, check host, check level
        if (link.first.getScheme() == "https" ||
            link.first.getHost() != m_settings->url.getHost() ||
            (m_settings->levels >= 0 && link.second > m_settings->levels)){
            continue;
        }

        /*
        //Check already downloaded
        if (){

        }
*/

        //download file for given URL
        auto optFile = m_connection->getFile(link.first);
        if (!optFile.has_value())
            continue; //Error or is behind defined boundaries, therefore skipped.
        auto downloaded_file = optFile.value();

        //store in map of downloaded files
        m_links_to_paths.insert({m_settings->url.getUrl(), "Filename"}); //TODO filename

        //set level
        downloaded_file->m_level = link.second;
        //generate filename and reserve it in given set
        downloaded_file->generateName(m_settings->targetFolder, m_used_filenames);

        //get links from file and save back into queue - only if same link is not already done
        auto links_list = downloaded_file->readLinks();
        for (const auto & new_link: links_list)
            if (m_links_to_paths.find(new_link.getUrl()) == m_links_to_paths.end())
                m_queue_download.push({new_link, downloaded_file->m_level + 1});

        //put file in process queue
        m_queue_process.push(downloaded_file);
    }
    cout << ">> All linked files downloaded." << endl; //TODO log
}

void CDownEngine::processFiles(){
    cout << ">> Starting processing downloaded files." << endl; //TODO log
    while (!m_queue_process.empty()){

        //get file from queue
        auto file = m_queue_process.front();
        m_queue_process.pop();

        //call process method in file
        //TODO exception?
        file->process(m_links_to_paths);
    }
    cout << ">> All downloaded files processed." << endl; //TODO log
}
