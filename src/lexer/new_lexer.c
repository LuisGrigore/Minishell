/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:24:35 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 15:23:03 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

char *expand_word(t_environment *env, char *word)
{
	char *result;
	char *temp;
	char *var_value;
	char var_name[256];
	int i;
	int j;
	size_t len;

	if (!env || !word)
		return (NULL);

	result = ft_strdup("");
	if (!result)
		return (NULL);

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1])
		{
			i++;
			j = 0;
			while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
				var_name[j++] = word[i++];
			var_name[j] = '\0';

			if (j > 0)
			{
				var_value = env_get(env, var_name);
				if (var_value)
				{
					temp = result;
					result = ft_strjoin(result, var_value);
					free(temp);
					free(var_value);
					if (!result)
						return (NULL);
				}
			}
			i--;
		}
		else
		{
			len = ft_strlen(result);
			temp = ft_calloc(len + 2, sizeof(char));
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			ft_strlcpy(temp, result, len + 1);
			temp[len] = word[i];
			free(result);
			result = temp;
		}
		i++;
	}

	return (result);
}

int handle_single_quoted_word(char **current_char, t_gen_list *tokens, char *line)
{
    size_t start;
    size_t end;
    char *value;
    t_token *token;

    if (!current_char || !*current_char || !tokens || !line)
        return (LEXER_NULL_ERR);
    (*current_char)++;
    start = 0;
    end = start;
    while ((*current_char)[end] && (*current_char)[end] != '\'')
        end++;
    if ((*current_char)[end] != '\'')
        return (LEXER_UNCLOSED_QUOTE_ERR);
    value = ft_strndup(*current_char, end);
    if (!value)
        return (MS_ALLOCATION_ERR);
    token = create_token(TOKEN_WORD, value);
    if (!token)
    {
        free(value);
        return (MS_ALLOCATION_ERR);
    }
    gen_list_push_back(tokens, token);
    *current_char += end + 1;
    return (MS_OK);
}

int handle_double_quoted_word(char **current_char, t_gen_list *tokens, char *line, t_environment *env)
{
	size_t start;
	size_t end;
	char *value;
	char *expanded_value;
	t_token *token;

	start = 1;
	end = start;
	while (line[end] != '\"' && line[end] != '\0')
		end++;
	if (line[end] == '\0')
		return (LEXER_UNCLOSED_QUOTE_ERR);
	value = ft_strndup(&line[start], end - start);
	if (!value)
		return (MS_ALLOCATION_ERR);
	expanded_value = expand_word(env, value);
	free(value);
	if (!expanded_value)
		return (MS_ALLOCATION_ERR);
	if (*expanded_value == '\0')
	{
		free(expanded_value);
		*current_char += (end - start) + 2;
		return (MS_OK);
	}
	token = create_token(TOKEN_WORD, expanded_value);
	if (!token)
	{
		free(expanded_value);
		return (MS_ALLOCATION_ERR);
	}
	gen_list_push_back(tokens, token);
	*current_char += (end - start) + 2;
	return (MS_OK);
}
int handle_unquoted_word(char **current_char, t_gen_list *tokens, char *line, t_environment *env)
{
	size_t start;
	size_t end;
	char *value;
	char *expanded_value;
	t_token *token;

	start = 0;
	end = start;
	while (line[end] != '\0' && !is_space(line[end]) && !is_operator_char(line[end]))
		end++;
	value = ft_strndup(&line[start], end - start);
	if (!value)
		return (MS_ALLOCATION_ERR);
	expanded_value = expand_word(env, value);
	free(value);
	if (!expanded_value)
		return (MS_ALLOCATION_ERR);
	if (*expanded_value == '\0')
	{
		free(expanded_value);
		*current_char += end;
		return (MS_OK);
	}
	token = create_token(TOKEN_WORD, expanded_value);
	if (!token)
	{
		free(expanded_value);
		return (MS_ALLOCATION_ERR);
	}
	gen_list_push_back(tokens, token);
	*current_char += end;
	return (MS_OK);
}


int add_word_token(char **current_char, t_gen_list *tokens, char *line, t_environment *env)
{	
	if (**current_char == '\'')
		return (handle_single_quoted_word(current_char, tokens, line));
	if (**current_char == '\"')
		return (handle_double_quoted_word(current_char, tokens, line, env));
	return (handle_unquoted_word(current_char, tokens, line, env));
}

int add_operator_token(char **current_char, t_gen_list *tokens, char *line)
{
	size_t start;
	size_t end;
	char *value;
	t_token *token;

	start = 0;
	end = start;
	while (is_operator_char(line[end]))
		end++;
	value = ft_strndup(&line[start], end - start);
	if (!value)
		return (MS_ALLOCATION_ERR);
	token = create_token(operator_type(value, end - start), value);
	if (!token)
		return (free(value), MS_ALLOCATION_ERR);
	gen_list_push_back(tokens, token);
	*current_char += (end - start);
	return (MS_OK);
}

bool is_word_start_char(char c)
{
	return (!is_space(c) && !is_operator_char(c) && c != '\0');
}

int tokenize_aux(char *current_char, t_gen_list *tokens, char *line, t_environment *env)
{
    int status_code;
    
    if (!current_char || !tokens || !line)
        return (LEXER_NULL_ERR);
    while (*current_char && is_space(*current_char))
        current_char++;
        if (*current_char == '\0')
        return (MS_OK);
    if (is_word_start_char(*current_char))
        status_code = add_word_token(&current_char, tokens, current_char, env);
    else if (is_operator_char(*current_char))
        status_code = add_operator_token(&current_char, tokens, current_char);
    else
        return (LEXER_UNSUPORTED_CHARACTER_ERR);

    if (status_code != MS_OK)
        return (status_code);
    return (tokenize_aux(current_char, tokens, line, env));
}

int new_tokenize_line(char *line, t_gen_list *tokens, t_environment *env)
{
	return (tokenize_aux(line, tokens, line, env));
}