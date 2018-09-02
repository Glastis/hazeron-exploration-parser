/*
** Created by Glastis on 30/07/18.
*/

#ifndef DOWNLOADER_STRUCTURE_H
#define DOWNLOADER_STRUCTURE_H

enum                        e_loc
{
    GALAXY,
    SECTOR,
    SYSTEM
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

struct                      s_process
{
    char                    *content;
    int                     fd_in;
    int                     fd_out;
    unsigned int            filesize;
    struct s_location       *location;
    int                     (*open_location)(struct s_process *, unsigned int *i);
};

typedef struct s_opt        t_opt;
typedef struct s_opt_init   t_opt_init;
typedef struct s_process    t_process;
typedef struct s_location   t_location;

#endif /* !DOWNLOADER_STRUCTURE_H */

