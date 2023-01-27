/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:37:30 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/27 01:35:38 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	strclear(char **str)
{
	if (!str)
		return ;
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int	count_rows(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	strsclear(char **ptrs)
{
	int	i;
	int	elements;

	if (!ptrs)
		return ;
	if (ptrs != NULL)
	{
		elements = count_rows(ptrs);
		i = 0;
		while (i < elements)
		{
			if (ptrs[i] != NULL)
				free(ptrs[i]);
			i++;
		}
		free(ptrs);
		ptrs = NULL;
	}
}

void	half_break_free(t_data	*data)
{
	data->flag_quit = 0;
	if (data->prompt)
		strsclear(data->prompt);
	if (data->str)
		strclear(&data->str);
	if (data->prompt_name)
		strclear(&data->prompt_name);
}

void	break_free(t_data *data)
{
	if (data)
		half_break_free(data);
	if (data->envp)
		strsclear(data->envp);
	rl_clear_history();
}
