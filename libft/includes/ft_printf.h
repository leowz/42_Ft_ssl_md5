/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:09:33 by zweng             #+#    #+#             */
/*   Updated: 2018/09/26 19:55:21 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

/*
** Macrons for printf flags
*/
# define PFFL_HT	1
# define PFFL_ZR	2
# define PFFL_MI	4
# define PFFL_PL	8
# define PFFL_SP	16

/*
** Macros for length
*/
# define PFLT_H     1
# define PFLT_HH    2
# define PFLT_L     3
# define PFLT_LL    4
# define PFLT_J     5
# define PFLT_Z     6
# define PFLT_CL    7

/*
** Macros for types
*/
# define PFTP_S     1
# define PFTP_CS    2
# define PFTP_P     3
# define PFTP_D     4
# define PFTP_CD    5
# define PFTP_I     6
# define PFTP_O     7
# define PFTP_CO    8
# define PFTP_U     9
# define PFTP_CU    10
# define PFTP_X     11
# define PFTP_CX    12
# define PFTP_C     13
# define PFTP_CC    14
# define PFTP_E     15
# define PFTP_CE    16
# define PFTP_F     17
# define PFTP_CF    18
# define PFTP_G     19
# define PFTP_CG    20
# define PFTP_A     21
# define PFTP_CA    22
# define PFTP_PC    23
# define PFTP_N     24
# define FTPF_PA	"$"
# define FTPF_FL	"+- #0"
# define FTPF_TY	"diouxXDOUeEfFgGaAcCsSpnb"
# define FTPF_LH	"hlzjL"
# define PRC_NO		(-2147483647)

typedef struct		s_formatph
{
	int				param;
	int				flags;
	int				fieldwidth;
	int				precision;
	int				length;
	int				type;
}					t_formatph;

size_t				ft_convert(char **buf, const char **format, t_formatph
					*forma, va_list ap);
size_t				ft_rpstr(char **buf, t_formatph forma, va_list ap);

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_asprintf(char **buf, const char *format, ...);
int					ft_vdprintf(int fd, const char *format, va_list ap);
int					ft_vasprintf(char **s, const char *format, va_list ap);

void				ft_scanflag(const char **format_ptr, t_formatph *forma);
void				ft_scan_width(const char **format_ptr,
					t_formatph *forma, va_list ap);
void				ft_scan_precision(const char **format_ptr,
					t_formatph *forma, va_list ap);
void				ft_scanlength(const char **format_ptr, t_formatph *forma);
void				ft_scantype(const char **format_ptr, t_formatph *forma);

char				*ft_handle_format_uint(char *rawstr, t_formatph forma);
char				*ft_handle_format_int(char *rawstr, intmax_t val,
					t_formatph forma);
char				*ft_handle_format_charstr(char *rawstr, size_t len,
					t_formatph forma);
char				*pf_itoa_base(uintmax_t val, t_formatph forma);
char				*pf_add_prefix_str(char *str, const char *str_to_add);
char				*ft_strndup(char *str, size_t size);
char				*pf_padding(char *rawstr, size_t len, t_formatph forma);
char				*pf_handle_null_c(const char c);
size_t				pf_handle_null_str(char **buf, const char *str, int n);
int					pf_get_base(const t_formatph forma);

size_t				ft_wstrlen(const wchar_t *wstr);
size_t				ft_widetoa(char *buf, wint_t w);
char				*ft_wstrtomb(const wchar_t *wstr);
size_t				ft_wstrntomb(char **buf, const wchar_t *wstr, size_t n);
#endif
