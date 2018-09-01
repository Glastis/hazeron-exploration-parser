/*
** Created by Glastis on 30/08/18.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "header/xml_parser.h"
#include "header/process.h"
#include "header/utilities.h"

static void                 open_location_galaxy(t_opt *opt, t_process *process, unsigned int *i)
{
    i[0] = move_to_flag(process->content, FLAG_GALAXY, FLAG_GALAXY_ATR_NAME, opt->galaxy);
}

static void                 open_location_sector(t_opt *opt, t_process *process, unsigned int *i)
{
    i[0] = move_to_flag(process->content, FLAG_SECTOR, FLAG_SECTOR_ATR_NAME, opt->sector);
}

static void                 open_location_system(t_opt *opt, t_process *process, unsigned int *i)
{
    i[0] = move_to_flag(process->content, FLAG_SYSTEM, FLAG_SYSTEM_ATR_NAME, opt->system);
}

static void                 init_process(t_opt *opt, t_process *process)
{
    if (opt->galaxy)
    {
        process->open_location = &open_location_galaxy;
    }
    else if (opt->sector)
    {
        process->open_location = &open_location_sector;
    }
    else if (opt->system)
    {
        process->open_location = &open_location_system;
    }
    else
    {
        process->open_location = NULL;
    }
}

static void                 process_content(t_opt *opt, t_process *process)
{
    unsigned int            i;

    i = 0;
    if (process->open_location)
    {
        process->open_location(opt, process, &i);
    }
    while (get_next_flag(&process->content[i], NULL, &i))
    {
        printf("%d\n", i);
        ++i;
    }
}

static void                 process_get_file(t_opt *opt, t_process *process)
{
//    process->fd_out = safe_open_write(opt->outfile, TRUE);
    process->fd_in = safe_open_read(opt->filename);
    process->filesize = (unsigned int) lseek(process->fd_in, 0, SEEK_END);
    process->content = mmap(NULL, process->filesize, PROT_READ, MAP_PRIVATE, process->fd_in, 0);
}

int                         core_process(t_opt *opt)
{
    t_process               process;

    init_process(opt, &process);
    process_get_file(opt, &process);
    process_content(opt, &process);
    return (TRUE);
}