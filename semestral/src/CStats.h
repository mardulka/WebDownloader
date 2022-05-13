#ifndef SEMESTRAL_CSTATS_H
#define SEMESTRAL_CSTATS_H

/**
 * @brief Structure for holding statistic information together
 */
struct CStats{
    /**
     * Number of downloaded HTML files
     */
    int html_files = 0;

    /**
     * Number of downloaded CSS files
     */
    int css_files = 0;

    /**
     * Number of downloaded pictures
     */
    int pictures = 0;

    /**
     * Number of downloaded JS files
     */
    int script_files = 0;

    /**
     * Number of max level
     */
    int levels = 0;

};


#endif //SEMESTRAL_CSTATS_H
