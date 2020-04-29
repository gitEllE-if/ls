#ifndef N_MSTACK_H
# define N_MSTACK_H

# include "libft.h"

//t_list	**get_mstack(void);
int		free_mstack(void *to_free);
int		free_all_mstack(void);
int		add_mstack(void *to_add);
int		num_mstack();

#endif
