/*
** Created by Glastis on 30/07/18.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "header/main.h"
#include "header/structure.h"
#include "header/utilities.h"
#include "header/process.h"
#include "header/trace.h"

#ifndef TRACE_DEBUG
void                        debug_init()
{

}
#endif

static void                 init_opt(t_opt *opt, t_opt_init *init)
{
    opt->filename = NULL;
    opt->system = NULL;
    opt->sector = NULL;
    opt->galaxy = NULL;
    opt->ressource = NULL;
    opt->min_quality = -1;
    opt->max_quality = -1;
    opt->outfile = NULL;

    init->min_quality = NULL;
    init->max_quality = NULL;
}

static int                  get_opt_detect(char **opt, const int next, const char *optstr, const char *optstr_short, const char **input)
{
    if (strcmp(input[0], optstr) && strcmp(input[0], optstr_short))
    {
        return (FALSE);
    }
    if (next && !input[1])
    {
        fprintf(stderr, "%s: %s\n", input[0], ERROR_ARGUMENT_VALUE);
        return (FALSE);
    }
    opt[0] = (char *) input[1];
    return (TRUE);
}

static void                 get_opt_init_cleanup(t_opt *opt, t_opt_init *init)
{
    opt->max_quality = init->max_quality ? atoi(init->max_quality) : -1;
    opt->min_quality = init->min_quality ? atoi(init->min_quality) : -1;
}

static void                 get_opt(t_opt *opt, const char **av, const int ac)
{
    int                     i;
    t_opt_init              opt_init;

    i = 1;
    init_opt(opt, &opt_init);
    while (i < ac)
    {
        if (!strcmp(OPT_HELP, av[i]) || !strcmp(OPT_HELP_SHOT, av[i]))
        {
            print_help();
            exit(0);
        }
        else if (   !get_opt_detect(&opt->galaxy, TRUE, OPT_GALAXY, OPT_GALAXY_SHORT, &av[i])
                 && !get_opt_detect(&opt->sector, TRUE, OPT_SECTOR, OPT_SECTOR_SHORT, &av[i])
                 && !get_opt_detect(&opt->system, TRUE, OPT_SYSTEM, OPT_SYSTEM_SHORT, &av[i])
                 && !get_opt_detect(&opt->filename, TRUE, OPT_FILE, OPT_FILE_SHORT, &av[i])
                 && !get_opt_detect(&opt->outfile, TRUE, OPT_FILE, OPT_FILE_SHORT, &av[i])
                 && !get_opt_detect(&opt->ressource, TRUE, OPT_RESSOURCE, OPT_RESSOURCE_SHORT, &av[i])
                 && !get_opt_detect(&opt_init.min_quality, TRUE, OPT_QUALITY_MAX, OPT_QUALITY_MAX_SHORT, &av[i])
                 && !get_opt_detect(&opt_init.max_quality, TRUE, OPT_QUALITY_MIN, OPT_QUALITY_MIN_SHORT, &av[i]))
        {
            fprintf(stderr, "%s: %s\n", av[i], ERROR_ARGUMENT_IGNORED);
        }
        else
        {
            ++i;
        }
        ++i;
    }
    get_opt_init_cleanup(opt, &opt_init);
}

static void                 check_opt(t_opt *opt)
{
    if ((opt->galaxy && opt->sector) || (opt->galaxy && opt->system) || (opt->sector && opt->system))
    {
        error(ERROR_ARGUMENT_MULTIPLE_LOCATION);
    }
    UNUSED(opt);
}

int                         main(int ac, const char **av)
{
    t_opt                   opt;

    UNUSED(ac);
    debug_init();
    get_opt(&opt, av, ac);
    check_opt(&opt);
    core_process(&opt);
    return (0);
}