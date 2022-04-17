#include "CCli.h"

void CCli::readSettings(int argc, char ** argv){
    if (argc < 2){
        write("No parameters given. Please specify required parameters.");
        printHelp();
        throw new std::invalid_argument("No parameters given.");
    }
}

void CCli::write(std::string text){
    std::cout << text << std::endl;
}

void CCli::printHelp(){

    std::string level1, level2;
    level1.append(2, ' ');
    level2.append(4, ' ');

    int optionsNameWidth = 7;

    std::cout << "Usage: webdownloader [OPTIONS] URL [URL...]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << level1 << "General Options:" << std::endl;
    std::cout << level2 << std::setw(optionsNameWidth) << std::left <<  "-h" << "Shows help for application CLI commands" << std::endl;
    std::cout << level2 << std::setw(optionsNameWidth) << std::left <<  "-p" << "Allows pictures download" << std::endl;
    std::cout << level2 << std::setw(optionsNameWidth) << std::left <<  "-j" << "Allows scripts download" << std::endl;
    std::cout << level2 << std::setw(optionsNameWidth) << std::left <<  "-e" << "Link beyond limit shows error page" << std::endl;
    std::cout << level1 << "Additional setting:" << std::endl;
    std::cout << level2 << std::setw(optionsNameWidth) << std::left <<  "-l NUMBER" << "Defines maximal link level for sites downloading." << std::endl;
    std::cout << level2 << std::setw(optionsNameWidth) << std::left <<  "-d FOLDER" << "Sets folder for website download." << std::endl;
}

