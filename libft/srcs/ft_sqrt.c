int	ft_sqrt(int nb)
{
	int	div;
	int res;

	div = nb;
	res = nb;
	if (nb <= 0)
		return (0);
	while (1)
	{
		div = (nb / div + div) / 2;
		if (res > div)
			res = div;
		else if (res * res == nb)
			return (res);
		else
			return (0);
	}
}
