/*
** Created by Glastis on 31/08/18.
*/

#include <stdio.h>
#include <string.h>
#include "header/xml_parser.h"
#include "header/utilities.h"

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
    return (i);
}

unsigned int                get_atr_value(const char *str, const char *atr, char *dest)
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
            if (str[i] != XML_ATR_IS)
            {
                error(ERROR_MALFORMED_XML);
            }
            ++i;
            if (str[i] == XML_STRING_ENCLOSURE)
            {
                ++i;
            }
            return (copy_until_cond(&str[i], dest, &is_alphanum, UNUSED_PADING_CHAR));
        }
        ++i;
    }
    return (i);
}

int                         get_flag_opened(const char *str, char *dest)
{
    return (is_flag_opened(str) && get_flag_opened_fill_buff(&str[1], dest));
}

int                         get_flag_closed(const char *str, char *dest)
{
    return (is_flag_closed(str) && get_flag_opened_fill_buff(&str[2], dest));
}

static int                  move_to_flag_check_atr(const char *str, const char *flagid, const char *flagid_value, unsigned int *ret)
{
    unsigned int            i;
    char                    buffer[XML_ATR_BUFF_SIZE];

    if ((i = get_atr_value(str, flagid, buffer)) && comp_str(buffer, flagid_value))
    {
        ret[0] = i;
        return (TRUE);
    }
    return (FALSE);
}

int                         get_next_flag(const char *str, const char *flag, unsigned int *ret)
{
    unsigned int            i;

    i = 0;
    while (str[i] && !is_flag_opened(&str[i]))
    {
        ++i;
    }
    ret[0] += i;
    if (str[i])
    {
        if (flag && is_this_flag_opened(&str[i], flag))
        {
            return (get_next_flag(&str[i], flag, ret));
        }
        return (TRUE);
    }
    return (FALSE);
}

unsigned int                move_to_flag(const char *str, const char *flag, const char *flagid, const char *flagid_value)
{
    unsigned int            i;

    i = 0;
    while (str[i])
    {
        if (is_flag_opened(&str[i]) && comp_str(&str[i + 1], flag) && move_to_flag_check_atr(&str[i], flagid, flagid_value, &i))
        {
            while (str[i] && str[i] != XML_ATR_END)
            {
                ++i;
            }
            i += str[i] ? 1 : 0;
            return (i);
        }
        ++i;
    }
    return (FALSE);
}