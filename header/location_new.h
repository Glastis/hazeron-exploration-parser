/*
** Created by Glastis on 03/09/18.
*/

#ifndef DOWNLOADER_LOCATION_NEW_H
#define DOWNLOADER_LOCATION_NEW_H

#define BUFFER_NAME_SIZE                            100

#include "structure.h"

void                        init_galaxy(t_galaxy *galaxy, const char *name, t_sector **sector);
int                         add_galaxy(const char *xml, t_process *process);

#endif /* !DOWNLOADER_LOCATION_NEW_H */
