#ifndef SEMESTRAL_CSTATS_H
#define SEMESTRAL_CSTATS_H

/**
 * @brief Structure for holding statistic information together
 */
struct CStats{
    /**
     * Number of downloaded HTML files
     */
    static int html_files;

    /**
     * Number of downloaded CSS files
     */
    static int css_files;

    /**
     * Number of downloaded pictures
     */
    static int pictures;

    /**
     * Number of downloaded JS files
     */
    static int script_files;

    /**
     * Number of max level
     */
    static int levels;

};


#endif //SEMESTRAL_CSTATS_H
