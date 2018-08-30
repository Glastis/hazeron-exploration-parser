/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_STRUCTURE_H
#define DOWNLOADER_STRUCTURE_H

struct                      s_opt
{
    char                    *filename;
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

struct                      s_process
{
    int                     system_opened;
    int                     sector_opened;
    int                     galaxy_opened;
};

typedef struct s_opt        t_opt;
typedef struct s_opt_init   t_opt_init;
typedef struct s_process    t_process;

#endif /* !DOWNLOADER_STRUCTURE_H */

