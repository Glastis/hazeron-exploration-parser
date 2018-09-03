/*
** Created by Glastis on 02/09/18.
*/

#ifndef DOWNLOADER_LOCATION_H
#define DOWNLOADER_LOCATION_H

#define SYSTEM_EOD_UNEXPLORED                       "Unexplored"
#define SYSTEM_EOD_EXPLORED                         "Explored"
#define SYSTEM_EOD_SURVEYED                         "Surveyed"

#define SYSTEM_EOD_ATR_NAME                         "eod"

#include "structure.h"

enum                        e_eod
{
    UNEXPLORED,
    EXPLORED,
    SURVEYED
};

typedef enum e_eod          t_eod;

int                         is_system_eod(const char *str, t_eod eod);
int                         is_system_surveyed(const char *str);
int                         check_and_add_ressource(t_opt *opt, t_process *process, const char *str);

#endif /* !DOWNLOADER_LOCATION_H */
