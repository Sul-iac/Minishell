/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 20:26:28 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 13:04:23 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_bzero(void *b, size_t len)
{
	unsigned int	i;
	unsigned char	*bytes;

	bytes = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		bytes[i] = 0;
		i++;
	}
	return (b);
}
