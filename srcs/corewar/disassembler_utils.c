/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 06:32:33 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/11 06:42:29 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	check_dir(t_header_t *player, int *code_idx, int type, int op_i)
{
	uint8_t		byte_ammount;
	int32_t		value;

	if (type != DIR_CODE)
		return ;
	byte_ammount = DIR_SIZE / (g_op_tab[op_i].dir_size + 1);
	value = get_n_byte(byte_ammount, player->code, *code_idx);
	if (g_op_tab[op_i].dir_size)
		value = (int16_t)value;
	*code_idx += byte_ammount;
	ft_printf("%%%d", value);
}

static void	check_ind(t_header_t *player, int *code_idx, int type)
{
	int16_t		value;

	if (type != IND_CODE)
		return ;
	value = get_n_byte(IND_SIZE, player->code, *code_idx);
	*code_idx += IND_SIZE;
	ft_printf("%d", value);
}

static void	check_reg(t_header_t *player, int *code_idx, int type)
{
	int8_t		value;

	if (type != REG_CODE)
		return ;
	value = get_n_byte(REG_NAME_SIZE, player->code, *code_idx);
	*code_idx += REG_NAME_SIZE;
	ft_printf("r%d", value);
}

void	diss_arg_byte(t_header_t *player, int *code_idx, int op_i)
{
	uint8_t		cur_2bit;
	int			i;
	int			arg_byte;

	i = 0;
	arg_byte = (*code_idx)++;
	while (1)
	{
		cur_2bit = get_2bit(player->code[arg_byte], i);
		check_dir(player, code_idx, cur_2bit, op_i);
		check_ind(player, code_idx, cur_2bit);
		check_reg(player, code_idx, cur_2bit);
		i++;
		if (i == g_op_tab[op_i].arg_amt)
			break ;
		else
			ft_printf(", ");
	}
	ft_printf("\n");
}

void	diss_no_arg(t_header_t *player, int *code_idx, int op_i)
{
	if (g_op_tab[op_i].arg_type[0] & T_DIR)
		check_dir(player, code_idx, DIR_CODE, op_i);
	else
		check_reg(player, code_idx, REG_CODE);
	ft_printf("\n");
}
