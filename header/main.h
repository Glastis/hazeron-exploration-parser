/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_MAIN_H
#define DOWNLOADER_MAIN_H

#define OPT_FILE                                    "--file"
#define OPT_FILE_SHORT                              "-f"
#define OPT_OUTPUT                                  "--output"
#define OPT_OUTPUT_SHORT                            "-o"
#define OPT_GALAXY                                  "--galaxy"
#define OPT_GALAXY_SHORT                            "-g"
#define OPT_SECTOR                                  "--sector"
#define OPT_SECTOR_SHORT                            "-s"
#define OPT_SYSTEM                                  "--system"
#define OPT_SYSTEM_SHORT                            "-ss"
#define OPT_RESSOURCE                               "--ressource"
#define OPT_RESSOURCE_SHORT                         "-r"
#define OPT_QUALITY_MIN                             "--quality-min"
#define OPT_QUALITY_MIN_SHORT                       "-qm"
#define OPT_QUALITY_MAX                             "--quality-max"
#define OPT_QUALITY_MAX_SHORT                       "-qx"

#define OPT_HELP                                    "--help"
#define OPT_HELP_SHOT                               "-h"

#define ERROR_ARGUMENT_IGNORED                      "Argument ignored/unknown. See --help or -h to get usage."
#define ERROR_ARGUMENT_VALUE                        "Argument must be followed by value. See --help or -h to get usage."
#define ERROR_ARGUMENT_MULTIPLE_LOCATION            "Multiple locations. That's galaxy OR sector OR system."


#define THREAD_DEFAULT_DOWNLOAD                     4u
#define THREAD_DEFAULT_CONVERT                      4u
#define THREAD_MIN_DOWNLOAD                         1u
#define THREAD_MIN_CONVERT                          1u

int                         main(int ac, const char **av);

#endif /* !DOWNLOADER_MAIN_H */
