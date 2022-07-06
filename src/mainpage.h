/**
* @mainpage Web downloader application
 *
 * @version 0.5
 *
 *
 * @author Ing. Marek Čermak (cermam22@fit.cvut.cz)
 *
 *
 *
 * @section sec1 Description
 * Application provided downloading website recursively. Downloading is provided only from same domain and can be limited
 * by specifying number of recursion steps. Recursion steps are considered only for HTML files, other files are downloaded
 * every time if they are on the same domain.
 *
 * Css files are downloaded as default with related HTML file, pictures and JS files must be specifically set for download,
 * or links to the original files remain.
 *
 * Links outside domain or beyond recursion steps limit can lead to original target, or the link could be replaced
 * with link to prepared error page. Again it could be set by switch.
 *
 * Files are stored in predefined structure in folder. Target folder could be specified with application all.
 * If no target folder is specified, it uses current folder where the application was called.
 *
 *
 * @section sec2 Application call
 * Application uses Command Line Interface (CLI) only. Application call is described later.

 * **webdownloader <URL> [-l levels_no] [-p] [-j] [-e] [-d target_folder]**
 * -  **-l**    Define maximum level of links for download by following number. Level number is always related
 *              to starting link, which has level 0.
 * -  **-p**    Enable downloading pictures.
 * -  **-j**    Enable downloading script files.
 * -  **-e**    Enable option which every link leads outside domain or beyond limits replaces by link to prepared error page.
 * -  **-d**    Setting target folder for download by following path. Default path is folder where application is called.
 *
 * @note Application calls doesn't support combined parameter cals, i.e. '-pje'
 *
 *
 * @section sec3 Links download
 * -#   For HTML files are link downloaded from same host and defined max level. Downloading pictures, css nad js files can be set.
 * -#   If css files are set for downloading, it could be parsed for more links defined by url(~~) tags. Links defined
 *      by @import "~~" tags and url("data:~~") tag are not considered.
 * -#   Pictures and JS files are not parsed for anz other links.
*/