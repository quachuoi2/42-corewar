/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:49:29 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/09 00:09:00 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	n_flag(char **argv, int argc, uint8_t *i)
{
	check_valid_arg(argv, argc, *i);
	g_flags.id = ft_atoi((const char *)argv[*i + 1]);
	check_num_within_range(g_flags.id);
	(*i)++;
}

static void	dump_flag(char **argv, int argc, uint8_t *i)
{
	check_valid_arg(argv, argc, *i);
	g_flags.dump_nbr = ft_atoi((const char *)argv[*i + 1]);
	if (argv[*i][2] == 'u')
		g_flags.byte = 32;
	else
		g_flags.byte = 64;
	(*i)++;
}

static void	aff_flag(void)
{
	g_flags.aff = SET;
}

static void	verbose_flag(char **argv, int argc, uint8_t *i)
{
	check_valid_arg(argv, argc, *i);
	g_flags.verbose = ft_atoi(argv[*i + 1]);
	(*i)++;
}

void	flag_handler(char **argv, int argc, uint8_t *i)
{
	if (!ft_strcmp(argv[*i], "-n"))
		n_flag(argv, argc, i);
	else if (!ft_strcmp(argv[*i], "-dump") || !ft_strcmp(argv[*i], "-d"))
		dump_flag(argv, argc, i);
	else if (!ft_strcmp(argv[*i], "-a"))
		aff_flag();
	else if (!ft_strcmp(argv[*i], "-v"))
		verbose_flag(argv, argc, i);
	else
		print_man_page();
}
