/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:17:37 by guribeir          #+#    #+#             */
/*   Updated: 2022/12/13 19:49:42 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	call_error(char *folder, char *errcode)
{
	printf("minishell: cd: %s: %s\n", folder, errcode);
	return (1);
}

int	cd(t_list *env, char *folder)
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
		path = read_env(env, "HOME");
	if (chdir(path) != 0)
		return (call_error(folder, strerror(errno))); // polemica do errno haha será q no minishell pode usar?
	pwd = read_env(env, "PWD");
	oldpwd = read_env(env, "OLDPWD");
	if (pwd && *pwd && oldpwd)
	{
		// change env maybe? The thing is, there is a case (when that key doesn't exist) that should be handled
		change_env(env, "OLDPWD", pwd);
	}
	if (pwd && *pwd)
	{
		// same as the above;
		change_env(env, "PWD", cwd);
	}
	strclear(&cwd);
	//strclear(&path);
	return(0);
}
