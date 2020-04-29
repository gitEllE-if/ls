int	ft_ceil(double num)
{
	long int inum;

	inum = num;
	if ((double)inum != num && inum >= 0)
		return (inum + 1);
	return (inum);
}
