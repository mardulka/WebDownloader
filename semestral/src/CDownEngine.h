#ifndef SEMESTRAL_CDOWNENGINE_H
#define SEMESTRAL_CDOWNENGINE_H

#include "CConnectionHttp.h"
#include "CSettings.h"
#include "CFile.h"
#include "CFileHtml.h"
#include "CConnection.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <set>


/**
 * Class running download and saving
 */
class CDownEngine{

    /**
     * Map for indexing file paths by their original resource url
     */
    std::unordered_map<std::string, std::filesystem::path> m_links_to_paths;

    /**
     * Set of the used filenames represented by absolute filesystem path
     */
    std::set<std::filesystem::path> m_used_filenames;

    /**
     * Queue of links for downloading file and parse for other links.
     * Second value stores information which level this file would be.
     */
    std::queue<std::pair<CUrl, int>> m_queue_download;

    /**
     * Queue of links for replacing links in files and save = process files
     */
    std::queue<std::shared_ptr<CFile>> m_queue_process;

    /**
     * Saved settings
     */
    std::shared_ptr<CSettings> m_settings;

    /**
     * Class which providing communication
     */
    std::shared_ptr<CConnection> m_connection;


public:

    /**
     * Contructor. Creates instance of engine and place starting URL into queue.
     * @param settings
     * @param connection
     */
    explicit CDownEngine(const std::shared_ptr<CSettings> & settings);

    /**
     * Method starting downloading process;
     */
    void start();

private:
    /**
     * Method downloads files from queue links, parse them for links.
     * Links are stored back in link queue, files in process queue.
     */
    void downloadFiles();

    /**
     * Method for processing files = replace links and save.
     */
    void processFiles();
};


#endif //SEMESTRAL_CDOWNENGINE_H
