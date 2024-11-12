/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenser_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:52 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 15:32:52 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_quotes(const char *p, t_process_data *data,
	int *in_single_quote, int *in_double_quote)
{
	if (p[data->i] == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		data->i++;
		return (1);
	}
	else if (p[data->i] == '\"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		data->i++;
		return (1);
	}
	return (0);
}

char	*handle_variable_replacement(const char *p,
	t_process_data *data, char *result)
{
	char	*var_value;
	size_t	value_len;

	data->i++;
	var_value = get_env_variable_value(p, &data->i);
	if (var_value)
	{
		value_len = strlen(var_value);
		result = resize_result_if_needed(result, &data->k, data->j + value_len);
		if (!result)
			return (NULL);
		strcpy(&result[data->j], var_value);
		data->j += value_len;
	}
	return (result);
}

char	*process_input(const char *p, t_process_data *data, char *result)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (p[data->i] != '\0')
	{
		if (handle_quotes(p, data, &in_single_quote, &in_double_quote))
			continue ;
		if (p[data->i] == '$' && p[data->i + 1] && p[data->i + 1] != ' '
			&& p[data->i + 1] != '\t' && !in_single_quote)
		{
			result = handle_variable_replacement(p, data, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = resize_result_if_needed(result, &data->k, data->j + 1);
			if (!result)
				return (NULL);
			result[data->j++] = p[data->i++];
		}
	}
	return (result);
}
