#ifndef SEMESTRAL_CDOWNENGINE_H
#define SEMESTRAL_CDOWNENGINE_H

#include "CConnectionHttp.h"
#include "CSettings.h"
#include "CFile.h"
#include "CFileHtml.h"
#include "CConnection.h"
#include "CStats.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <set>
#include <unordered_set>


/**
 * @class CDownEngine
 * @brief Class which actually running download and saving for files.
 */
class CDownEngine{

    /**
     * @brief Map for indexing file paths by their original resource url
     */
    std::unordered_map<std::string, std::filesystem::path> m_links_to_paths;

    /**
     * @brief Set of already downloaded links
     */
    std::unordered_set<std::string> m_downloaded_links;

    /**
     * @brief Set of the used filenames represented by absolute filesystem path
     */
    std::set<std::filesystem::path> m_used_filenames;

    /**
     * @brief Queue of links for downloading file and parse for other links.
     * @note Second value stores information which level this file would be.
     */
    std::queue<std::pair<CUrl, int>> m_queue_download;

    /**
     * @brief Queue of links for replacing links in files and save
     */
    std::queue<std::shared_ptr<CFile>> m_queue_process;

    /**
     * @brief Class which providing communication
     */
    std::shared_ptr<CConnection> m_connection;


public:

    /**
     * @brief Constructor creates instance and initialize CConnection class instance member attribute.
     */
    explicit CDownEngine();

    /**
     * @brief Starting download process;
     * @throws invalid_argument if starting URL is not valid or is not HTML file
     */
    void start();

private:

    /**
     * @brief Downloads files from queue links, parse them for links.
     * @note Links are stored back in link queue, files in process queue.
     */
    void downloadFiles();

    /**
     * @brief Processes files = replace links and save.
     */
    void processFiles();

    /**
     * @brief Creates Error page as HTML file instance if necessary.
     * @return Shared pointer to HTML file instance representing Error page
     */
    std::shared_ptr<CFileHtml> createErrorPage();
};


#endif //SEMESTRAL_CDOWNENGINE_H
