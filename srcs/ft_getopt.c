#include "ft_getopt.h"
#include "ft_ls.h"

int32_t		g_optind = 1;
const char	g_prn_error[] = ": illegal option --";
const char	g_prn_format[] = "%s%s %s\n";
char		*g_app_name = 0;

static char				*ft_get_app_name(char *argv_0)
{
	char	*p_argv_0;
	char	*s;

	s = argv_0;
	p_argv_0 = argv_0;
	while (*s != 0)
	{
		if (*s == '/')
			p_argv_0 = s;
		s++;
	}
	return (p_argv_0 + 1);
}

static int32_t			ft_getopt_parse(char *str, uint32_t *j,
															const char *opt_str)
{
	int32_t			i;
	const int32_t	cur_val = *(str + *j);

	i = -1;
	while (++i >= 0)
	{
		if (opt_str[i] == '\0')
		{
			ft_printf(g_prn_format, g_app_name, g_prn_error, (char*)&cur_val);
			if (*(str + ++(*j)) == '\0')
			{
				*j = 1;
				g_optind++;
			}
			return ('?');
		}
		if (cur_val == opt_str[i])
			break ;
	}
	if (*(str + ++(*j)) == '\0')
	{
		g_optind++;
		*j = 1;
	}
	return (cur_val);
}

int						ft_getopt(int argc, char *argv[], const char *opt_str)
{
	static int32_t		pars_end;
	static uint32_t		j = 1;
	int32_t				cur_val;
	int32_t				next_val;

	if (pars_end)
		return (-1);
	if (!g_app_name)
		g_app_name = ft_get_app_name(argv[0]);
	if (j > 1)
		return (ft_getopt_parse(argv[g_optind], &j, opt_str));
	if ((uint32_t)g_optind >= (uint32_t)argc)
	{
		pars_end = 1;
		return (-1);
	}
	cur_val = *argv[g_optind];
	next_val = *(argv[g_optind] + 1);
	if (!(cur_val == '-' && next_val != '\0'))
	{
		pars_end = 1;
		return (-1);
	}
	if (next_val != '-')
		return (ft_getopt_parse(argv[g_optind], &j, opt_str));
	g_optind++;
	pars_end = 1;
	return (-1);
}
