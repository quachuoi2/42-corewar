/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:10:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/30 22:55:54 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	g_arena[MEM_SIZE];

int	main(uint32_t argc, char **argv)
{
	uint8_t			p_count;
	t_header_t		player[4];

	if (argc < 2)
		print_man_page();
	initialize(player); //variable initialing goes here
	p_count = parse(player, argv, argc);
	corewar(player, p_count);
	return (0);
}

//	print_mem(player[0].prog_size, player[0].code); // print player data
//	print_mem(MEM_SIZE, arena); // print arena
