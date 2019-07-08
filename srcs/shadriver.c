#include "ft_ssl.h"
#include "sha.h"

void sha256_string (char *string, int flag)
{
	SHA256_CTX context;
	unsigned char digest[32];
	unsigned int len = ft_strlen(string);

	sha256_init (&context);
	sha256_update (&context, (unsigned char *)string, len);
	sha256_final (digest, &context);

	ft_printf ("SHA%d (\"%s\") = ", 256, string);
	sha_print (digest);
	ft_printf ("\n");
}

void sha256_file (char *filename, int flag)
{
	FILE *file;
	SHA256_CTX context;
	int len;
	unsigned char buffer[1024], digest[32];

	if ((file = fopen (filename, "rb")) == NULL)
		printf ("%s can't be opened\n", filename);
	else
	{
		sha256_init(&context);
		while ((len = fread (buffer, 1, 1024, file)))
			sha256_update(&context, buffer, len);
		sha256_final(digest, &context);
		fclose (file);
		
		ft_printf ("MD5 (%s) = ", filename);
		sha_print (digest);
		ft_printf ("\n");
	}
}

void sha256_filter(int repeat)
{
	SHA256_CTX context;
	int len;
	unsigned char buffer[32], digest[32];

	sha256_init(&context);
	while ((len = fread (buffer, 1, 32, stdin)))
		sha256_update(&context, buffer, len);
	sha256_final(digest, &context);

	sha_print (digest);
	ft_printf ("\n");
}
