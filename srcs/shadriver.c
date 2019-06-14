#include "ft_ssl.h"

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

static void MDTestSuite ()
{
	printf ("MD%d test suite:\n", 5);

	md5_string ("");
	md5_string ("a");
	md5_string ("abc");
	md5_string ("message digest");
	md5_string ("abcdefghijklmnopqrstuvwxyz");
	md5_string ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	md5_string ("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

static void md5_file (char *filename)
{
	FILE *file;
	MD5_CTX context;
	int len;
	unsigned char buffer[1024], digest[16];

	if ((file = fopen (filename, "rb")) == NULL)
		printf ("%s can't be opened\n", filename);
	else
	{
		md5_init(&context);
		while ((len = fread (buffer, 1, 1024, file)))
			md5_update(&context, buffer, len);
		md5_final(digest, &context);
		fclose (file);
		
		ft_printf ("MD5 (%s) = ", filename);
		md5_print (digest);
		ft_printf ("\n");
	}
}

static void md5_filter(void)
{
	MD5_CTX context;
	int len;
	unsigned char buffer[16], digest[16];

	md5_init(&context);
	while ((len = fread (buffer, 1, 16, stdin)))
		md5_update(&context, buffer, len);
	md5_final(digest, &context);

	md5_print (digest);
	ft_printf ("\n");
}

void md5(int ac, char **av)
{
	int i;

	if (ac > 2)
	{
		i = 1;
		while (++i < ac)
		{
			if (av[i][0] == '-' && av[i][1] == 's')
			{
				if (ft_strlen(av[i]) > 2)
					md5_string(av[i] + 2);
				else if (++i < ac)
					md5_string(av[i]);
				else
					ft_printf("md5: option requires an argument -- s\n");
			}
			else if (ft_strcmp (av[i], "-x") == 0)
				MDTestSuite();
			else
				md5_file(av[i]);
		}
	}
	else
		md5_filter();
}
