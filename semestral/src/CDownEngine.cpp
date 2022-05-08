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

    //create error page - if is required save
    auto errorPage = createErrorPage();
    if (m_settings->errorPage){
        errorPage->generateName(m_settings->targetFolder, m_used_filenames);
        errorPage->process(m_links_to_paths);
    }

    while (!m_queue_download.empty()){

        //get URL from queue
        auto link = m_queue_download.front().first;
        auto level = m_queue_download.front().second;
        m_queue_download.pop();

        //Check https - not supported, check host, check level
        if (link.getScheme() == "https" ||
            link.getHost() != m_settings->url.getHost() ||
            (m_settings->levels >= 0 && level > m_settings->levels)){
            if (m_settings->errorPage)
                m_links_to_paths.insert({link.getUrl(), errorPage->getFilePath()});
            continue;
        }

        //Check already downloaded
        if (m_links_to_paths.find(link.getUrl()) != m_links_to_paths.end()){
            continue;
        }

        //download file for given URL
        auto optFile = m_connection->getFile(link);
        if (!optFile.has_value())
            continue; //Error or is behind defined boundaries, therefore skipped.
        auto downloaded_file = optFile.value();

        //check settings for downloading pictures and scripts
        if ((!m_settings->pictures && downloaded_file->getType() == CFileType::PICTURE) ||
            (!m_settings->scripts && downloaded_file->getType() == CFileType::JS))
            continue;

        //set level
        downloaded_file->m_level = level;
        //generate filename and reserve it in given set
        downloaded_file->generateName(m_settings->targetFolder, m_used_filenames);

        //store in map of downloaded files
        m_links_to_paths.insert({link.getUrl(), downloaded_file->getFilePath()});

        //get links from file and save back into queue
        auto links_list = downloaded_file->readLinks();
        for (const auto & new_link: links_list)
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

shared_ptr<CFileHtml> CDownEngine::createErrorPage(){
    CUrl errorUrl(m_settings->url.getHost() + "/web_downloader/error_page");
    auto file = make_shared<CFileHtml>(errorUrl);
    file->setContent(R"(
<!DOCTYPE html>
<html>
<head>
    <style>
        body{
            background-color: black;
            vertical-align: center;
        }
        div {
            margin: auto;
            width: 50%;
            text-align: center;
        }
        h1   {color: white;}
        p    {color: red;}
    </style>
</head>
<body>
    <div>
        <h1>Link lead to external address or outside specified limits.</h1>
        <p>If you want to see this link to original site, make download again without error page switch on.</p>
    </div>
</body>
</html>
)");

    return file;
}
