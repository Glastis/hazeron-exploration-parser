/*
** Created by Glastis on 31/08/18.
*/

#include <stdio.h>
#include <string.h>
#include "header/xml_parser.h"
#include "header/utilities.h"

int                         is_flag(const char *str)
{
    return (str[0] == XML_FLAG_BEG);
}

int                         is_flag_opened(const char *str)
{
    return (str[0] == XML_FLAG_BEG && str[1] != XML_FLAG_END);
}

int                         is_flag_closed(const char *str)
{
    return (str[0] == XML_FLAG_BEG && str[1] == XML_FLAG_END);
}

int                         is_this_flag_opened(const char *str, const char *flag)
{
    return (is_flag_opened(str) && comp_str(&str[1], flag));
}

int                         is_this_flag_closed(const char *str, const char *flag)
{
    return (is_flag_closed(str) && comp_str(&str[2], flag));
}

static int                  get_flag_opened_fill_buff(const char *str, char *dest)
{
    int                     i;

    i = 0;
    while (str[i] && str[i] != XML_ATR_SEPARATOR && str[i] != XML_ATR_END)
    {
        dest[i] = str[i];
        ++i;
    }
    return (str[i]);
}

static int                  is_num(const char a, const char b)
{
    return ((a >= '0' && a <= '9'));
    UNUSED(b);
}

static int                  is_alpha(const char a, const char b)
{
    return ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'));
    UNUSED(b);
}

static int                  is_alphanum(const char a, const char b)
{
    return (is_alpha(a, b) || is_num(a, b));
}

static int                  is_same_char(const char a, const char b)
{
    return (a == b);
}

static int                  is_open_str(const char a, const char b)
{
    return (!is_same_char(a, XML_STRING_ENCLOSURE));
    UNUSED(b);
}

static unsigned int         skip_cond(const char *str, int (*cond)(const char, const char), const char a)
{
    unsigned int            i;

    i = 0;
    while (cond(str[i], a))
    {
        ++i;
    }
    return (i);
}

static int                  skip_flag_name(const char *str, unsigned int *ret)
{
    unsigned int            i;

    i = 0;
    if (!is_flag_opened(str))
    {
        fprintf(stderr, "Warning: %s\n", WARNING_BAD_USAGE_SKIP_FLAG_NAME);
    }
    ++i;
    i += skip_cond(&str[i], &is_same_char, XML_ATR_SEPARATOR);
    if (is_alphanum(str[i], UNUSED_PADING_CHAR))
    {
        i += skip_cond(&str[i], &is_alphanum, UNUSED_PADING_CHAR);
        i += skip_cond(&str[i], &is_same_char, XML_ATR_SEPARATOR);
    }
    else
    {
        error(ERROR_MALFORMED_XML);
    }
    if (str[i] == XML_ATR_END)
    {
        return (FALSE);
    }
    else if (is_alphanum(str[i], UNUSED_PADING_CHAR))
    {
        ret[0] = i;
        return (TRUE);
    }
    error(ERROR_MALFORMED_XML);
    return (FALSE);
}

static unsigned int         copy_until_cond(const char *src, char *dest, int (*cond)(const char, const char), const char a)
{
    unsigned int            i;

    i = 0;
    while (src[i] && cond(src[i], a))
    {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return (i);
}

static int                  go_to_atr_value(const char *str, const char *atr, unsigned int *ret)
{
    unsigned int            i;

    if (!skip_flag_name(str, &i))
    {
        return (FALSE);
    }
    while (str[i] != XML_ATR_END)
    {
        i += skip_cond(&str[i], &is_same_char, XML_ATR_SEPARATOR);
        if (comp_str(&str[i], atr))
        {
            i += strlen(atr);
            if (str[i] != XML_ATR_IS && str[i + 1] != XML_STRING_ENCLOSURE)
            {
                error(ERROR_MALFORMED_XML);
            }
            ret[0] += i + 2;
            return (TRUE);
        }
        ++i;
    }
    return (FALSE);
}

int                         is_atr_value(const char *str, const char *atr, const char *value)
{
    unsigned int            i;

    i = 0;
    return (go_to_atr_value(str, atr, &i) && comp_str(&str[i], value));
}

int                         get_atr_value(const char *str, const char *atr, char *dest)
{
    unsigned int            i;

    i = 0;
    return (go_to_atr_value(str, atr, &i) && copy_until_cond(&str[i + 1], dest, &is_open_str, UNUSED_PADING_CHAR));
}

int                         get_flag_opened(const char *str, char *dest)
{
    return (is_flag_opened(str) && get_flag_opened_fill_buff(&str[1], dest));
}

int                         get_flag_closed(const char *str, char *dest)
{
    return (is_flag_closed(str) && get_flag_opened_fill_buff(&str[2], dest));
}

static int                  get_next_flag_flag(const char *str, const char *flag, unsigned int *ret, t_state state)
{
    unsigned int            i;

    i = 0;
    while (str[i])
    {
        if (is_flag(&str[i]) &&
           ((state == ALL && (is_this_flag_opened(&str[i], flag) || is_this_flag_closed(&str[i], flag))) ||
            (state == OPEN && is_this_flag_opened(&str[i], flag)) ||
            (state == CLOSE && is_this_flag_closed(&str[i], flag))))
        {
            ret[0] += i;
            return (TRUE);
        }
        ++i;
    }
    return (FALSE);
}

int                         get_next_flag(const char *str, const char *flag, unsigned int *ret, t_state state)
{
    unsigned int            i;

    i = 0;
    if (flag)
    {
        return (get_next_flag_flag(str, flag, ret, state));
    }
    while (str[i] && !is_flag(&str[i]))
    {
        ++i;
    }
    ret[0] += i;
    return (str[i] != '\0');
}

int                         move_to_flag(const char *str, const char *flag, const char *flagid, const char *flagid_value, unsigned int *ret)
{
    unsigned int            i;

    i = 0;
    while (get_next_flag(&str[i], flag, &i, OPEN))
    {
        if (is_atr_value(&str[i], flagid, flagid_value))
        {
            ret[0] += i;
            return (TRUE);
        }
        ++i;
    }
    return (FALSE);
}