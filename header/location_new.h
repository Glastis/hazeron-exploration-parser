/*
** Created by Glastis on 03/09/18.
*/

#ifndef DOWNLOADER_LOCATION_NEW_H
#define DOWNLOADER_LOCATION_NEW_H

#define BUFFER_NAME_SIZE                            100

#include "structure.h"

void                        search_and_set_atr(const char *xml, const char *atr_name, char **dest);
void                        add_galaxy(const char *xml, t_process *process);
void                        init_sector(const char *xml, t_sector *sector, t_galaxy **galaxy);
void                        add_sector(const char *xml, t_galaxy **galaxy);
void                        init_system(const char *xml, t_system *system, t_sector **sector);
void                        add_system(const char *xml, t_sector **sector);
static void                 planet_get_size(const char *xml, t_planet *planet);
void                        init_planet(const char *xml, t_planet *planet, t_system **system);
void                        add_planet(const char *xml, t_system **system);
void                        init_ressource(const char *xml, t_ressource *ressource, t_planet **planet);
void                        add_ressource(const char *xml, t_planet **planet, t_process *process);

#endif /* !DOWNLOADER_LOCATION_NEW_H */
