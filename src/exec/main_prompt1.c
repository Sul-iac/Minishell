/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:10 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 19:40:20 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_username(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = "user";
	return (user);
}

char	*ft_get_status_color(void)
{
	if (g_global_sig == 0)
		return (GREEN);
	return (RED);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	ft_fill_prompt(char *prompt, char *user, char *dir)
{
	char	*first_line;
	char	*second_line;
	char	*color;

	prompt[0] = '\0';
	first_line = ft_strjoin(CYAN "╭─" GREEN, user);
	if (!first_line)
		return ;
	first_line = ft_strjoin_free(first_line, RESET " 🌟 " BLUE);
	first_line = ft_strjoin_free(first_line, dir);
	first_line = ft_strjoin_free(first_line, RESET "\n");
	color = ft_get_status_color();
	second_line = ft_strjoin("╰─", color);
	second_line = ft_strjoin_free(second_line, "➜" RESET " ");
	if (first_line && second_line)
	{
		ft_strlcpy(prompt, first_line, ft_strlen(first_line) + 1);
		ft_strlcat(prompt, second_line, ft_strlen(prompt)
			+ ft_strlen(second_line) + 1);
	}
	free(first_line);
	free(second_line);
}

char	*ft_create_prompt(void)
{
	char	*dir;
	char	*user;
	char	*prompt;
	size_t	len;

	dir = ft_get_dirname();
	user = ft_get_username();
	if (!dir || !user)
	{
		free(dir);
		return (NULL);
	}
	len = ft_strlen(user) + ft_strlen(dir) + 100;
	prompt = (char *)ft_calloc(len, sizeof(char));
	if (!prompt)
	{
		free(dir);
		return (NULL);
	}
	ft_fill_prompt(prompt, user, dir);
	free(dir);
	return (prompt);
}
