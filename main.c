#define _GNU_SOURCE
#include "splitter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void	init_hes(t_opt *opt, t_info *info)
{
  /* Opt structure initialisation */
  opt->file = NULL;
  opt->galaxy = NULL;
  opt->sector = NULL;
  opt->error = NULL;

  /* Info structure initialisation */
  info->output_fd = NULL;
  info->input_fd = NULL;
  info->galaxy_open = NULL;
  info->sector_open = NULL;
  info->choosen_galaxy = 0;
}

static int	get_opt(t_opt *opt, char **av, char **ags, int agsi)
{
  unsigned int	i;
  
  i = 0;
  /* Unecessary commentary */
  if (ags)
    {
      /* In case of stupid user */
      if (!ags[1] || ags[1][0] == '-')
	{
	  opt->error = ERROR_BAD_ARGUMENT;
	  return (EXIT_FAILURE);
	}
      if (agsi == 0)
	{
	  if (opt->file)
	    {
	      opt->error = ERROR_REDEFINITION;
	    }
	  opt->file = ags[1];
	}
      else if (agsi == 1)
	{
	  if (opt->galaxy)
	    {
	      opt->error = ERROR_REDEFINITION;
	    }
	  opt->galaxy = ags[1];
	}
      else
	{
	  opt->error = DEVELOPPEMENT_PROCESS;
	}
      return (EXIT_SUCCESS);
    }
  while (av[i])
    {
      if (!strcmp(FILENAME_FLAG, av[i]) || !strcmp(FILENAME_FLAG_S, av[i]))
	{
	  /* Using same function instead of new one is pointless, fun only */
	  get_opt(opt, NULL, &av[i], 0);
	}
      else if (!strcmp(GALAXY_FLAG, av[i]) || !strcmp(GALAXY_FLAG_S, av[i]))
	{
	  /* Using same function instead of new one is pointless, fun only */
	  get_opt(opt, NULL, &av[i], 1);  
	}
      else if (!strcmp(SECTOR_FLAG, av[i]) || !strcmp(SECTOR_FLAG_S, av[i]))
	{
	  /* Using same function instead of new one is pointless, fun only */
	  get_opt(opt, NULL, &av[i], 2);
	}
      else if (!strcmp(OUTPUT_FLAG, av[i]) || !strcmp(SECTOR_FLAG_S, av[i]))
	{
	  /* Using same function instead of new one is pointless, fun only */
	  get_opt(opt, NULL, &av[i], 3);
	}
      ++i;
    }
  /* In case of stupid user */
  if (!opt->galaxy && !opt->error)
    {
      opt->error = ERROR_UNSET_GALAXY;
    }
  if (!opt->file && !opt->error)
    {
      opt->error = ERROR_UNSET_FILE;
    }
  if (opt->error)
    {
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
  char		*line;
  size_t	len;
  int		read;
  t_opt		opt;
  t_info	info;
  
  len = 0;
  line = NULL;
  init_hes(&opt, &info);
  if (get_opt(&opt, &av[1], NULL, -1) || !(info.input_fd = fopen(opt.file, "r")) || !(info.output_fd = fopen(DEFAULT_OUTPUT, "w")))
    {
      if (opt.error)
	{
	  fprintf(stderr, "%s%s%s", "Error: ", opt.error, "\n");
	  printf("%s", HELP);
	}
      return (EXIT_FAILURE);
    }
  while ((read = getline(&line, &len, info.input_fd)) != -1)
    {
      line_process(&opt, &info, line, read);
    } 
  fclose(info.input_fd);
  fclose(info.output_fd);
  if (line)
    {
      free(line);
    }
  return (EXIT_SUCCESS);
  UNUSED(ac);
}
