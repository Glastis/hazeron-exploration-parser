#ifndef SPLITTER_H_
# define SPLITTER_H_

#include <stdio.h>

/* UTILITIES */
#define TRUE		1
#define FALSE		0
#define UNUSED(X)	(void)(X)

/* OPTIONS FLAGS */
#define FILENAME_FLAG		"--filename"
#define FILENAME_FLAG_S		"-f"
#define GALAXY_FLAG		"--galaxy"
#define GALAXY_FLAG_S		"-g"
#define OUTPUT_FLAG		"--output"
#define OUTPUT_FLAG_S		"-o"
#define SECTOR_FLAG		"--sector"
#define SECTOR_FLAG_S		"-s"

/* ERRORS */
#define ERROR_UNSET_GALAXY	"Galaxy undefined"
#define ERROR_UNSET_FILE	"Report file undefined"
#define ERROR_BAD_ARGUMENT	"Bad argument"
#define ERROR_REDEFINITION	"Redefinition of already set parameter"
#define DEVELOPPEMENT_PROCESS	"Feature not implemented yet"

/* OTHER */
#define HELP			"Usage: hes -f [filename] -g [galaxy]\n\t\t-f, --filename Specify a report name\n\t\t-g, --galaxy Specify galaxy to keep.\n\t\t -o --output Specify output file. Default filename is cut.xml.\n"
#define DEFAULT_OUTPUT		"cut.xml"
#define GALAXY_FLAG_BEG		"<galaxy name=\""
#define GALAXY_FLAG_BEG_LEN	(sizeof(GALAXY_FLAG_BEG) - 1)
#define GALAXY_FLAG_END		"</galaxy>"
#define GALAXY_FLAG_END_LEN	(sizeof(GALAXY_FLAG_END) - 1)


struct			s_opt
{
  char			*file;
  char			*galaxy;
  char			*sector;
  char			*error;
};

struct			s_info
{
  FILE		        *input_fd;
  FILE			*output_fd;
  char			*galaxy_open;
  int			choosen_galaxy;
  char			*sector_open;
};

typedef struct s_opt	t_opt;
typedef struct s_info	t_info;

void            line_process(t_opt *opt, t_info *info, char *line, int len);

#endif /* !SPLITTER_H_ */
