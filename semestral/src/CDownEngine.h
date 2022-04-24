#ifndef SEMESTRAL_CDOWNENGINE_H
#define SEMESTRAL_CDOWNENGINE_H

#include "CConnection.h"
#include "CSettings.h"
#include "CConnection.h"
#include "CFile.h"
#include "CFileHtml.h"
#include <queue>
#include <map>
#include <algorithm>
#include <memory>


/**
 * Class running download and saving
 */
class CDownEngine{

    /**
     * Map for indexing files by their original resource url
     */
    std::map <std::string, std::shared_ptr<CFile>> m_files;

    /**
     * Queue of files for further download and save
     */
    std::queue <std::shared_ptr<CFile>> m_queue;

    /**
     * Saved settings
     */
    std::shared_ptr <CSettings> m_settings;

    /**
     * Class which providing communication
     */
    CConnection m_connection;


public:

    /**
     * Contructor. Creates instance of engine and place starting URL into queue.
     * @param settings
     * @param connection
     */
    CDownEngine(const std::shared_ptr <CSettings> & settings);

    /**
     * Method starting downloading process;
     */
    void start();
};


#endif //SEMESTRAL_CDOWNENGINE_H
