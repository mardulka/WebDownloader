#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Create struct holding settings together
    auto settings = make_shared<CSettings>();

    //Read CLI information for application RUN into prepared settings struct
    CCli Cli(settings);
    try{
        Cli.readSettings(argc, argv);
    } catch (const exception & e){
        Cli.write(e.what());
        return 1;
    }

    //Check settings
    Cli.printSettings();



    //TODO Give control to download and start.
    CDownEngine engine(settings);
    engine.start();


    //TODO testing
    /*
        CConnection connection;
        connection.sendGetRequest("/");
        cout << connection.getServerResponse() << endl;
        cout << "Stahujeme." << endl;
    */


    //TODO Print stats from engine



}