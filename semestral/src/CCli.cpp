#include "CCli.h"

#include <utility>

using namespace std;

CCli::CCli(shared_ptr<CSettings> settings) : m_settings{std::move(settings)}{}

void CCli::readSettings(int argc, char ** argv){
    if (argc < 2){
        throw invalid_argument("No argument provided. Please use -h option to see help.");
    }

    for (auto i = 1 ; i < argc ; ++i){
        string arg = argv[i];

        if (argv[i][0] == '-'){
            if (arg == "-h"){
                printHelp();
                throw invalid_argument("");
            } else if (arg == "-p"){
                m_settings->pictures = true;
            } else if (arg == "-j"){
                m_settings->scripts = true;
            } else if (arg == "-e"){
                m_settings->errorPage = true;
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
                m_settings->levels = value;
            } else if (arg == "-d"){
                string strPath;
                if (i + 1 == argc) throw invalid_argument("No directory provided!");
                strPath = argv[++i];
                // throws exception for directory validate, it should be left to propagate further;
                readDirectory(strPath);
            } else{
                throw invalid_argument("Unknown parameter given.");
            }
        } else{
            if (!m_settings->url.empty())
                throw invalid_argument("Ambiguous URL defined.");
            m_settings->url = CUrl(arg);
        }
    }

    //if directory remain empty, use current directory.
    if (m_settings->targetFolder.empty()){
        m_settings->targetFolder = filesystem::current_path();
    }

}

void CCli::readDirectory(const string & strPath){
    filesystem::path tmpPath;
    try{
        tmpPath = filesystem::path(strPath);
    } catch (...){
        throw invalid_argument("Provided target path in not a path!");
    }

    if (!m_settings->targetFolder.empty() && !filesystem::equivalent(m_settings->targetFolder, tmpPath))
        throw invalid_argument("Ambiguous target path defined.");
    if (!filesystem::exists(tmpPath))
        throw invalid_argument("Provided path doesn't exist.");
    if (!filesystem::is_directory(tmpPath))
        throw invalid_argument("Provided path is not a directory");

    m_settings->targetFolder.swap(tmpPath);
}

void CCli::write(const string & text) const{
    cout << text << endl;
}

void CCli::printHelp(){

    string level1, level2;
    level1.append(2, ' ');
    level2.append(4, ' ');

    int optionsNameWidth = 15;

    cout << "Usage: webdownloader [OPTIONS] URL [URL...]" << endl;
    cout << "WARNING: CLI calls doesn't support combined options writing, like '-pje' !" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << level1 << "General Options:" << endl;
    cout << level2 << left << setw(optionsNameWidth) << "-h" << "Shows help for application CLI commands" << endl;
    cout << level2 << left << setw(optionsNameWidth) << "-p" << "Allows pictures download" << endl;
    cout << level2 << left << setw(optionsNameWidth) << "-j" << "Allows scripts download" << endl;
    cout << level2 << left << setw(optionsNameWidth) << "-e" << "Link beyond limit shows error page" << endl;
    cout << level1 << "Additional setting:" << endl;
    cout << level2 << left << setw(optionsNameWidth) << "-l NUMBER"
         << "Defines maximal link level for sites downloading." << endl;
    cout << level2 << left << setw(optionsNameWidth) << "-d FOLDER" << "Sets folder for website download." << endl;
}

void CCli::printSettings() const{
    //Header
    cout << setw(16) << setfill('-') << "";
    cout << "Download settings:";
    cout << setw(16) << setfill('-') << left << " " << endl << setfill(' ');
    //Body
    cout << setw(25) << left << "Pictures download: " << boolalpha << m_settings->pictures << endl;
    cout << setw(25) << left << "Scripts download: " << boolalpha << m_settings->scripts << endl;
    cout << setw(25) << left << "Error-page creation: " << boolalpha << m_settings->errorPage << endl;
    cout << setw(25) << left << "Levels: " << m_settings->levels << endl;
    cout << setw(25) << left << "Target folder: " << m_settings->targetFolder << endl;
    cout << setw(25) << left << "Starting URL: " << m_settings->url.getUrl() << endl;
    //Footer
    cout << setw(50) << setfill('-') << "" << endl;
}

void CCli::printStatistics(const shared_ptr<CStats> & stats) const{
    //Header
    cout << setw(14) << setfill('-') << "";
    cout << "Download statistics:";
    cout << setw(14) << setfill('-') << left << " " << endl << setfill(' ');
    //Body
    cout << setw(45) << left << "HTML files downloaded: " << setw(5)<< stats->html_files << endl;
    cout << setw(45) << left << "CSS files download: " << setw(5)<< stats->css_files << endl;
    cout << setw(45) << left << "Pictures downloaded: " << setw(5)<< stats->pictures << endl;
    cout << setw(45) << left << "JS files download: " << setw(5)<< stats->script_files << endl;
    cout << setw(45) << left << "Maximal level for download reached: " << setw(5)<< stats->levels << endl;
    //Footer
    cout << setw(48) << setfill('-') << "" << endl;
}



