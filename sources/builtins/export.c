/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:02:00 by etachott          #+#    #+#             */
/*   Updated: 2023/02/04 20:07:38 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static int	has_dash(char *name)
{
	int	index;

	index = 0;
	while (name[index] && name[index] != '=')
	{
		if (name[index] == '-')
			return (1);
		index++;
	}
	return (0);
}

static int	is_valid(char *name, int *invalid_flag)
{
	if (!ft_isalpha_under(name[0]) || has_dash(name) || name[0] == '=')
	{
		*(invalid_flag) += 1;
		if (*(invalid_flag) == 1)
			printf("minishell: export `%s': not a valid identifier\n", name);
		return (0);
	}
	if (!ft_strnstr(name, "=", ft_strlen(name)))
	{
		append_to_fake_envp(name);
		return (0);
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

static void	append_to_envp(char *name)
{
	char	**temp;
	char	*key;
	int		i;
	int		envp_size;

	i = -1;
	key = get_key(name);
	while (g_data.envp[++i])
	{
		if (ft_strncmp(g_data.envp[i], key, ft_strlen(g_data.envp[i])) == 0)
		{
			free(key);
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

int	builtin_export(char **argv)
{
	static int	invalid_flag = 0;
	int			index;
	int			argv_size;

	if (!argv)
		return (0);
	if (!argv[1])
	{
		env_export_no_arg();
		return (0);
	}
	index = 1;
	argv_size = ft_matrix_size(argv);
	while (index < argv_size)
	{
		if (is_valid(argv[index], &invalid_flag))
		{
			append_to_fake_envp(argv[index]);
			append_to_envp(argv[index]);
		}
		else
			return (1);
		index++;
	}
	invalid_flag = 0;
	return (0);
}
