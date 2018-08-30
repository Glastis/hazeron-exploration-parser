/*
** Created by Glastis on 30/08/18.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header/process.h"
#include "header/utilities.h"

static void                 init_process(t_opt *opt, t_process *process)
{
    process->system_opened = (opt->system) ? FALSE : TRUE;
    process->sector_opened = (opt->sector) ? FALSE : TRUE;
    process->galaxy_opened = (opt->galaxy) ? FALSE : TRUE;
}

static int                  process_check_flag(t_opt *opt, t_process *process,const char *buff, int readed)
{
    int                     i;

    i = 0;
    while (i < readed)
    {
        if (opt->galaxy && comp_str(&buff[i], FLAG_GALAXY_NAME_BEG) && comp_str(&buff[i + sizeof(FLAG_GALAXY_NAME_BEG) - 1], opt->galaxy))
        {
            process->galaxy_opened = TRUE;
            puts("opened");
        }
        ++i;
    }
    return (FALSE);
}

static void                 process_read(t_opt *opt, t_process *process, int fd)
{
    char                    buff[READ_SIZE + 1];
    char                    *remember;
    char                    *tmp;
    int                     flag;
    unsigned int            readed;

    flag = FALSE;
    remember = NULL;
    while ((readed = (unsigned int) read(fd, buff, READ_SIZE)) > 0)
    {
        buff[readed] = '\0';
        if (!remember)
        {
            remember = str_coupler(buff, NULL);
        }
        else if (!flag)
        {
            tmp = remember;
            remember = str_coupler(remember, buff);
            free(tmp);
            flag = TRUE;
        }
        else
        {
            tmp = remember;
            remember = str_coupler(&remember[readed], (char *)buff);
            free(tmp);
        }
        if (process_check_flag(opt, process, remember, readed) >= 0)
        {

        }
    }
}

int                         core_process(t_opt *opt)
{
    t_process               process;
    int                     fd;

    init_process(opt, &process);
    fd = safe_open_read(opt->filename);
    process_read(opt, &process,fd);
    return (TRUE);
}