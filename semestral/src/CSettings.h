#ifndef SEMESTRAL_CSETTINGS_H
#define SEMESTRAL_CSETTINGS_H

#include <filesystem>

/**
 * Struct for storing application settings
 */
struct CSettings{
    /**
     * Defines whether pictures should be downloaded
     */
    bool pictures;

    /**
     * Defines whether scripts should be downloaded
     */
    bool scripts;

    /**
     * Defines whether links beyond limits should lead to error page (other option is remain original)
     */
    bool errorPage;

    /**
     * Defines number of link levels which should be download. {0} is top, so download only original page. {-1} means no limit.
     */
    int levels = -1;

    /**
     * Defines target folder where downloaded files should be stored.
     */
    std::filesystem::path targetFolder;

    /**
     * Defines starting URL from which download should be started.
     */
    std::string url;

};


#endif //SEMESTRAL_CSETTINGS_H
