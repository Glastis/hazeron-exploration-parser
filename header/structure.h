/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_STRUCTURE_H
#define DOWNLOADER_STRUCTURE_H

enum                        e_loc
{
    GALAXY,
    SECTOR,
    SYSTEM,
    PLANET,
    ZONE
};

struct                      s_opt
{
    char                    *filename;
    char                    *outfile;
    char                    *system;
    char                    *sector;
    char                    *galaxy;
    char                    *ressource;
    int                     min_quality;
    int                     max_quality;
};

struct                      s_opt_init
{
    char                    *min_quality;
    char                    *max_quality;
};

struct                      s_location
{
    char                    *name;
    char                    *flag;
    enum e_loc              type;
};

struct                      s_galaxy
{
    char                    *name;
    struct s_sector         **sector;
};

struct                      s_sector
{
    char                    *name;
    char                    *coord_x;
    char                    *coord_y;
    char                    *coord_z;
    struct s_galaxy         *galaxy;
    struct s_system         **system;
};

struct                      s_system
{
    char                    *name;
    char                    *coord_x;
    char                    *coord_y;
    char                    *coord_z;
    struct s_sector         *sector;
    struct s_planet         **planet;
};

struct                      s_planet
{
    char                    *type;
    char                    *size;
    char                    *name;
    char                    *orbiting_zone;
    struct s_system         *system;
    struct s_ressource      **ressource;
};

struct                      s_ressource
{
    char                    *name;
    char                    *quality_zone1_str;
    char                    *quality_zone2_str;
    char                    *quality_zone3_str;
    int                     quality_zone1;
    int                     quality_zone2;
    int                     quality_zone3;
    struct s_planet         *planet;
};

struct                      s_process
{
    char                    *content;
    int                     fd_in;
    int                     fd_out;
    unsigned int            filesize;
    struct s_galaxy         **galaxy;
    struct s_location       *location;
    int                     (*open_location)(struct s_process *, unsigned int *i);
};

typedef struct s_opt        t_opt;
typedef struct s_opt_init   t_opt_init;
typedef struct s_process    t_process;
typedef struct s_location   t_location;
typedef struct s_galaxy     t_galaxy;
typedef struct s_sector     t_sector;
typedef struct s_system     t_system;
typedef struct s_planet     t_planet;
typedef struct s_ressource  t_ressource;

#endif /* !DOWNLOADER_STRUCTURE_H */

