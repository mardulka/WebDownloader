#ifndef SEMESTRAL_CSETTINGS_H
#define SEMESTRAL_CSETTINGS_H

#include <filesystem>
#include "CUrl.h"

/**
 * @struct CSettings
 * @brief Struct for storing application settings
 */
struct CSettings{

    /**
     * @brief Defines whether pictures should be downloaded
     */
    static bool pictures;

    /**
     * @brief Defines whether scripts should be downloaded
     */
    static bool scripts;

    /**
     * @brief Defines whether links beyond limits should lead to error page (other option is remain original)
     */
    static bool errorPage;

    /**
     * @brief Defines number of link levels which should be download. {0} is top, so download only original page. {-1} means no limit.
     */
    static int levels;

    /**
     * @brief Defines target folder where downloaded files should be stored.
     */
    static std::filesystem::path targetFolder;

    /**
     * @brief Defines starting URL from which download should be started.
     */
    static CUrl url;

};


#endif //SEMESTRAL_CSETTINGS_H
