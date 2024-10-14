/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:48:48 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/13 13:43:14 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *phrase)
{
	int i = 0;
	while (phrase[i]!='\0')
	{
		i++;
	}
	return(i);
}

int main (void)
{
	char *phrase = "mon ch`at cestg le plus bo";
printf("%d\n",ft_strlen(phrase));
}