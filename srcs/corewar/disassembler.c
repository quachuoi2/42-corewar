/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 02:54:56 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/11 06:58:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	open_diss_file(int *fd, char *diss_name, char *champ)
{
	int	len;

	len = ft_strlen(champ);
	ft_strncpy(diss_name, champ, len - 3);
	diss_name[len - 3] = 's';
	diss_name[len - 2] = '\0';
	*fd = open(diss_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

static void	handle_instruction(t_header_t *player)
{
	int	op_i;
	int	code_idx;

	code_idx = 0;
	while (code_idx < (int)player->prog_size)
	{
		op_i = 0;
		while (player->code[code_idx] != g_op_tab[op_i].order_num)
			op_i++;
		ft_printf("%-6s", g_op_tab[op_i].name);
		code_idx++;
		if (g_op_tab[op_i].arg_byte)
			diss_arg_byte(player, &code_idx, op_i);
		else
			diss_no_arg(player, &code_idx, op_i);
	}
}

void	disassembler(t_header_t *player, char *champ)
{
	int		fd;
	char	diss_name[1000];

	if (g_flags.diss == NOT_SET)
		return ;
	open_diss_file(&fd, diss_name, champ);
	ft_printf(".name \"%s\"\n", player->prog_name);
	ft_printf(".comment \"%s\"\n\n", player->comment);
	handle_instruction(player);
	write(fd, g_p_str.s, g_p_str.i);
	close(fd);
	ft_bzero(g_p_str.s, g_p_str.i);
	g_p_str.i = 0;
}
