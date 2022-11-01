/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/11/01 16:32:23 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	flag_handler(char **argv, int argc, uint8_t i, int8_t *id)
{
	if (!ft_strcmp(argv[i], "-n"))
	{
		check_valid_arg(argv, argc, i);
		*id = ft_atoi((const char *)argv[i + 1]);
		check_num_within_range(*id);
	}
	else if (!ft_strcmp(argv[i], "-dump"))
	{
		check_valid_arg(argv, argc, i);
		g_dump_nbr = ft_atoi((const char *)argv[i + 1]);
		//check if number < 0? or just ignore it?
	}
	else
		print_man_page();
}

static void	get_file_content(unsigned char *str, char *file)
{
	uint16_t	fd;

	fd = open(file, O_RDONLY);
	read(fd, str, MEM_SIZE);
	close(fd);
	check_file_type(str);
}

void	introduce_le_champ(t_header_t *player)
{
	uint8_t	i;

	i = 0;
	while (i < g_p_count)
	{
		check_missing_id(player[i].id);
		ft_printf("* Player %d @%d, weighing %d bytes, \"%s\" (\"%s\")!\n",
			player[i].id, i, player[i].prog_size,
			player[i].prog_name, player[i].comment);
		// print_mem(player[i].prog_size, player[i].code);
		i++;
	}
}

void	parse(t_header_t *player, char **argv, int argc)
{
	uint8_t			i;
	int8_t			id;
	unsigned char	str[MEM_SIZE];

	g_p_count = 0;
	id = NOT_SET;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			flag_handler(argv, argc, i++, &id);
		else
		{
			get_file_content(str, argv[i]);
			assign_player(player, str, id);
			id = NOT_SET;
			g_p_count++;
		}
		i++;
	}
	check_num_within_range(g_p_count);
	player_sort(player);
	introduce_le_champ(player);
}
