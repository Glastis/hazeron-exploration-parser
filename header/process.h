/*
** Created by Glastis on 30/08/18.
*/

#ifndef DOWNLOADER_PROCESS_H
#define DOWNLOADER_PROCESS_H

#include "structure.h"

#define FLAG_GALAXY                                 "galaxy"
#define FLAG_GALAXY_ATR_NAME                        "name"

#define FLAG_SECTOR                                 "sector"
#define FLAG_SECTOR_ATR_NAME                        "name"
#define FLAG_SECTOR_ATR_COORD_X                     "x"
#define FLAG_SECTOR_ATR_COORD_Y                     "y"
#define FLAG_SECTOR_ATR_COORD_Z                     "z"

#define FLAG_SYSTEM                                 "system"
#define FLAG_SYSTEM_ATR_NAME                        "name"
#define FLAG_SYSTEM_ATR_COORD_X                     "x"
#define FLAG_SYSTEM_ATR_COORD_Y                     "y"
#define FLAG_SYSTEM_ATR_COORD_Z                     "z"

#define FLAG_PLANET                                 "planet"
#define FLAG_PLANET_ATR_TYPE                        "bodyType"
#define FLAG_PLANET_ATR_ZONE                        "zone"
#define FLAG_PLANET_ATR_NAME                        "name"

#define FLAG_PLANET_GEOSPHERE                       "planet"
#define FLAG_PLANET_GEOSPHERE_ATR_SIZE              "diameter"

#define FLAG_RESSOURCE                              "resource"
#define FLAG_RESSOURCE_ATR_NAME                     "name"
#define FLAG_RESSOURCE_ATR_ZONE_1                   "qualityZone1"
#define FLAG_RESSOURCE_ATR_ZONE_2                   "qualityZone2"
#define FLAG_RESSOURCE_ATR_ZONE_3                   "qualityZone3"

#define ERROR_LOCATION_NOT_FOUND                    "Location not found"

int                         core_process(t_opt *opt);

#endif /* !DOWNLOADER_PROCESS_H */
