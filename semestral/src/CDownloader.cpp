#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Read CLI information for application RUN
    CCli Cli;

    try{
        Cli.readSettings(argc, argv);
    } catch (const invalid_argument & e){
        cout << ">>>" << e.what() << "<<<" << endl;
        return 1;
    }

    //Enable connection with web and give control to download


    //Write

}