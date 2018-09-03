/*
** Created by Glastis on 03/09/18.
*/

#include <stdio.h>
#include "header/location_new.h"
#include "header/utilities.h"
#include "header/xml_parser.h"
#include "header/process.h"

void                        search_and_set_atr(const char *xml, const char *atr_name, char **dest)
{
    char                    buff[BUFFER_NAME_SIZE];

    if (!get_atr_value(xml, atr_name, buff))
    {
        dest[0] = NULL;
    }
    dest[0] = str_coupler(buff, NULL);
}

/**
*** Galaxy
**/
void                        add_galaxy(const char *xml, t_process *process)
{
    t_galaxy                *galaxy_new;
    unsigned int            i;

    i = 0;
    galaxy_new = safe_malloc(1, sizeof(t_galaxy));
    while (process->galaxy[i++]);
    process->galaxy = safe_realloc(process->galaxy, i + 1, sizeof(t_galaxy *));
    search_and_set_atr(xml, FLAG_GALAXY_ATR_NAME, &galaxy_new->name);
    galaxy_new->sector = NULL;
    process->galaxy[i - 1] = galaxy_new;
    process->galaxy[i] = NULL;
}

/**
*** Sector
**/
void                        init_sector(const char *xml, t_sector *sector, t_galaxy **galaxy)
{
    search_and_set_atr(xml, FLAG_SECTOR_ATR_NAME, &sector->name);
    search_and_set_atr(xml, FLAG_SECTOR_ATR_COORD_X, &sector->coord_x);
    search_and_set_atr(xml, FLAG_SECTOR_ATR_COORD_Y, &sector->coord_y);
    search_and_set_atr(xml, FLAG_SECTOR_ATR_COORD_Z, &sector->coord_z);
    sector->galaxy = galaxy[0];
    sector->system = NULL;
}

void                        add_sector(const char *xml, t_galaxy **galaxy)
{
    t_sector                *sector_new;
    unsigned int            i;

    i = 0;
    sector_new = safe_malloc(1, sizeof(t_sector));
    init_sector(xml, sector_new, galaxy);
    while (galaxy[0]->sector[i++]);
    galaxy[0]->sector = safe_realloc(galaxy[0]->sector, i + 1, sizeof(t_sector *));
    galaxy[0]->sector[i - 1] = sector_new;
    galaxy[0]->sector[i] = NULL;
}

/**
*** System
**/
void                        init_system(const char *xml, t_system *system, t_sector **sector)
{
    search_and_set_atr(xml, FLAG_SYSTEM_ATR_NAME, &system->name);
    search_and_set_atr(xml, FLAG_SYSTEM_ATR_COORD_X, &system->coord_x);
    search_and_set_atr(xml, FLAG_SYSTEM_ATR_COORD_Y, &system->coord_y);
    search_and_set_atr(xml, FLAG_SYSTEM_ATR_COORD_Z, &system->coord_z);
    system->sector = sector[0];
    system->planet = NULL;
}

void                        add_system(const char *xml, t_sector **sector)
{
    t_system                *system_new;
    unsigned int            i;

    i = 0;
    system_new = safe_malloc(1, sizeof(t_system));
    init_system(xml, system_new, sector);
    while (sector[0]->system[i++]);
    sector[0]->system = safe_realloc(sector[0]->system, i + 1, sizeof(t_system *));
    sector[0]->system[i - 1] = system_new;
    sector[0]->system[i] = NULL;
}

/**
*** Planet
**/
static void                 planet_get_size(const char *xml, t_planet *planet)
{
    unsigned int            i;

    i = 0;
    if (!get_next_flag(xml, FLAG_PLANET_GEOSPHERE, &i, OPEN))
    {
        planet->size = NULL;
        return;
    }
    search_and_set_atr(xml, FLAG_PLANET_GEOSPHERE_ATR_SIZE, &planet->size);
}

void                        init_planet(const char *xml, t_planet *planet, t_system **system)
{

    search_and_set_atr(xml, FLAG_PLANET_ATR_NAME, &planet->name);
    search_and_set_atr(xml, FLAG_PLANET_ATR_TYPE, &planet->type);
    search_and_set_atr(xml, FLAG_PLANET_ATR_ZONE, &planet->orbiting_zone);
    planet->system = system[0];
    planet_get_size(xml, planet);
    planet->ressource = NULL;
}

void                        add_planet(const char *xml, t_system **system)
{
    t_planet                *planet_new;
    unsigned int            i;

    i = 0;
    planet_new = safe_malloc(1, sizeof(t_planet));
    init_planet(xml, planet_new, system);
    while (system[0]->planet[i++]);
    system[0]->planet = safe_realloc(system[0]->planet, i + 1, sizeof(t_planet *));
    system[0]->planet[i - 1] = planet_new;
    system[0]->planet[i] = NULL;
}

/**
*** Ressources
**/
void                        init_ressource(const char *xml, t_ressource *ressource, t_planet **planet)
{

    search_and_set_atr(xml, FLAG_RESSOURCE_ATR_NAME, &ressource->name);
    search_and_set_atr(xml, FLAG_RESSOURCE_ATR_ZONE_1, &ressource->quality_zone1_str);
    search_and_set_atr(xml, FLAG_RESSOURCE_ATR_ZONE_2, &ressource->quality_zone1_str);
    search_and_set_atr(xml, FLAG_RESSOURCE_ATR_ZONE_3, &ressource->quality_zone1_str);
    ressource->quality_zone1 = (ressource->quality_zone1_str) ? atoi(ressource->quality_zone1_str) : FALSE;
    ressource->quality_zone2 = (ressource->quality_zone2_str) ? atoi(ressource->quality_zone2_str) : FALSE;
    ressource->quality_zone3 = (ressource->quality_zone3_str) ? atoi(ressource->quality_zone3_str) : FALSE;
    ressource->planet = planet[0];
}

void                        add_ressource(const char *xml, t_planet **planet, t_process *process)
{
    t_ressource                *ressource_new;
    unsigned int            i;

    i = 0;
    ressource_new = safe_malloc(1, sizeof(t_ressource));
    init_ressource(xml, ressource_new, planet);
    while (planet[0]->ressource[i++]);
    planet[0]->ressource = safe_realloc(planet[0]->ressource, i + 1, sizeof(t_ressource *));
    planet[0]->ressource[i - 1] = ressource_new;
    planet[0]->ressource[i] = NULL;
    while (process->ressource[i++]);
    process->ressource = safe_realloc(process->ressource, i + 1, sizeof(t_ressource *));
    process->ressource[i - 1] = ressource_new;
    process->ressource[i] = NULL;
}