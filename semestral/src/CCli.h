#ifndef SEMESTRAL_CCLI_H
#define SEMESTRAL_CCLI_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include "CSettings.h"

class CCli{

    std::shared_ptr<CSettings> m_settings;

public:

    explicit CCli(std::shared_ptr<CSettings> settings);

    /**
     * Method reads given parameters and parse them into application settings.
     * @param argc number of parameters
     * @param argv parameters
     */
    void readSettings(int argc, char ** argv);

    /**
     * Method printing help for application
     */
    void printHelp();

    /**
     * Method for printing settings.
     */
    void printSettings();

    /**
     * Method for printing simple text line to CLI
     * @param text
     */
    void write(std::string text);

    /**
     * Method validate given string as system path and tore it into settings class if ok.
     * @param strPath
     */
    void readDirectory(const std::string & strPath);
};


#endif //SEMESTRAL_CCLI_H
