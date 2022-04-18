#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Create struct holding settings together
    auto settings = make_shared<CSettings>();

    //Read CLI information for application RUN into prepared settings struct
    CCli Cli(settings);
    try{
        Cli.readSettings(argc, argv);
    } catch (const invalid_argument & e){
        string message = e.what();
        Cli.write(message);
        return 1;
    }

    //TODO validate URL in CConnection class first

    //TODO Enable connection with web and give control to download


    //TODO Write result

}