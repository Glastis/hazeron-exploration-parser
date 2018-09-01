/*
** Created by Glastis on 31/08/18.
*/

#ifndef DOWNLOADER_XML_PARSER_H
#define DOWNLOADER_XML_PARSER_H

#define XML_ATR_BUFF_SIZE                           200u

#define UNUSED_PADING_CHAR                          '\0'

#define XML_ATR_SEPARATOR                           ' '
#define XML_ATR_END                                 '>'
#define XML_ATR_IS                                  '='
#define XML_FLAG_BEG                                '<'
#define XML_FLAG_END                                '/'
#define XML_STRING_ENCLOSURE                        '\"'

#define ERROR_MALFORMED_XML                         "Malformed XML"
#define WARNING_BAD_USAGE_SKIP_FLAG_NAME            "skip_flag_name: bad usage"

unsigned int                get_atr_value(const char *str, const char *atr, char *dest);
int                         get_flag_opened(const char *str, char *dest);
int                         get_flag_closed(const char *str, char *dest);
int                         is_flag_opened(const char *str);
int                         is_flag_closed(const char *str);
int                         is_this_flag_opened(const char *str, const char *flag);
int                         is_this_flag_closed(const char *str, const char *flag);
int                         get_next_flag(const char *str, const char *flag, unsigned int *ret);
unsigned int                move_to_flag(const char *str, const char *flag, const char *flagid, const char *flagid_value);

#endif /* !DOWNLOADER_XML_PARSER_H */
