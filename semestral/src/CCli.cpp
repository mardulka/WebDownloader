#include "CCli.h"

#include <utility>

using namespace std;

void CCli::readSettings(int argc, char ** argv){

    if (argc < 2){
        throw invalid_argument("No argument provided. Please use -h option to see help.");
    }


    for (auto i = 1 ; i < argc ; ++i){
        string arg = argv[i];

        if (argv[i][0] == '-'){
            if (arg == "-h"){
                CCli::printHelp();
                throw invalid_argument("");
            } else if (arg == "-p"){
                CSettings::pictures = true;
            } else if (arg == "-j"){
                CSettings::scripts = true;
            } else if (arg == "-e"){
                CSettings::errorPage = true;
            } else if (arg == "-l"){
                if (i + 1 == argc) throw invalid_argument("No levels number provided!");
                int value;
                try{
                    value = stoi(argv[++i]);
                } catch (const invalid_argument & e){
                    throw invalid_argument("Level number has not number format!");
                } catch (const out_of_range & e1){
                    throw invalid_argument("Level number is too big!");
                }
                if (value < 0) throw invalid_argument("Levels number cannot be negative value!");
                CSettings::levels = value;
            } else if (arg == "-d"){
                string strPath;
                if (i + 1 == argc) throw invalid_argument("No directory provided!");
                strPath = argv[++i];
                // throws exception for directory validate, it should be left to propagate further;
                CCli::readDirectory(strPath);
            } else{
                throw invalid_argument("Unknown parameter given.");
            }
        } else{
            if (!CSettings::url.empty())
                throw invalid_argument("Ambiguous URL defined.");
            CSettings::url = CUrl(arg);
        }
    }

    //if directory remain empty, use current directory.
    if (CSettings::targetFolder.empty()){
        CSettings::targetFolder = filesystem::current_path();
    }

}

void CCli::readDirectory(const string & strPath){
    filesystem::path tmpPath;
    try{
        tmpPath = filesystem::path(strPath);
    } catch (...){
        throw invalid_argument("Provided target path in not a path!");
    }

    if (!CSettings::targetFolder.empty() && !filesystem::equivalent(CSettings::targetFolder, tmpPath))
        throw invalid_argument("Ambiguous target path defined.");
    if (!filesystem::exists(tmpPath))
        throw invalid_argument("Provided path doesn't exist.");
    if (!filesystem::is_directory(tmpPath))
        throw invalid_argument("Provided path is not a directory");

    CSettings::targetFolder.swap(tmpPath);
}

void CCli::write(const string & text){
    m_cout << text << endl;
}

void CCli::printHelp(){

    string level1, level2;
    level1.append(2, ' ');
    level2.append(4, ' ');

    int optionsNameWidth = 15;

    m_cout << "Usage: webdownloader [OPTIONS] URL [URL...]" << endl;
    m_cout << "WARNING: CLI calls doesn't support combined options writing, like '-pje' !" << endl;
    m_cout << endl;
    m_cout << "Options:" << endl;
    m_cout << level1 << "General Options:" << endl;
    m_cout << level2 << left << setw(optionsNameWidth) << "-h" << "Shows help for application CLI commands" << endl;
    m_cout << level2 << left << setw(optionsNameWidth) << "-p" << "Allows pictures download" << endl;
    m_cout << level2 << left << setw(optionsNameWidth) << "-j" << "Allows scripts download" << endl;
    m_cout << level2 << left << setw(optionsNameWidth) << "-e" << "Link beyond limit shows error page" << endl;
    m_cout << level1 << "Additional setting:" << endl;
    m_cout << level2 << left << setw(optionsNameWidth) << "-l NUMBER"
           << "Defines maximal link level for sites downloading." << endl;
    m_cout << level2 << left << setw(optionsNameWidth) << "-d FOLDER" << "Sets folder for website download." << endl;
}

void CCli::printSettings(){
    //Header
    m_cout << endl;
    m_cout << setw(16) << setfill('-') << "";
    m_cout << "Download settings:";
    m_cout << setw(16) << setfill('-') << left << " " << endl << setfill(' ');
    //Body
    m_cout << setw(25) << left << "Pictures download: " << boolalpha << CSettings::pictures << endl;
    m_cout << setw(25) << left << "Scripts download: " << boolalpha << CSettings::scripts << endl;
    m_cout << setw(25) << left << "Error-page creation: " << boolalpha << CSettings::errorPage << endl;
    m_cout << setw(25) << left << "Levels: " << CSettings::levels << endl;
    m_cout << setw(25) << left << "Target folder: " << CSettings::targetFolder << endl;
    m_cout << setw(25) << left << "Starting URL: " << CSettings::url.getUrl() << endl;
    //Footer
    m_cout << setw(50) << setfill('-') << "" << endl;
}

void CCli::printStatistics(){
    //Header
    m_cout << endl;
    m_cout << setw(14) << setfill('-') << "";
    m_cout << "Download statistics:";
    m_cout << setw(14) << setfill('-') << left << " " << endl << setfill(' ');
    //Body
    m_cout << setw(45) << left << "HTML files downloaded: " << setw(5) << CStats::html_files << endl;
    m_cout << setw(45) << left << "CSS files download: " << setw(5) << CStats::css_files << endl;
    m_cout << setw(45) << left << "Pictures downloaded: " << setw(5) << CStats::pictures << endl;
    m_cout << setw(45) << left << "JS files download: " << setw(5) << CStats::script_files << endl;
    m_cout << setw(45) << left << "Maximal level for download reached: " << setw(5) << CStats::levels << endl;
    //Footer
    m_cout << setw(48) << setfill('-') << "" << endl;
}

void CCli::logInfoMain(const string & body){
    string content = "INFO: "s + body;

    m_cout << setw(content.length()) << setfill('-') << "" << endl;
    m_cout << content << endl;
    m_cout << setw(content.length()) << setfill('-') << "" << endl;
}

void CCli::logInfoLineStart(const string & head, const string & body){
    size_t length = TERMINAL_WIDTH - LOG_END_WIDTH;
    string content = string(head + ": "s + body);
    //if is shorter or equal, print as is
    if (content.length() <= length)
        m_cout << setw(length) << left << setfill(' ') << content << flush;
    else{
        // if is longer, shorten and make space for ...
        m_cout << content.substr(0, length - 3) << "..."s << flush;
    }
}

void CCli::logInfoLineEnd(const string & status){
    string content = string("["s + status + "]"s);
    cout << setw(LOG_END_WIDTH) << right << setfill(' ') << content << endl;
}

void CCli::logError(const string & message){
    m_err << "ERROR: " << message << endl;
}
