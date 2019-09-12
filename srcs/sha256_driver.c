#include "ft_ssl.h"
#include <sys/stat.h> 
#include <fcntl.h>

static void print(unsigned char digest[], char *string, int f)
{
	if (f & F_QUITE)
	{
		sha_print (digest);
		ft_printf ("\n");
	}
	else if (f & F_REVERSE)
	{
		sha_print (digest);
		if (f & F_FILE)
			ft_printf (" %s", string);
		else
			ft_printf (" \"%s\"", string);
		ft_printf ("\n");
	}
	else
	{
		if (f & F_FILE)
			ft_printf ("SHA%d (%s) = ", 256, string);
		else
			ft_printf ("SHA%d (\"%s\") = ", 256, string);
		sha_print (digest);
		ft_printf ("\n");
	}
}

void sha256_string (char *string, int flag)
{
	SHA256_CTX context;
	unsigned char digest[32];
	unsigned int len = ft_strlen(string);

	sha256_init(&context);
	sha256_update(&context, (unsigned char *)string, len);
	sha256_final(digest, &context);
	print(digest, string, flag);
}

void sha256_file (char *filename, int flag)
{
	SHA256_CTX context;
	int len;
	int pfd;
	unsigned char buffer[32];

	if ((pfd = open(filename, O_RDONLY)) == -1)
		printf ("%s can't be opened\n", filename);
	else
	{
		sha256_init(&context);
		while ((len = read (pfd, buffer, 32)) > 0)
			sha256_update(&context, buffer, len);
		sha256_final(buffer, &context);
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

void sha256_filter(int repeat)
{
	SHA256_CTX context;
	unsigned char buffer[32];
	unsigned char *str;
	int len;
	int retLen;

	str = NULL;
	retLen = 0;
	sha256_init(&context);
	while ((len = read(STDIN_FILENO, buffer, 32)) > 0)
	{
		sha256_update(&context, buffer, len);
		if (repeat)
			retLen = strmerge(&str, retLen, buffer, len);
	}
	sha256_final(buffer, &context);
	if (repeat)
	{
		ft_printf("%s", str);
		ft_strdel((char **)&str);
	}
	print(buffer, NULL, F_QUITE);
}
