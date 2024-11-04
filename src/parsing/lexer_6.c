/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:14:56 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 17:14:56 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**allocate_array(int size)
{
	return (malloc((size + 1) * sizeof(char *)));
}

char	**copy_segment(char **str_array, const char *input, size_t *start)
{
	const char	*pipe_pos;
	size_t		length;

	pipe_pos = strchr(input + *start, '|');
	if (pipe_pos != NULL)
		length = (size_t)(pipe_pos - (input + *start));
	else
		length = strlen(input + *start);
	str_array[*start] = allocate_and_copy(input + *start, length);
	if (str_array[*start] == NULL)
		return (NULL);
	*start += length + 1;
	return (str_array);
}

char	**initialize_array(int num_pipes)
{
	char	**str_array;

	str_array = allocate_array(num_pipes + 1);
	if (str_array == NULL)
		return (NULL);
	return (str_array);
}

char	**copy_to_array(char **str_array, const char *input, int num_pipes)
{
	size_t	start;
	int		index;
	int		j;

	start = 0;
	index = 0;
	while (index <= num_pipes)
	{
		str_array = copy_segment(str_array, input, &start);
		if (str_array == NULL)
		{
			j = 0;
			while (j < index)
			{
				free(str_array[j]);
				j++;
			}
			free(str_array);
			return (NULL);
		}
		index++;
	}
	str_array[index] = NULL;
	return (str_array);
}

char	**split_into_array(const char *input, int num_pipes)
{
	char	**str_array;

	str_array = initialize_array(num_pipes);
	if (str_array == NULL)
		return (NULL);
	return (copy_to_array(str_array, input, num_pipes));
}
