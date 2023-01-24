/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:09:50 by etachott          #+#    #+#             */
/*   Updated: 2023/01/24 20:40:40 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

int	is_expansible(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == '$' && (ft_isalpha(str[index + 1])
			|| str[index + 1] == '?'))
			return (1);
		index++;
	}
	return (0);
}

static int	has_cash_after_single_quotes(char *str)
{
	char	*quote_pos;
	int		index;
	int		expandable;

	index = -1;
	expandable = -1;
	quote_pos = ft_strnstr(str, "\'", ft_strlen(str));
	while (str[++index])
	{
		if (str[index] == '\"')
		{
			while (str[++index])
			{
				if (str[index] == '\"')
					break ;
				if (str[index] == '\'')
					return (0);
			}
		}
	}
	if (is_expansible(quote_pos))
		return (1);
	return (0);
}

char	*key_to_value(char *key_start)
{
	char	*final;
	char	*temp;
	char	*key;
	int		index;

	index = 0;
	final = NULL;
	while (((ft_isalpha(key_start[index]))
			|| key_start[index] == '_' || (key_start[index] == '?'))
		&& key_start[index])
		index++;
	key = ft_strndup(key_start, index);
	temp = ft_strjoin(key, "=");
	index = 0;
	while (g_data.envp[index])
	{
		if (ft_strncmp(g_data.envp[index], temp, ft_strlen(temp)) == 0)
			final = ft_strdup(g_data.envp[index] + ft_strlen(temp));
		index++;
	}
	if (!final)
		final = ft_strdup(" ");
	free(temp);
	return (final);
}

void	clear_four_string(char *temp1, char *temp2, char *str, char *final)
{
	strclear(&str);
	strclear(&temp1);
	if (temp2)
		strclear(&temp2);
	strclear(&final);
}

int	count_valid_vars(char *str)
{
	int	index;
	int	count;

	index = -1;
	count = 0;
	while (str[++index])
	{
		if (str[index] == '$' && (ft_isalpha(str[index + 1])
			|| str[index + 1] == '_' || str[index + 1] == '?'))
			count++;
	}
	return (count);
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
	if (has_cash_after_single_quotes(str))
		return (str);
	pos = 0;
	temp2 = NULL;
	temp3 = NULL;
	final = NULL;
	while (str[pos] != '$')
		pos++;
	temp1 = ft_strndup(str, pos);
	pos++;
	final = key_to_value(str + pos);
	while (((ft_isalpha(str[pos]) || str[pos] == '_'
			|| (str[pos] == '?')) && str[pos]))
		pos++;
	if (*(str + pos))
		temp2 = ft_strdup(str + pos);
	temp3 = join_three(temp1, final, temp2);
	clear_four_string(temp1, temp2, str, final);
	// if (is_expansible(temp3))
	// 	expand_str(temp3);
	return (temp3);
}
