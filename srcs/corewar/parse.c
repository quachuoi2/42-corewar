/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:09:11 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/11 06:59:25 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static uint16_t	open_read_close(unsigned char *str, char *file)
{
	int16_t		fd;
	uint16_t	ret;

	fd = open(file, O_RDONLY);
	ret = read(fd, str, MEM_SIZE);
	check_file_type(str, fd);
	close(fd);
	return (ret);
}

static void	introduce_le_champ(t_header_t *player)
{
	uint8_t	i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < g_p_count)
	{
		check_missing_id(player[i].id);
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			player[i].id, player[i].prog_size,
			player[i].prog_name, player[i].comment);
		i++;
	}
}

void	parse(t_header_t *player, char **argv, int argc)
{
	uint8_t			i;
	uint16_t		ret;
	unsigned char	*str;

	g_p_count = 0;
	i = 0;
	str = ft_memalloc(sizeof(unsigned char) * FILE_SIZE);
	check_err_malloc(str);
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			flag_handler(argv, argc, &i);
		else
		{
			ret = open_read_close(str, argv[i]);
			assign_player(&player[g_p_count], str, g_flags.id, ret);
			g_flags.id = NOT_SET;
			disassembler(&player[g_p_count], argv[i]);
			g_p_count++;
		}
	}
	check_num_within_range(g_p_count);
	player_sort(player);
	introduce_le_champ(player);
	free(str);
}
