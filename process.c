/*
** Created by Glastis on 30/08/18.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include "header/xml_parser.h"
#include "header/process.h"
#include "header/utilities.h"

static int                  open_location_galaxy(t_process *process, unsigned int *i)
{
    return (move_to_flag(process->content, process->location->flag, FLAG_GALAXY_ATR_NAME, process->location->name, i));
}

static int                  open_location_sector(t_process *process, unsigned int *i)
{
    return (move_to_flag(process->content, process->location->flag, FLAG_SECTOR_ATR_NAME, process->location->name, i));
}

static int                  open_location_system(t_process *process, unsigned int *i)
{
    return (move_to_flag(process->content, process->location->flag, FLAG_SYSTEM_ATR_NAME, process->location->name, i));
}

static void                 process_get_file(t_opt *opt, t_process *process)
{
//    process->fd_out = safe_open_write(opt->outfile, TRUE);
    process->fd_out = FALSE;
    process->fd_in = safe_open_read(opt->filename);
    process->filesize = (unsigned int) lseek(process->fd_in, 0, SEEK_END);
    process->content = mmap(NULL, process->filesize, PROT_READ, MAP_PRIVATE, process->fd_in, 0);
}

static void                 init_process(t_opt *opt, t_process *process)
{
    process->location = safe_malloc(1, sizeof(t_location));
    if (opt->galaxy)
    {
        process->open_location = &open_location_galaxy;
        process->location->name = opt->galaxy;
        process->location->flag = FLAG_GALAXY;
        process->location->type = GALAXY;
    }
    else if (opt->sector)
    {
        process->open_location = &open_location_sector;
        process->location->name = opt->sector;
        process->location->flag = FLAG_SECTOR;
        process->location->type = SECTOR;
    }
    else if (opt->system)
    {
        process->open_location = &open_location_system;
        process->location->name = opt->system;
        process->location->flag = FLAG_SYSTEM;
        process->location->type = SYSTEM;
    }
    else
    {
        process->open_location = NULL;
        free(process->location);
        process->location = NULL;
    }
    process_get_file(opt, process);
}

static void                 process_flag_check_closed_location(t_process *process, char *str)
{
    if (!str[0] || is_this_flag_closed(str, process->location->flag))
    {
        print_line(str);
        if (process->fd_out)
        {
            close(process->fd_out);
        }
        exit(42);
    }
}

static void                 process_flag(t_opt *opt, t_process *process, char *str)
{
    process_flag_check_closed_location(process, str);
    print_line(str);
    UNUSED(opt);
}

static void                 process_content(t_opt *opt, t_process *process)
{
    unsigned int            i;

    i = 0;
    if (process->open_location && !process->open_location(process, &i))
    {
        fprintf(stderr, "%s: ", process->location->name);
        error(ERROR_LOCATION_NOT_FOUND);
    }
    while (get_next_flag(&process->content[i], NULL, &i, ALL))
    {
        process_flag(opt, process, &process->content[i]);
        ++i;
    }
}

int                         core_process(t_opt *opt)
{
    t_process               process;

    init_process(opt, &process);
    process_content(opt, &process);
    return (TRUE);
}