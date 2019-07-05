#include "ft_ssl.h"
#include <sys/stat.h> 
#include <fcntl.h>

static void md5_string (char *string)
{
	MD5_CTX context;
	unsigned char digest[16];
	unsigned int len = ft_strlen(string);

	md5_init (&context);
	md5_update (&context, (unsigned char *)string, len);
	md5_final (digest, &context);

	ft_printf ("MD%d (\"%s\") = ", 5, string);
	md5_print (digest);
	ft_printf ("\n");
}

static void md5_file (char *filename)
{
	MD5_CTX context;
	int len;
	int pfd;	
	unsigned char buffer[16], digest[16];

	ft_printf("filename %s\n", filename);	
	if ((pfd = open(filename, O_RDONLY)) == -1)
	{
		ft_printf ("%s can't be opened\n", filename);
	}
	else
	{
		md5_init(&context);
		while ((len = read (pfd, buffer, 16)) > 0) 
			md5_update(&context, buffer, len);
		md5_final(digest, &context);

		close (pfd);
		ft_printf ("MD5 (%s) = ", filename);
		md5_print (digest);
		ft_printf ("\n");
	}
}

static int strmerge(unsigned char **s1, int s1Len, unsigned char *s2, int len) {
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
		return (0);
	}
	if ((ret = (unsigned char *)ft_strnew(s1Len + len)))
	{
		ft_memcpy(ret, *s1, s1Len);
		ft_memcpy(ret + s1Len, s2, len);
		ft_strdel((char **)s1);
		*s1 = ret;
	}
	return (s1Len + len);
}

static void md5_filter(int repeat)
{
	MD5_CTX context;
	int len;
	unsigned char buffer[16], digest[16];
	unsigned char *str;
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
	md5_final(digest, &context);

	if (repeat)
	{
		ft_printf("%s", str);
		ft_strdel((char **)&str);
	}
	md5_print (digest);
	ft_printf ("\n");
}

void hash(int ac, char **av, int index)
{
	int i;
	int	f; //  q=2, r=1	

	if (ac > 2)
	{
		i = 1;
		while (++i < ac)
		{
			if (av[i][0] == '-')
			{
				if (av[i][1] == 's')
				{
					if (++i < ac)
						md5_string(av[i]);
					else
						ft_printf("md5: option requires an argument -- s\n");
				}
				else if (av[i][1] == 'p')
					md5_filter(1);
				else if (av[i][1] == 'q')
					f = 2;
				else if (av[i][1] == 's')
					f = 1;
				else
					ft_printf("md5: illegal option -- c\n", av[i][1]);
			}
			else
				md5_file(av[i]);
		}
	}
	else
		md5_filter(0);
}
