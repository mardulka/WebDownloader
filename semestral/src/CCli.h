#ifndef SEMESTRAL_CCLI_H
#define SEMESTRAL_CCLI_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

class CCli{

    bool pictures = false;
    bool scripts = false;
    bool errorPage = false;
    unsigned int levels = 0;
    std::string targetFolder;
    std::string url;


public:
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

    void write(std::string text);
};


#endif //SEMESTRAL_CCLI_H
