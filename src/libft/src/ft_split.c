/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 07:19:44 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 14:21:25 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_word_count(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	ft_word_len(const char *str, char c, int j)
{
	int	i;

	i = 0;
	while (str[i + j] != '\0' && str[i + j] != c)
		i++;
	return (i);
}

void	free_split(char **spl, int j)
{
	while (j >= 0)
	{
		free(spl[j]);
		j--;
	}
	free(spl);
}

char	**ft_split(const char *s, char c)
{
	char	**spl;
	int		i;
	int		j;
	int		wlen;

	i = 0;
	j = 0;
	spl = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!spl)
		return (NULL);
	while (j < ft_word_count(s, c))
	{
		while (s[i] == c)
			i++;
		wlen = ft_word_len(s, c, i);
		spl[j] = ft_substr(s, i, wlen);
		if (!spl[j])
			return (free_split(spl, j - 1), NULL);
		i += wlen;
		j++;
	}
	spl[j] = NULL;
	return (spl);
}
