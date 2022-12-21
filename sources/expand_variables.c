/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott <etachott@student.42sp.org.b      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:09:50 by etachott          #+#    #+#             */
/*   Updated: 2022/12/21 13:54:01 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	t_data	g_data;

int	is_expansible(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index])
	{
		if (str[index] == '$'
			&& ((65 <= str[index + 1] && str[index + 1] <= 90)
			|| str[index + 1] == '?'))
			return (1);
		index++;
	}
	return (0);
}

char	*key_to_value(char *key)
{
	char	*final;
	char	*temp;
	int		index;

	index = 0;
	final = NULL;
	temp = ft_strjoin(key, "=");
	while (g_data.envp[index])
	{
		if (ft_strncmp(g_data.envp[index], key, ft_strlen(key)) == 0)
			final = ft_strdup(g_data.envp[index] + (ft_strlen(key) + 2));
		index++;
	}
	if (!final)
		final = ft_strdup(" ");
	free(temp);
	return (final);
}

char	*expand_str(char *str)
{
	char	*final;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	int		pos;

	if (!str)
		return (NULL);
	final = ft_strdup(str);
	pos = 0;
	temp2 = NULL;
	temp3 = NULL;
	while (ft_strnstr(final, "$", ft_strlen(final)))
	{
		while (str[pos] != '$')
			pos++;
		temp1 = ft_strndup(str, pos);
		pos++;
		strclear(&final);
		final = key_to_value(str + pos);
		while (((65 <= str[pos] && str[pos] <= 90)
				 || str[pos] == '_') && str[pos])
			pos++;
		if (*(str + pos))
			temp2 = ft_strdup(str + pos);
		temp3 = join_three(temp1, final, temp2);
	}
	strclear(&str);
	strclear(&temp1);
	if (temp2)
		strclear(&temp2);
	strclear(&final);
	return (temp3);
}
