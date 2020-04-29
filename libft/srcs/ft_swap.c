void		ft_swap(char **a, char **b)
{
	char	*sw;

	sw = *a;
	*a = *b;
	*b = sw;
}
