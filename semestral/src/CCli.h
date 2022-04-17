#ifndef SEMESTRAL_CCLI_H
#define SEMESTRAL_CCLI_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include "CSettings.h"

class CCli{

    CSettings & settings;

public:

    explicit CCli(CSettings & settings);

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
     * Method for printing simple text line to CLI
     * @param text
     */
    void write(std::string text);
};


#endif //SEMESTRAL_CCLI_H
