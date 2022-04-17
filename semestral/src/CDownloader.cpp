#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    CSettings settings;
    //Read CLI information for application RUN
    CCli Cli(settings);

    try{
        Cli.readSettings(argc, argv);
    } catch (const invalid_argument & e){
        string message = e.what();
        Cli.write(">>>" + message + "<<<");
        return 1;
    }

    //TODO validate URL + Folder

    //Enable connection with web and give control to download


    //Write

}