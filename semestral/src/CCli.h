#ifndef SEMESTRAL_CCLI_H
#define SEMESTRAL_CCLI_H

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include "CSettings.h"
#include "CStats.h"

/**
 * @brief Class providing communication with UI, CLI as default.
 */
class CCli{

    /**
     * @brief Defined default input stream
     */
    constexpr static std::istream & m_cin = std::cin;

    /**
     * @brief Defined default output stream
     */
    constexpr static std::ostream & m_cout = std::cout;

    /**
     * @brief Defined default err stream
     */
    constexpr static std::ostream & m_err = std::cerr;

    /**
     * @brief Defined default output stream width
     */
    constexpr static size_t TERMINAL_WIDTH = 200;

    /**
     * @brief Defined default ending width for log line ending
     */
    constexpr static size_t LOG_END_WIDTH = 30;

public:

    CCli() = delete;

    /**
     * Method reads given parameters and parse them into application settings.
     * @param argc number of parameters
     * @param argv parameters
     */
    static void readSettings(int argc, char ** argv);

    /**
     * Method printing help for application
     */
    static void printHelp();

    /**
     * Method for printing settings.
     */
    static void printSettings();

    /**
     * Method for printing statistics.
     */
    static void printStatistics();

    /**
     * Method for printing simple text line to CLI
     * @param text
     */
    static void write(const std::string & text);

    /**
     * Method validate given string as system path and tore it into settings class if ok.
     * @param strPath
     */
    static void readDirectory(const std::string & strPath);

    /**
     * @brief Print main info log
     * @param string
     */
    static void logInfoMain(const std::string & string);

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
