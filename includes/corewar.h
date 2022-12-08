/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 00:32:42 by qnguyen           #+#    #+#             */
/*   Updated: 2022/12/09 00:07:11 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <fcntl.h>
# include "libftprintf.h"
# include "op.h"

# define NOT_SET	0
# define SET		1
# define NOT_OKEI	0
# define OKEI		1
# define FILE_SIZE	100000

typedef struct s_process		t_process;
typedef struct s_game_param		t_game_param;
typedef struct s_flag			t_flag;
typedef struct s_arg			t_arg;
typedef void					t_instruct_table(t_process *process,
									t_arg *arg, t_game_param *game);
typedef void					t_verbose_table(t_process *process,
									t_arg *arg);
typedef struct s_table			t_table;

struct s_process
{
	int8_t		cmd :5;
	uint8_t		carry :1;
	uint16_t	pc;
	uint16_t	bytes_to_next;
	uint16_t	wait_cycle;
	uint32_t	id;
	uint32_t	last_live_cycle;
	uint32_t	reg[REG_NUMBER + 1];
	t_process	*next;
};

struct s_game_param
{
	uint8_t		check_counter;
	uint8_t		last_alive;
	int16_t		cycle_to_die;
	uint32_t	live_performed;
	uint64_t	current_cycle;
	t_process	*head;
};

struct s_arg
{
	uint8_t		type;
	int32_t		value;
};

struct s_flag
{
	int8_t		id;
	int8_t		aff;
	uint8_t		byte;
	uint8_t		verbose;
	uint64_t	dump_nbr;
};

struct s_table
{
	t_instruct_table	*instruct_table[16];
	t_verbose_table		*verbose_table[16];
};

enum e_registry
{
	r1 = 1,
	r2,
	r3,
	r4,
	r5,
	r6,
	r7,
	r8,
	r9,
	r10,
	r11,
	r12,
	r13,
	r14,
	r15,
	r16
};

extern unsigned char			g_arena[MEM_SIZE];
extern uint8_t					g_p_count;
extern t_flag					g_flags;

//main.c
void		print_man_page(void);

//parse.c
void		parse(t_header_t *player, char **argv, int argc);

//flag_handler.c
void		flag_handler(char **argv, int argc, uint8_t *i);

//player_handler.c
void		assign_player(t_header_t *player,
				unsigned char *file, int8_t p_num, uint16_t ret);
void		player_sort(t_header_t *player);

//error.c
void		check_file_type(unsigned char *file, int16_t fd);
void		check_file_size(uint32_t size);
void		check_matching_champ_size(uint32_t byte_size, uint32_t actual);
void		check_valid_arg(char **argv, int argc, uint8_t i);
void		check_existing_id(int8_t id);
void		check_missing_id(int8_t id);
void		check_num_within_range(uint8_t num);

//process.c
void		processor(t_game_param *game, t_table *tab, t_header_t *player);

//process_util.c
void		free_process(t_process *prev, t_process *delete);
void		print_free_exit(t_process *head);
t_process	*new_process(t_process *head, uint16_t pos, int id);
t_process	*process_init(t_header_t *player);
void		kill_process(t_game_param *game);

//utilities.c
int			get_n_byte(uint8_t n, unsigned char *data, uint32_t idx);
uint8_t		get_2bit(uint8_t byte, uint8_t position);
uint16_t	get_position(uint16_t pos);
void		get_arg_without_arg_byte(t_process *process, t_arg *arg);

//corewar.c
void		corewar(t_header_t *player);

//instruction.c
void		live(t_process *process, t_arg *arg, t_game_param *game);
void		ld(t_process *process, t_arg *arg, t_game_param *game);
void		lld(t_process *process, t_arg *arg, t_game_param *game);
void		st(t_process *process, t_arg *arg, t_game_param *game);
void		add_sub(t_process *process, t_arg *arg, t_game_param *game);
void		and_or_xor(t_process *process, t_arg *arg, t_game_param *game);
void		zjmp(t_process *process, t_arg *arg, t_game_param *game);
void		ldi(t_process *process, t_arg *arg, t_game_param *game);
void		lldi(t_process *process, t_arg *arg, t_game_param *game);
void		sti(t_process *process, t_arg *arg, t_game_param *game);
void		l_foork(t_process *process, t_arg *arg, t_game_param *game);
void		aff(t_process *process, t_arg *arg, t_game_param *game);

//verbose_four.c
void		verbose_live(t_process *process, t_arg *arg);
void		verbose_l_ld(t_process *process, t_arg *arg);
void		verbose_st(t_process *process, t_arg *arg);
void		verbose_add_sub(t_process *process, t_arg *arg);
void		verbose_and_or_xor(t_process *process, t_arg *arg);
void		verbose_zjmp(t_process *process, t_arg *arg);
void		verbose_l_ldi(t_process *process, t_arg *arg);
void		verbose_sti(t_process *process, t_arg *arg);
void		verbose_l_foork(t_process *process, t_arg *arg);

//verbose.c
void		print_sixteen(t_process *process);
void		print_eight(t_process *process, t_game_param *game);

//instruc_util.c
int32_t		get_arg_value(t_process *process, t_arg *arg);
int8_t		check_matching_arg(t_process *process, t_arg *arg);

//init.c
void		initialize_players(t_header_t *player);
void		arena_init(t_header_t *player);
void		game_init(t_game_param *game, t_process *head);
void		flag_init(void);

//print.c
void		print_arena(t_header_t *player);
void		print_arg(t_process *process, t_arg *arg);
#endif
