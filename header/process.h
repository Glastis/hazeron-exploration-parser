/*
** Created by Glastis on 30/08/18.
*/

#ifndef DOWNLOADER_PROCESS_H
#define DOWNLOADER_PROCESS_H

#include "structure.h"

#define FLAG_GALAXY_ATR_NAME                        "name"
#define FLAG_GALAXY                                 "galaxy"
#define FLAG_SECTOR_ATR_NAME                        "name"
#define FLAG_SECTOR                                 "sector"
#define FLAG_SYSTEM_ATR_NAME                        "name"
#define FLAG_SYSTEM                                 "system"

#define ERROR_LOCATION_NOT_FOUND                    "Location not found"

int                         core_process(t_opt *opt);

#endif /* !DOWNLOADER_PROCESS_H */
