/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:02:00 by etachott          #+#    #+#             */
/*   Updated: 2023/02/15 16:13:22 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static void	error_handler_export(char *str1)
{
	ft_putstr_fd("minishell: export `", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

static int	is_valid(char *name, int *invalid_flag)
{
	int		index;

	index = 0;
	while (name[index])
	{
		if (name[index] == '=' && index != 0)
			break ;
		if (!ft_isalpha_under(name[index]))
		{
			*(invalid_flag) += 1;
			if (*(invalid_flag) == 1)
				error_handler_export(name);
			return (0);
		}
		if (!ft_isalpha_under(name[0]) || name[0] == '=')
			return (0);
		index++;
	}
	return (1);
}

static char	*get_key(char *name)
{
	char	*key;
	int		index;

	index = 0;
	while (name[index] != '=')
		index++;
	key = ft_strndup(name, index);
	return (key);
}

void	append_to_envp(char *name, int i)
{
	char	**temp;
	char	*key;
	int		envp_size;

	key = get_key(name);
	while (g_data.envp[++i])
	{
		if (!ft_envcmp(g_data.fenvp[i], key))
		{
			free(key);
			free(g_data.envp[i]);
			g_data.envp[i] = ft_strdup(name);
			return ;
		}
	}
	free(key);
	i = -1;
	envp_size = ft_matrix_size(g_data.envp);
	temp = ft_calloc(sizeof(char *), envp_size + 2);
	while (g_data.envp[++i])
		temp[i] = ft_strdup(g_data.envp[i]);
	temp[i] = ft_strdup(name);
	strsclear(g_data.envp);
	g_data.envp = temp;
}

int	builtin_export(char **av)
{
	static int	invalid_flag = 0;
	int			av_sz;

	if (!av)
		return (0);
	if (!av[1])
		return (env_export_no_arg());
	av_sz = 0;
	while (++av_sz < ft_matrix_size(av))
	{
		if (is_valid(av[av_sz], &invalid_flag)
			&& !ft_strnstr(av[av_sz], "=", ft_strlen(av[av_sz])))
			append_to_fake_envp(av[av_sz]);
		else if (is_valid(av[av_sz], &invalid_flag)
			&& ft_strnstr(av[av_sz], "=", ft_strlen(av[av_sz])))
		{
			append_to_fake_envp(av[av_sz]);
			append_to_envp(av[av_sz], -1);
		}
		else
			return (1);
	}
	invalid_flag = 0;
	return (0);
}
