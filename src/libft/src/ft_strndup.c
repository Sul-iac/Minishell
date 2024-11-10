/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:36:56 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 13:06:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *str, int n)
{
	int i = 0;
	int len = ft_strlen(str);
	
	if(n > len)
		n = len;
	char *dup = (char *)malloc(sizeof(char) * (n + 1));
	if(!dup)
		return(NULL);
	while(i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[n] = '\0';
	return(dup);
}