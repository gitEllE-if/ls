#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include <stdint.h>

extern int32_t	g_optind;
extern char		*g_app_name;

int32_t			ft_getopt(int argc, char *argv[], const char *optstr);

#endif
