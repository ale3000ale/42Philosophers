/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 18:14:11 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/07/10 16:10:24 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>

// Reset

# define	OFF	"\033[0m"

// Regular colors

# define	BLACK		"\033[0;30m"
# define	RED			"\033[0;31m" 
# define	GREEN		"\033[0;32m"
# define	YEL			"\033[0;33m"
# define	BLUE		"\033[0;34m"
# define	PUR			"\033[0;35m"
# define	CYAN		"\033[0;36m"
# define	WHITE		"\033[0;37m"

# define PHIL	"\033[0;33m \
_______  __   __  ___   ___      _______  _______  _______  _______  __ \
  __  _______  ______    _______ \n\
|       ||  | |  ||   | |   |    |       ||       ||       ||       ||  | \
|  ||       ||    _ |  |       |\n\
|    _  ||  |_|  ||   | |   |    |   _   ||  _____||   _   ||    _  ||  |_\
|  ||    ___||   | ||  |  _____|\n\
|   |_| ||       ||   | |   |    |  | |  || |_____ |  | |  ||   |_| ||    \
   ||   |___ |   |_||_ | |_____ \n\
|    ___||       ||   | |   |___ |  |_|  ||_____  ||  |_|  ||    ___||    \
   ||    ___||    __  ||_____  |\n\
|   |    |   _   ||   | |       ||       | _____| ||       ||   |    |   _\
   ||   |___ |   |  | | _____| |\n\
|___|    |__| |__||___| |_______||_______||_______||_______||___|    |__| \
|__||_______||___|  |_||_______|\n\
\033[0m\n\n"

# define	PROCS	"\033[0;31m\
                                  ██▓███   ██▀███   ▒█████   ▄████▄  ▓█████ \
  ██████   ██████ \n\
                                 ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▒██▀ ▀█  ▓█   ▀ \
▒██    ▒ ▒██    ▒ \n\
                                 ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▒▓█    ▄ ▒███   \
░ ▓██▄   ░ ▓██▄   \n\
                                 ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒▓▓▄ ▄██▒▒▓█  ▄ \
  ▒   ██▒  ▒   ██▒\n\
                                 ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░▒ ▓███▀ ░░▒████▒\
▒██████▒▒▒██████▒▒\n\
                                 ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ░ ░▒ ▒  ░░░ ▒░ ░\
▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░\n\
                                 ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░   ░  ▒    ░ ░  ░\
░ ░▒  ░ ░░ ░▒  ░ ░\n\
                                 ░░         ░░   ░ ░ ░ ░ ▒  ░  amarcell ░   \
░  ░  ░  ░  ░  ░  \n\
                                             ░         ░ ░  ░ ░         ░   \
░      ░        ░ \n\
 \033[0m\n\n"

# define	SLEEP_STAMP		"is sleeping        \033[0;35m(( _ _ ))\
\033[0;36m..zzZZ"
# define	DEAD_STAMP		"died               \033[0;35m(´\033[0;31m༎ຶོ\
\033[0;35mρ\033[0;31m༎ຶོ\033[0;35m`)"
# define	EATING_STAMP	"is eating          \033[0;35m( ^o^)🍝\033[0m"
# define	THINKING_STAMP	"is thinking        \033[0;35m('ω')\033[0;32m｡o○"
# define	FULL_STAMP		"are FULL           \033[0;35m(\033[0;33m●\033[0;35m´ω｀\
\033[0;33m●\033[0;35m)"
# define	DROP_STAMP		"has DROP the forks    🍴🍴"
# define	FORK_STAMP		"has taken a fork   \033[0;35m🍴(｀∇´)"

# define	DEAD		0
# define	EATING		1
# define	THINKING	2
# define	SLEEPING	3
# define	FULL		4
# define	FINISH		5
# define	CAN_EAT		1

# define	SEM_FORKS	"forks"
# define	SEM_PRINT	"print"

typedef struct s_philo
{
	int				id;
	int				status;
	int				can_i_eat;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			eat_count;
	long			eat_max;
	struct timeval	time;
	struct timeval	*global_time;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	pthread_t		thread;
}				t_philo;

typedef struct s_main
{
	int				n_philos;
	t_philo			philo;
	pid_t			*pid_philo;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			eat_max;
	struct timeval	time;
	sem_t			*sem;
	sem_t			*sem_print;
}				t_main;

long	ft_latoi(const char *str);
int		ft_atoi(const char *str);
int		ft_isnumber(char *s);
int		ft_strlen(char *s);
int		is_integer(char *s);
void	*ft_calloc(size_t count, size_t size);
long	msleep(int ms);
int		create_process(t_main *control);
int		init_main(t_main *control, char	**argc);
int		timestamp(t_philo *philo, char *s);
long	timepassed_ms(struct timeval time_start);
int		think_time(t_philo *philo);
void	*wait_forks(void *ph);
int		starvation(t_philo *philo);
void	philo_routine(t_philo *philo);

#endif