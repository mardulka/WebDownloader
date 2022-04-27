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

    //Settings output
    Cli.printSettings();

    //Give control to download engine and start downloading.
    try{
        CDownEngine engine(settings);
        engine.start();
    } catch (const invalid_argument & e){
        Cli.write(e.what());
        return 2;
    }

    //TODO print downloading stats
    //engine.printStats();
}