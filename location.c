/*
** Created by Glastis on 02/09/18.
*/

#include "header/location.h"
#include "header/xml_parser.h"
#include "header/main.h"
#include "header/utilities.h"

int                         is_system_eod(const char *str, t_eod eod)
{
    const char              *eod_name;

    if (eod == SURVEYED)
    {
        eod_name = SYSTEM_EOD_SURVEYED;
    }
    else if (eod == EXPLORED)
    {
        eod_name = SYSTEM_EOD_EXPLORED;
    }
    else
    {
        eod_name = SYSTEM_EOD_UNEXPLORED;
    }
    return (is_atr_value(str, SYSTEM_EOD_ATR_NAME, eod_name));
}

int                         is_system_surveyed(const char *str)
{
    return (is_system_eod(str, SURVEYED));
}

int                         check_ressource_in_system(const char *str, const char *ressource, char *dest, int min, int max)
{
    UNUSED(str);
    UNUSED(ressource);
    UNUSED(dest);
    UNUSED(min);
    UNUSED(max);
    return (FALSE);
}

int                         check_and_add_ressource(t_opt *opt, t_process *process, const char *str)
{
    char                    buff[sizeof(RESSOURCE_QUALITY_MAX)];

    UNUSED(process);
    if (check_ressource_in_system(str, opt->ressource, buff, opt->min_quality, opt->max_quality))
    {
        return (TRUE);
    }
    return (FALSE);
}