/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:02:03 by etachott          #+#    #+#             */
/*   Updated: 2023/02/13 20:27:48 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	error_handler_unset(char *str1)
{
	ft_putstr_fd("minishell: unset `", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

static int	is_valid(char *name)
{
	int		index;

	index = 0;
	while (name[index])
	{
		if (!ft_isalpha_under(name[0]))
			return (0);
		if (!ft_isalpha_under(name[index])
			&& !ft_isdigit(name[index]) && index != 0)
		{
			error_handler_unset(name);
			return (0);
		}
		index++;
	}
	return (1);
}

static void	remove_from_envp(char *name)
{
	char	**temp;
	char	*tmp;
	int		size;
	int		i;

	tmp = ft_strjoin(name, "=");
	i = 0;
	size = ft_matrix_size(g_data.envp);
	temp = ft_calloc(sizeof(char *), size);
	temp[size - 1] = NULL;
	size = 0;
	while (size < ft_matrix_size(g_data.envp) - 1)
	{
		if (ft_envcmp(g_data.envp[i], name) == 0)
			i++;
		else
		{
			temp[size] = ft_strdup(g_data.envp[i]);
			size++;
			i++;
		}
	}
	strsclear(g_data.envp);
	g_data.envp = temp;
	free(tmp);
}

static void	remove_from_fenvp(char *name)
{
	char	**temp;
	char	*tmp;
	int		size;
	int		i;

	tmp = ft_strdup(name);
	i = 0;
	size = ft_matrix_size(g_data.fenvp);
	temp = ft_calloc(sizeof(char *), size);
	temp[size - 1] = NULL;
	size = 0;
	while (size < ft_matrix_size(g_data.fenvp) - 1)
	{
		if (ft_envcmp(g_data.fenvp[i], name) == 0)
			i++;
		else
		{
			temp[size] = ft_strdup(g_data.fenvp[i]);
			size++;
			i++;
		}
	}
	strsclear(g_data.fenvp);
	g_data.fenvp = temp;
	free(tmp);
}

int	builtin_unset(char **argv)
{
	int	index;
	int	invalid_flag;

	index = 0;
	invalid_flag = 0;
	if (!argv[1])
		return (0);
	while (++index < ft_matrix_size(argv))
	{
		if (is_valid(argv[index]))
		{
			remove_from_fenvp(argv[index]);
			remove_from_envp(argv[index]);
		}
	}
	return (invalid_flag);
}
