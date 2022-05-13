#include "CDownloader.h"

using namespace std;

int main(int argc, char ** argv){
    //Create struct holding settings and statistics
    auto settings = make_shared<CSettings>();
    auto statistics = make_shared<CStats>();

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
        CDownEngine engine(settings, statistics);
        engine.start();
    } catch (const invalid_argument & e){
        Cli.write(e.what());
        return 2;
    } catch (const filesystem::filesystem_error & fe){
        Cli.write(fe.what());
        return 5;
    } catch (...){
        Cli.write("Unknown ERROR occurred!");
    }

    //Print stats at program end
    Cli.printStatistics(statistics);

    return 0;
}