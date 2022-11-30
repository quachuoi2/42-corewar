/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_sixteen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:40:05 by jrummuka          #+#    #+#             */
/*   Updated: 2022/11/30 23:40:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	print_sixteen(t_process *process)
{
	int	i;

	if (process->bytes_to_next > 0)
	{
		i = -1;
		ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", process->bytes_to_next, process->pc, process->pc + process->bytes_to_next);
		while (i++ < process->bytes_to_next - 1)
			ft_printf("%02x ", g_arena[get_position(process->pc + i)]);
		ft_printf("\n");
	}
}
