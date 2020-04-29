#include "ft_printf.h"
#include "pf_types.h"

int32_t	ft_putbuf(t_prnf *pf, va_list *ap, char type, char *buf)
{
	int32_t	i;

	if (!type)
		return (0);
	i = 0;
	while (g_type_tab[i].type != '0')
	{
		if (type == g_type_tab[i].type)
		{
			g_type_tab[i].f(type, buf, pf, ap);
			return (1);
		}
		i++;
	}
	g_type_tab[i].f(type, buf, pf, ap);
	return (1);
}
