#include "CCli.h"

using namespace std;

CCli::CCli(CSettings & settings) : settings(settings){}

void CCli::readSettings(int argc, char ** argv){
    if (argc < 2){
        printHelp();
        throw invalid_argument("No parameters given. Please specify required parameters!");
    }

    for (auto i = 1 ; i < argc ; ++i){
        string arg = argv[i];

        if (argv[i][0] == '-'){
            if (arg == "-h"){
                printHelp();
                throw invalid_argument("Help page requested.");
            } else if (arg == "-p"){
                settings.pictures = true;
            } else if (arg == "-j"){
                settings.scripts = true;
            } else if (arg == "-e"){
                settings.errorPage = true;
            } else if (arg == "-l"){
                if (i + 1 == argc) throw invalid_argument("No levels number provided!");
                try{
                    settings.levels = stoul(argv[++i]);
                } catch (...){
                    throw invalid_argument("No levels number provided or given level number is too big!");
                }
            } else if (arg == "-d"){
                if (i + 1 == argc) throw invalid_argument("No directory provided!");
                settings.targetFolder = argv[++i];
            } else{
                throw invalid_argument("Unknown parameter given.");
            }
        } else{
            if (!settings.url.empty())
                throw invalid_argument("Ambiguous URL defined.");
            settings.url = arg;
        }
    }

}

void CCli::write(string text){
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

