#include "ft_ls.h"

static inline void	ft_append(char **comma, char *str, char *flag)
{
	if (*comma != NULL)
		ft_strcat(str, *comma);
	ft_strcat(str, flag);
	*comma = ",";
}

static inline void	ft_flag_to_str_sf(uint64_t flags, char *str, char **comma)
{
	if (flags & SF_ARCHIVED)
		ft_append(comma, str, "arch");
	if (flags & SF_IMMUTABLE)
		ft_append(comma, str, "schg");
	if (flags & SF_APPEND)
		ft_append(comma, str, "sappnd");
	if (flags & SF_RESTRICTED)
		ft_append(comma, str, "restricted");
	if (flags & SF_NOUNLINK)
		ft_append(comma, str, "sunlnk");
}

char				*ft_flag_to_str(uint64_t flags, char *deflt)
{
	static char	str[128];
	char		*comma;

	str[0] = '\0';
	comma = NULL;
	if (flags & UF_NODUMP)
		ft_append(&comma, str, "nodump");
	if (flags & UF_IMMUTABLE)
		ft_append(&comma, str, "uchg");
	if (flags & UF_APPEND)
		ft_append(&comma, str, "uappnd");
	if (flags & UF_OPAQUE)
		ft_append(&comma, str, "opaque");
	if (flags & UF_TRACKED)
		ft_append(&comma, str, "tracked");
	if (flags & UF_HIDDEN)
		ft_append(&comma, str, "hidden");
	ft_flag_to_str_sf(flags, str, &comma);
	return (comma == NULL && deflt != NULL ? deflt : str);
}
