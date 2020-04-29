static void printxattr(DISPLAY *dp, char *filename, ssize_t xattr)
{
	int flags = XATTR_NOFOLLOW;
	char *buf = malloc(xattr);

	if (NULL == buf)
		err(1, "malloc");
	if (listxattr(filename, buf, xattr, flags) > 0)
	{
		char *name;
		for (name = buf; name < buf+xattr; name += strlen(name) + 1)
		{
			ssize_t size = getxattr(filename, name, 0, 0, 0, flags);
			putchar('\t');
			printname(name);
			putchar('\t');
			printsize(dp->s_size, size);
			putchar('\n');
		}
	}
	free(buf);
}
