/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:30:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 13:04:37 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	size_t			i;
	unsigned char	*byte_dst;
	unsigned char	*byte_src;

	byte_dst = (unsigned char *)dst;
	byte_src = (unsigned char *)src;
	i = -1;
	while (++i < len)
		byte_dst[i] = byte_src[i];
	return (dst);
}
