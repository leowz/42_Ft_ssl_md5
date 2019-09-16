#include "ft_ssl.h"
#include <sys/stat.h> 
#include <fcntl.h>

static void print(unsigned char digest[], char *string, int f)
{
	if (f & F_QUITE)
	{
		md5_print (digest);
		ft_printf ("\n");
	}
	else if (f & F_REVERSE)
	{
		md5_print (digest);
		if (f & F_FILE)
			ft_printf (" %s", string);
		else
			ft_printf (" \"%s\"", string);
		ft_printf ("\n");
	}
	else
	{
		if (f & F_FILE)
			ft_printf ("MD%d (%s) = ", 5, string);
		else
			ft_printf ("MD%d (\"%s\") = ", 5, string);
		md5_print (digest);
		ft_printf ("\n");
	}
}

void md5_string (char *string, int flag)
{
	MD5_CTX context;
	unsigned char digest[16];
	unsigned int len;

	len = ft_strlen(string);
	md5_init(&context);
	md5_update(&context, (unsigned char *)string, len);
	md5_final(digest, &context);
	print(digest, string, flag);
}

void md5_file (char *filename, int flag)
{
	MD5_CTX context;
	int len;
	int pfd;	
	unsigned char buffer[16];

	if ((pfd = open(filename, O_RDONLY)) == -1)
		ft_printf ("ft_ssl: md5: %s: No such file or directory\n", filename);
	else
	{
		md5_init(&context);
		while ((len = read (pfd, buffer, 16)) > 0) 
			md5_update(&context, buffer, len);
		md5_final(buffer, &context);

		close (pfd);
		print(buffer, filename, flag);
	}
}

static int strmerge(unsigned char **s1, int s1Len, unsigned char *s2, int len)
{
	unsigned char *ret;

	ret = NULL;
	if (s1Len == 0)
	{
		if ((ret = (unsigned char *)ft_strnew(len)))
		{
			ft_memcpy(ret, s2, len);
			*s1 = ret;
			return (len);
		}
	}
	if ((ret = (unsigned char *)ft_strnew(s1Len + len)))
	{
		ft_memcpy(ret, *s1, s1Len);
		ft_memcpy(ret + s1Len, s2, len);
		ft_strdel((char **)s1);
		*s1 = ret;
		return (s1Len + len);
	}
	return (0);
}

void md5_filter(int repeat)
{
	MD5_CTX context;
	unsigned char buffer[16];
	unsigned char *str;
	int len;
	int retLen;

	str = NULL;
	retLen = 0;
	md5_init(&context);
	while ((len = read(STDIN_FILENO, buffer, 16)) > 0)
	{
		md5_update(&context, buffer, len);
		if (repeat)
			retLen = strmerge(&str, retLen, buffer, len);
	}
	md5_final(buffer, &context);
	if (repeat)
	{
		ft_printf("%s", str);
		ft_strdel((char **)&str);
	}
	print(buffer, NULL, F_QUITE);
}
