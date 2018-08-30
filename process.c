/*
** Created by Glastis on 30/08/18.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include "header/process.h"
#include "header/utilities.h"

static void                 init_process(t_opt *opt, t_process *process)
{
    process->system_opened = (opt->system) ? FALSE : TRUE;
    process->sector_opened = (opt->sector) ? FALSE : TRUE;
    process->galaxy_opened = (opt->galaxy) ? FALSE : TRUE;
}

static int                  process_check_flag_char(char *content, char *flag, char *name, int *bool, int boolset, unsigned int *i)
{
    if (name && comp_str(content, flag) && (!name || comp_str(&content[strlen(flag)], name)))
    {
        bool[0] = boolset;
        i[0] += strlen(flag) + safe_strlen(name);
        puts("test");
        return (TRUE);
    }
    return (FALSE);
}

static int                  process_check_flag(t_opt *opt, t_process *process, unsigned int i)
{
    return (process_check_flag_char(&process->content[i], FLAG_GALAXY_BEG, opt->galaxy, &process->galaxy_opened, TRUE, &i)
         || process_check_flag_char(&process->content[i], FLAG_GALAXY_END, opt->galaxy, &process->galaxy_opened, FALSE, &i)
         || process_check_flag_char(&process->content[i], FLAG_SECTOR_BEG, opt->sector, &process->sector_opened, TRUE, &i)
         || process_check_flag_char(&process->content[i], FLAG_SECTOR_END, opt->sector, &process->sector_opened, FALSE, &i)
         || process_check_flag_char(&process->content[i], FLAG_SYSTEM_BEG, opt->system, &process->system_opened, TRUE, &i)
         || process_check_flag_char(&process->content[i], FLAG_SYSTEM_END, opt->system, &process->system_opened, FALSE, &i));
}

static void                 process_content(t_opt *opt, t_process *process)
{
    unsigned int            i;

    i = 0;
    while (i < process->filesize)
    {
        process_check_flag(opt, process, i);
        ++i;
    }
}

static void                 process_get_file(t_opt *opt, t_process *process)
{
    process->fd_out = safe_open_write(opt->outfile, TRUE);
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