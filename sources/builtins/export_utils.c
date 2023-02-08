/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:01:45 by etachott          #+#    #+#             */
/*   Updated: 2023/02/08 15:48:22 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

static char	*get_key(char *name)
{
	char	*key;
	int		index;

	index = 0;
	if (!ft_strnstr(name, "=", ft_strlen(name)))
		return (ft_strdup(name));
	while (name[index] != '=')
		index++;
	key = ft_strndup(name, index);
	return (key);
}

static int	fake_check(char *fenvp_str, char *name)
{
	if (ft_strnstr(fenvp_str, "=", ft_strlen(fenvp_str))
		&& ft_strnstr(name, "=", ft_strlen(name)))
		return (1);
	else if (!ft_strnstr(fenvp_str, "=", ft_strlen(fenvp_str))
		&& ft_strnstr(name, "=", ft_strlen(name)))
		return (1);
	else if (!ft_strnstr(fenvp_str, "=", ft_strlen(fenvp_str))
		&& !ft_strnstr(name, "=", ft_strlen(name)))
		return (1);
	else if (ft_strnstr(fenvp_str, "=", ft_strlen(fenvp_str))
		&& !ft_strnstr(name, "=", ft_strlen(name)))
		return (0);
	else
		return (-1);
}

static void	replace_name(char *key, char *name, int i)
{
	if (!fake_check(g_data.fenvp[i], name))
		return ;
	free(key);
	free(g_data.fenvp[i]);
	g_data.fenvp[i] = ft_strdup(name);
}

void	append_to_fake_envp(char *name)
{
	char	**temp;
	char	*k;
	int		i;
	int		fenvp_size;

	i = -1;
	k = get_key(name);
	while (g_data.fenvp[++i])
	{
		if (!ft_envcmp(g_data.fenvp[i], k))
			return (replace_name(k, name, i));
	}
	free(k);
	i = -1;
	fenvp_size = ft_matrix_size(g_data.fenvp);
	temp = ft_calloc(sizeof(char *), fenvp_size + 2);
	while (g_data.fenvp[++i])
		temp[i] = ft_strdup(g_data.fenvp[i]);
	temp[i] = ft_strdup(name);
	strsclear(g_data.fenvp);
	g_data.fenvp = temp;
}
