#include "CDownEngine.h"

using namespace std;

CDownEngine::CDownEngine(): m_connection(make_shared<CConnectionHttp>()){}

void CDownEngine::start(){

    //Create starting file
    CCli::logInfoMain("Downloading starting file..."s);
    auto optFile = m_connection->getFile(CSettings::url);
    if (!optFile.has_value())
        throw invalid_argument("URL is not valid!"s);
    auto start_file = optFile.value();

    //check starting file type
    if (start_file->getType() != CFileType::HTML){
        throw invalid_argument("Starting URL must be a web page, not resource!"s);
    }

    //generate filename and reserve it in given set
    start_file->generateName(CSettings::targetFolder, m_used_filenames);

    //store in map of downloaded files
    m_links_to_paths.insert({CSettings::url.getUrl(), start_file->getFilePath()});

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

    CCli::logInfoMain("WEB downloading process completed..."s);
}

void CDownEngine::downloadFiles(){

    CCli::logInfoMain("Start downloading linked files..."s);

    //create error page - if is required save
    auto errorPage = createErrorPage();
    if (CSettings::errorPage){
        errorPage->m_level = numeric_limits<int>::max();
        errorPage->generateName(CSettings::targetFolder, m_used_filenames);
        errorPage->save();
    }

    while (!m_queue_download.empty()){

        //get URL from queue
        auto link = m_queue_download.front().first;
        auto level = m_queue_download.front().second;
        m_queue_download.pop();

        //Check https - not supported, check host
        if (link.getHost() != CSettings::url.getHost()){
            if (CSettings::errorPage)
                m_links_to_paths.insert({link.getUrl(), errorPage->getFilePath()});
            continue;
        }

        //Check already downloaded
        if (m_downloaded_links.find(link.getUrl()) != m_downloaded_links.end()){
            continue;
        }

        //download file for given URL and record into downloaded links set
        auto optFile = m_connection->getFile(link);
        m_downloaded_links.insert(link.getUrl());
        //Error or is behind defined boundaries, therefore skipped.
        if (!optFile.has_value()){
            continue;
        }
        auto downloaded_file = optFile.value();

        //check settings for downloading pictures and scripts
        if ((!CSettings::pictures && downloaded_file->getType() == CFileType::PICTURE) ||
            (!CSettings::scripts && downloaded_file->getType() == CFileType::JS))
            continue;

        //check level only for HTML file
        if (downloaded_file->getType() == CFileType::HTML && CSettings::levels >= 0 && level > CSettings::levels){
            if (CSettings::errorPage)
                m_links_to_paths.insert({link.getUrl(), errorPage->getFilePath()});
            continue;
        }

        //set level
        downloaded_file->m_level = level;
        //generate filename and reserve it in given set
        downloaded_file->generateName(CSettings::targetFolder, m_used_filenames);

        //store in map of downloaded files
        m_links_to_paths.insert({link.getUrl(), downloaded_file->getFilePath()});

        //get links from file and save back into queue
        auto links_list = downloaded_file->readLinks();
        for (const auto & new_link: links_list)
            m_queue_download.push({new_link, downloaded_file->m_level + 1});

        //put file in process queue
        m_queue_process.push(downloaded_file);
    }
}

void CDownEngine::processFiles(){

    CCli::logInfoMain("Start saving downloaded files..."s);
    while (!m_queue_process.empty()){

        //get file from queue
        auto file = m_queue_process.front();
        m_queue_process.pop();

        //call process method in file
        file->replaceLinks(m_links_to_paths);

        //save
        try{
            file->save();
            file->notch();
        } catch (...){
            CCli::logError("File cannot be saved!"s);
        }
    }

}

shared_ptr<CFileHtml> CDownEngine::createErrorPage(){
    CUrl errorUrl(CSettings::url.getHost() + "/web_downloader/error_page"s);
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
