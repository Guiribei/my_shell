/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:02:03 by etachott          #+#    #+#             */
/*   Updated: 2023/02/04 20:41:26 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static int	is_valid(char *name)
{
	if (ft_strnstr(name, "=", ft_strlen(name))
		|| ft_strnstr(name, "-", ft_strlen(name)))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", name);
		return (0);
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
		if (ft_strncmp(g_data.envp[i], tmp, ft_strlen(g_data.envp[i])) == 0)
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

	tmp = ft_strjoin(name, "=");
	i = 0;
	size = ft_matrix_size(g_data.fenvp);
	temp = ft_calloc(sizeof(char *), size);
	temp[size - 1] = NULL;
	size = 0;
	while (size < ft_matrix_size(g_data.fenvp) - 1)
	{
		if (ft_strncmp(g_data.fenvp[i], tmp, ft_strlen(g_data.fenvp[i])) == 0)
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

static void	remove_from_fenvp_no_equal(char *name)
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
		if (ft_strncmp(g_data.fenvp[i], tmp, ft_strlen(g_data.fenvp[i])) == 0)
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

	index = 0;
	if (!argv[1])
		return (1);
	while (argv[++index])
	{
		if (is_valid(argv[index]))
		{
			remove_from_fenvp(argv[index]);
			remove_from_fenvp_no_equal(argv[index]);
			remove_from_envp(argv[index]);
		}
		else
			return (1);
	}
	return (0);
}
