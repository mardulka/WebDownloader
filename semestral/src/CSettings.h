#ifndef SEMESTRAL_CSETTINGS_H
#define SEMESTRAL_CSETTINGS_H

/**
 * Struct for storing application settings
 */
struct CSettings{
    /**
     * Defines wheter pictures should be downloaded
     */
    bool pictures = false;

    /**
     * Defines whether scripts should be downloaded
     */
    bool scripts = false;

    /**
     * Defines whetheer links beyond limits shoud lead to error page (other option is remain original)
     */
    bool errorPage = false;

    /**
     * Defines number of link levels which should be download. {0} is top, so download only original page. {-1} means no limit.
     */
    int levels = 0;

    /**
     * Defines target folder where downloaded files should be stored.
     */
    std::string targetFolder;

    /**
     * Defines starting URL from which download should be started.
     */
    std::string url;
};


#endif //SEMESTRAL_CSETTINGS_H
