#include "ft_ssl.h"

#ifndef MD
#define MD 5
#endif

#if MD == 2
#include "md2.h"
#endif
#if MD == 4
#include "md4.h"
#endif
#if MD == 5
#include "md5.h"
#endif

/* Length of test block, number of test blocks.
 */
#define TEST_BLOCK_LEN 1000
#define TEST_BLOCK_COUNT 1000

static void MDString(char *);
static void MDTestSuite(void);
static void MDFile(char *);
static void MDFilter(void);
static void MDPrint(unsigned char [16]);

#if MD == 2
#define MD_CTX MD2_CTX
#define MDInit MD2Init
#define MDUpdate MD2Update
#define MDFinal MD2Final
#endif
#if MD == 4
#define MD_CTX MD4_CTX
#define MDInit MD4Init
#define MDUpdate MD4Update
#define MDFinal MD4Final
#endif
#if MD == 5
#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final
#endif

/* Main driver.

Arguments (may be any combination):
  -sstring - digests string
  -t       - runs time trial
  -x       - runs test script
  filename - digests file
  (none)   - digests standard input
 */
void md5(argc, argv)
int argc;
char *argv[];
{
  int i;

  if (argc > 1)
    for (i = 1; i < argc; i++)
      if (argv[i][0] == '-' && argv[i][1] == 's')
        MDString (argv[i] + 2);
      else if (ft_strcmp (argv[i], "-x") == 0)
        MDTestSuite ();
      else
        MDFile (argv[i]);
      else
        MDFilter ();
}

/* Digests a string and prints the result.
 */
static void MDString (string)
char *string;
{
  MD_CTX context;
  unsigned char digest[16];
  unsigned int len = ft_strlen(string);

  MDInit (&context);
  MDUpdate (&context, (unsigned char *)string, len);
  MDFinal (digest, &context);

  printf ("MD%d (\"%s\") = ", MD, string);
  MDPrint (digest);
  printf ("\n");
}

/* Digests a reference suite of strings and prints the results.
 */
static void MDTestSuite ()
{
  printf ("MD%d test suite:\n", MD);

  MDString ("");
  MDString ("a");
  MDString ("abc");
  MDString ("message digest");
  MDString ("abcdefghijklmnopqrstuvwxyz");
  MDString ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
  MDString ("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

/* Digests a file and prints the result.

 */
static void MDFile (filename)
char *filename;
{
  FILE *file;
  MD_CTX context;
  int len;
  unsigned char buffer[1024], digest[16];

  if ((file = fopen (filename, "rb")) == NULL)
    printf ("%s can't be opened\n", filename);
  else
  {
    MDInit (&context);
    while ((len = fread (buffer, 1, 1024, file)))
      MDUpdate (&context, buffer, len);
    MDFinal (digest, &context);

    fclose (file);

    printf ("MD%d (%s) = ", MD, filename);
    MDPrint (digest);
    printf ("\n");
  }
}

/* Digests the standard input and prints the result.
 */
static void MDFilter ()
{
  MD_CTX context;
  int len;
  unsigned char buffer[16], digest[16];

  MDInit (&context);
  while ((len = fread (buffer, 1, 16, stdin)))
  MDUpdate (&context, buffer, len);
  MDFinal (digest, &context);

  MDPrint (digest);
  printf ("\n");
}

/* Prints a message digest in hexadecimal.
 */
static void MDPrint (digest)
unsigned char digest[16];
{
  unsigned int i;

  for (i = 0; i < 16; i++)
    printf ("%02x", digest[i]);
}
