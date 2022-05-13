#ifndef SEMESTRAL_CSTATS_H
#define SEMESTRAL_CSTATS_H

/**
 * @struct CStats
 * @brief Structure for holding statistic information together
 */
struct CStats{
    /**
     * @brief Number of downloaded HTML files
     */
    static int html_files;

    /**
     * @brief Number of downloaded CSS files
     */
    static int css_files;

    /**
     * @brief Number of downloaded pictures
     */
    static int pictures;

    /**
     * @brief Number of downloaded JS files
     */
    static int script_files;

    /**
     * @brief Number of max level
     */
    static int levels;

};


#endif //SEMESTRAL_CSTATS_H
