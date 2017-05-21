#include "splitter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void     set_galaxy_name(t_info *info, char *str, int len, int remove_mode)
{
  int		i;

  i = 0;
  if (remove_mode)
    {
      if (!info->galaxy_open)
	{
	  fprintf(stderr, "%s", "Error: Malformed file\n");
	  exit(EXIT_FAILURE);
	}
      free(info->galaxy_open);
      info->galaxy_open = NULL;
      return;
    }
  while (i < len && str[i] && str[i] != '"')
    {
      ++i;
    }
  if (!str[i] || info->galaxy_open)
    {
      fprintf(stderr, "%s", "Error: Malformed file\n");
      exit(EXIT_FAILURE);
    }
  if (!(info->galaxy_open = malloc(sizeof(char) * (i + 1))))
    {
      fprintf(stderr, "%s", "Error: Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
  strncpy(info->galaxy_open, str, i);
  /* Not needed, already provided by strncpy but by safety */
  info->galaxy_open[i] = '\0';
}

void		line_process(t_opt *opt, t_info *info, char *line, int len)
{
  int		i;

  i = 0;
  while (line[i] == ' ')
    {
      ++i;
    }
  if (!strncmp(&line[i], GALAXY_FLAG_BEG, GALAXY_FLAG_BEG_LEN))
    {
      set_galaxy_name(info, &line[i + GALAXY_FLAG_BEG_LEN], len - i - GALAXY_FLAG_BEG_LEN, 0);
      if (!strcmp(opt->galaxy, info->galaxy_open))
	{
	  info->choosen_galaxy = 1;
	  free(info->galaxy_open);
	  info->galaxy_open = NULL;
	}
    }
  else if (!strncmp(&line[i], GALAXY_FLAG_END, GALAXY_FLAG_END_LEN))
    {
      if (!info->choosen_galaxy)
	{
	  set_galaxy_name(info, NULL, 0, 1);
	  return;
	}
      info->choosen_galaxy = 0;
    }
  if (!info->galaxy_open)
    {
      fwrite(line, sizeof(char), len, info->output_fd);
    }
}
