/*
** Created by Glastis on 30/08/18.
*/

#ifndef DOWNLOADER_PROCESS_H
#define DOWNLOADER_PROCESS_H

#include "structure.h"

#define READ_SIZE                                   1000u /* Must be greater than flags and ressources names */

#define FLAG_GALAXY_NAME_BEG                        "<galaxy name=\""
#define FLAG_GALAXY_NAME_END                        "\">"
#define FLAG_GALAXY_BEG                             FLAG_GALAXY_NAME_BEG
#define FLAG_GALAXY_END                             "</galaxy>"
#define FLAG_SECTOR_NAME_BEG                        "<sector name=\""
#define FLAG_SECTOR_NAME_END                        "\">"
#define FLAG_SECTOR_BEG                             FLAG_SECTOR_NAME_BEG
#define FLAG_SECTOR_END                             "</sector>"
#define FLAG_SYSTEM_NAME_BEG                        "<system name=\""
#define FLAG_SYSTEM_NAME_END                        "\">"
#define FLAG_SYSTEM_BEG                             FLAG_SYSTEM_NAME_BEG
#define FLAG_SYSTEM_END                             "</system>"

int                         core_process(t_opt *opt);

#endif /* !DOWNLOADER_PROCESS_H */
