/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:17:37 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/14 18:13:06 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	call_error(char *folder, char *errcode)
{
	printf("minishell: cd: %s: %s\n", folder, errcode);
	return (1);
}

int	cd(char **envp, char *folder)
{
	char	*pwd;
	char	*oldpwd;
	char	*cwd;
	char	*path;
	
	cwd = getcwd(NULL, 0);
	//tratar too many arguments;
	if (folder && !(ft_strncmp(folder, "~", 2) == 0))
		//path = ft_strdup(folder); //preciso alocar isso daqui? não
		path = folder;
	else
		path = read_env(envp, "HOME");
	if (chdir(path) != 0)
		return (call_error(folder, strerror(errno))); // polemica do errno haha será q no minishell pode usar?
	pwd = read_env(envp, "PWD");
	oldpwd = read_env(envp, "OLDPWD");
	if (pwd && *pwd && oldpwd)
	{
		// change env maybe? The thing is, there is a case (when that key doesn't exist) that should be handled
		change_env(envp, "OLDPWD", pwd);
	}
	if (pwd && *pwd)
	{
		// same as the above;
		change_env(envp, "PWD", cwd);
	}
	strclear(&cwd);
	//strclear(&path);
	return(0);
}
