/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:17:37 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/24 16:04:09 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **envp, char *folder)
{
	char	*pwd;
	char	*oldpwd;
	char	*cwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	if (folder && !(ft_strncmp(folder, "~", 2) == 0))
		path = folder;
	else
		path = read_env(envp, "HOME");
	if (chdir(path) != 0)
	{
		perror_handler(folder, ": ", 1, NULL);
		return (1);
	}
	pwd = read_env(envp, "PWD");
	oldpwd = read_env(envp, "OLDPWD");
	if (pwd && *pwd && oldpwd)
		change_env(envp, "OLDPWD", pwd);
	if (pwd && *pwd)
		change_env(envp, "PWD", cwd);
	strclear(&cwd);
	return (0);
}
