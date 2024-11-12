/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:34:14 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 14:34:14 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(const char *input)
{
	int			num_pipes;
	int			in_quotes;
	const char	*ptr;

	num_pipes = 0;
	in_quotes = 0;
	ptr = input;
	while (*ptr != '\0')
	{
		if (*ptr == '"')
			in_quotes = !in_quotes;
		if (*ptr == '|' && !in_quotes)
			num_pipes++;
		ptr++;
	}
	return (num_pipes);
}

char	*allocate_and_copy(const char *start, size_t length)
{
	char	*new_str;

	new_str = malloc((length + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	strncpy(new_str, start, length);
	new_str[length] = '\0';
	return (new_str);
}

int	process_segment(const char *input, t_split_info *info)
{
	const char	*pipe_pos;
	int			in_quotes;
	size_t		length;

	length = 0;
	in_quotes = 0;
	pipe_pos = input + info->start;
	while (pipe_pos[length] != '\0' && (pipe_pos[length] != '|' || in_quotes))
	{
		if (pipe_pos[length] == '"')
			in_quotes = !in_quotes;
		length++;
	}
	info->str_array[info->index]
		= allocate_and_copy(input + info->start, length);
	if (info->str_array[info->index] == NULL)
	{
		free_array(info->str_array, info->index);
		return (-1);
	}
	info->start += length + 1;
	info->index++;
	return (0);
}

char	**split_into_array(const char *input, int num_pipes)
{
	t_split_info	info;

	info.start = 0;
	info.index = 0;
	info.num_pipes = num_pipes;
	info.str_array = malloc((num_pipes + 2) * sizeof(char *));
	if (info.str_array == NULL)
		return (NULL);
	while (info.index <= num_pipes)
	{
		if (process_segment(input, &info) == -1)
			return (NULL);
	}
	info.str_array[info.index] = NULL;
	return (info.str_array);
}

char	**split_string(const char *input)
{
	int	num_pipes;

	num_pipes = count_pipes(input);
	return (split_into_array(input, num_pipes));
}
