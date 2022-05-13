#ifndef SEMESTRAL_CSETTINGS_H
#define SEMESTRAL_CSETTINGS_H

#include <filesystem>
#include "CUrl.h"

/**
 * Struct for storing application settings
 */
struct CSettings{
    /**
     * Defines whether pictures should be downloaded
     */
    static bool pictures;

    /**
     * Defines whether scripts should be downloaded
     */
    static bool scripts;

    /**
     * Defines whether links beyond limits should lead to error page (other option is remain original)
     */
    static bool errorPage;

    /**
     * Defines number of link levels which should be download. {0} is top, so download only original page. {-1} means no limit.
     */
    static int levels;

    /**
     * Defines target folder where downloaded files should be stored.
     */
    static std::filesystem::path targetFolder;

    /**
     * Defines starting URL from which download should be started.
     */
    static CUrl url;

};


#endif //SEMESTRAL_CSETTINGS_H
