#ifndef SEMESTRAL_CSETTINGS_H
#define SEMESTRAL_CSETTINGS_H


struct CSettings{
    bool pictures = false;
    bool scripts = false;
    bool errorPage = false;
    unsigned int levels = 0;
    std::string targetFolder;
    std::string url;
};


#endif //SEMESTRAL_CSETTINGS_H
