/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:55:38 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/14 18:48:52 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 4096);
	ft_putendl_fd(str, 1);
	strclear(&str);
	return (0);
}
