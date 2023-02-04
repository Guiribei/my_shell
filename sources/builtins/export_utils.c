/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:01:45 by etachott          #+#    #+#             */
/*   Updated: 2023/02/04 20:14:37 by etachott         ###   ########.fr       */
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

void	append_to_fake_envp(char *name)
{
	char	**temp;
	char	*key;
	int		i;
	int		fenvp_size;

	i = -1;
	key = get_key(name);
	while (g_data.fenvp[++i])
	{
		if (ft_strncmp(g_data.fenvp[i], key, ft_strlen(g_data.fenvp[i])) == 0)
		{
			free(key);
			g_data.fenvp[i] = ft_strdup(name);
			return ;
		}
	}
	free(key);
	i = -1;
	fenvp_size = ft_matrix_size(g_data.fenvp);
	temp = ft_calloc(sizeof(char *), fenvp_size + 2);
	while (g_data.fenvp[++i])
		temp[i] = ft_strdup(g_data.fenvp[i]);
	temp[i] = ft_strdup(name);
	strsclear(g_data.fenvp);
	g_data.fenvp = temp;
}
