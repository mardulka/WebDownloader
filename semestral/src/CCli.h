#ifndef SEMESTRAL_CCLI_H
#define SEMESTRAL_CCLI_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <filesystem>
#include "CSettings.h"
#include "CStats.h"

/**
 * @class CCli
 * @brief Class providing communication with UI, CLI as default.
 */
class CCli{

    /**
     * @brief Defined default input stream.
     */
    constexpr static std::istream & m_cin = std::cin;

    /**
     * @brief Defined default output stream.
     */
    constexpr static std::ostream & m_cout = std::cout;

    /**
     * @brief Defined default err stream.
     */
    constexpr static std::ostream & m_err = std::cerr;

    /**
     * @brief Defined default output stream width.
     */
    constexpr static size_t TERMINAL_WIDTH = 200;

    /**
     * @brief Defined default ending width for log line ending.
     */
    constexpr static size_t LOG_END_WIDTH = 30;

public:

    /**
     * @brief Constructor - deleted
     */
    CCli() = delete;

    /**
     * @brief Reads given parameters and parse them into application settings.
     * @param argc number of parameters
     * @param argv parameters
     * @return true if settings was successfully read, false if application should end without error
     * @throws invalid_argument if there are mistake in program call attributes
     */
    static bool readSettings(int argc, char ** argv);

    /**
     * @brief Prints help for application
     */
    static void printHelp();

    /**
     * @brief Prints initial settings.
     */
    static void printSettings();

    /**
     * @brief Prints final statistics.
     */
    static void printStatistics();

    /**
     * @brief Prints simple text line to CLI.
     * @param text String of simple text to write
     */
    static void write(const std::string & text);

    /**
     * @brief Validates given string as system path and store it into settings class if is ok.
     * @param strPath String of path
     * @throws invalid_argument if given directory path is not valid or not exists
     */
    static void readDirectory(const std::string & strPath);

    /**
     * @brief Print main info log
     * @param string String of main info body
     */
    static void logInfoMain(const std::string & body);

    /**
     * @brief Print info line start with defined length. No new line is called, waiting for ending.
     * @param head String of line info heading.
     * @param body String of line info body
     */
    static void logInfoLineStart(const std::string & head, const std::string & body);

    /**
     * @brief Print info line end with defined length. Need to be append after line start and call new line.
     * @param status String of status which should be printed at line end.
     */
    static void logInfoLineEnd(const std::string & status);

    /**
     * @brief Prints error message
     * @param message String of error message
     */
    static void logError(const std::string & message);
};


#endif //SEMESTRAL_CCLI_H
