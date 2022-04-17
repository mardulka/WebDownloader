#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Read CLI information for application RUN
    CCli Cli;
    try{
        Cli.readSettings(argc, argv);
    } catch (invalid_argument & e){
        cout << e << "--> return 1" << endl;
        return 1;
    }

    //Enable connection with web and give control to download


    //Write

}