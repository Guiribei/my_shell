/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:42:41 by etachott          #+#    #+#             */
/*   Updated: 2023/02/12 15:34:22 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_var_size(char *envp_str)
{
	int	index;

	index = 0;
	while (envp_str[index] != '=' && envp_str[index])
		index++;
	return (index);
}

int	ft_envcmp(char *envp_str, char *key)
{
	char	*env_var;
	int		env_var_size;

	if (!envp_str)
		return (1);
	env_var_size = count_var_size(envp_str);
	env_var = ft_strndup(envp_str, env_var_size);
	if (ft_strncmp(env_var, key, ft_strlen(env_var)) == 0
		&& ft_strncmp(env_var, key, ft_strlen(key)) == 0)
	{
		free(env_var);
		return (0);
	}
	free(env_var);
	return (1);
}
