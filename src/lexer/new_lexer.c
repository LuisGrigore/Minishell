/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:24:35 by lgrigore          #+#    #+#             */
/*   Updated: 2025/11/10 18:51:56 by lgrigore         ###   ########.fr       */
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
			if (word[i] == '?')
			{
				var_value = env_get(env, "?");
				i++;
			}
			else
			{
				while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
					var_name[j++] = word[i++];
				var_name[j] = '\0';
				if (j > 0)
					var_value = env_get(env, var_name);
				else
					var_value = NULL;
			}
			
			if (var_value)
			{
				temp = result;
				result = ft_strjoin(result, var_value);
				free(temp);
				free(var_value);
				if (!result)
					return (NULL);
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




char *handle_single_quotes(char **current_char, char *line)
{
	char *start;
	
	*current_char ++;
	start = *current_char;
	while (**current_char != '\0' && **current_char != '\'')
		*current_char++;
	if (**current_char != '\0')
		return NULL;
	return ft_substr(line, (line - start), *current_char - start);
		
}

int add_word_token(char **current_char, t_gen_list *tokens, char *line, t_environment *env)
{	
	char *p;
	size_t i;
	char *buf;
	char *seg;
	char *tmp;
	char *var;
	size_t j;
	t_token *token;

	if (!current_char || !*current_char || !tokens)
		return (LEXER_NULL_ERR);

	p = *current_char;
	i = 0;
	buf = ft_strdup("");
	if (!buf)
		return (MS_ALLOCATION_ERR);

	while (p[i] && !is_space(p[i]) && !is_operator_char(p[i]))
	{
		if (p[i] == '\'')
		{
			/* single quoted: take literal untile nxt ' */
			size_t start = ++i;
			while (p[i] && p[i] != '\'')
				i++;
			if (!p[i])
			{
				free(buf);
				return (LEXER_UNCLOSED_QUOTE_ERR);
			}
			seg = ft_strndup(&p[start], i - start);
			if (!seg)
			{
				free(buf);
				return (MS_ALLOCATION_ERR);
			}
			tmp = ft_strjoin(buf, seg);
			free(buf);
			free(seg);
			if (!tmp)
				return (MS_ALLOCATION_ERR);
			buf = tmp;
			i++; /* skip closing ' */
		}
		else if (p[i] == '"')
		{
			/* double quoted: allow expansion inside */
			size_t start = ++i;
			while (p[i] && p[i] != '"')
			{
				if (p[i] == '$')
				{
					/* append preceding chunk */
					if (i > start)
					{
						seg = ft_strndup(&p[start], i - start);
						if (!seg)
						{
							free(buf);
							return (MS_ALLOCATION_ERR);
						}
						tmp = ft_strjoin(buf, seg);
						free(buf);
						free(seg);
						if (!tmp)
							return (MS_ALLOCATION_ERR);
						buf = tmp;
					}
					/* parse variable */
					i++;
					if (p[i] == '?')
					{
						var = env_get(env, "?");
						i++;
						if (var)
						{
							tmp = ft_strjoin(buf, var);
							free(buf);
							free(var);
							if (!tmp)
								return (MS_ALLOCATION_ERR);
							buf = tmp;
						}
						start = i;
					}
					else
					{
						j = 0;
						char name[256];
						while (p[i] && (ft_isalnum(p[i]) || p[i] == '_') && j + 1 < sizeof(name))
							name[j++] = p[i++];
						name[j] = '\0';
						if (j > 0)
						{
							var = env_get(env, name);
							if (var)
							{
								tmp = ft_strjoin(buf, var);
								free(buf);
								free(var);
								if (!tmp)
									return (MS_ALLOCATION_ERR);
								buf = tmp;
							}
							start = i;
						}
						else
						{
							/* '$' not followed by name: treat as literal '$' */
							tmp = ft_strjoin(buf, "$");
							free(buf);
							if (!tmp)
								return (MS_ALLOCATION_ERR);
							buf = tmp;
							/* don't consume the next char (i already points to it) */
							start = i;
						}
					}
					continue;
				}
				i++;
			}
			if (!p[i])
			{
				free(buf);
				return (LEXER_UNCLOSED_QUOTE_ERR);
			}
			/* append remaining inside-double-quotes chunk */
			if (i > start)
			{
				seg = ft_strndup(&p[start], i - start);
				if (!seg)
				{
					free(buf);
					return (MS_ALLOCATION_ERR);
				}
				tmp = ft_strjoin(buf, seg);
				free(buf);
				free(seg);
				if (!tmp)
					return (MS_ALLOCATION_ERR);
				buf = tmp;
			}
			i++; /* skip closing " */
		}
		else
		{
			/* unquoted: copy until special or handle $ */
			size_t start = i;
			while (p[i] && !is_space(p[i]) && !is_operator_char(p[i]) && p[i] != '\'' && p[i] != '"' && p[i] != '$')
				i++;
			if (i > start)
			{
				seg = ft_strndup(&p[start], i - start);
				if (!seg)
				{
					free(buf);
					return (MS_ALLOCATION_ERR);
				}
				tmp = ft_strjoin(buf, seg);
				free(buf);
				free(seg);
				if (!tmp)
					return (MS_ALLOCATION_ERR);
				buf = tmp;
			}
			if (p[i] == '$')
			{
				i++;
				if (p[i] == '?')
				{
					var = env_get(env, "?");
					i++;
					if (var)
					{
						tmp = ft_strjoin(buf, var);
						free(buf);
						free(var);
						if (!tmp)
							return (MS_ALLOCATION_ERR);
						buf = tmp;
					}
				}
				else
				{
					j = 0;
					char name[256];
					while (p[i] && (ft_isalnum(p[i]) || p[i] == '_') && j + 1 < sizeof(name))
						name[j++] = p[i++];
					name[j] = '\0';
					if (j > 0)
					{
						var = env_get(env, name);
						if (var)
						{
							tmp = ft_strjoin(buf, var);
							free(buf);
							free(var);
							if (!tmp)
								return (MS_ALLOCATION_ERR);
							buf = tmp;
						}
					}
					else
					{
						/* treat lone '$' as literal */
						tmp = ft_strjoin(buf, "$");
						free(buf);
						if (!tmp)
							return (MS_ALLOCATION_ERR);
						buf = tmp;
					}
				}
			}
		}
	}

	/* advance the caller pointer */
	*current_char += i;

	if (!buf)
		return (MS_ALLOCATION_ERR);
	if (*buf == '\0')
	{
		free(buf);
		return (MS_OK);
	}
	token = create_token(TOKEN_WORD, buf);
	if (!token)
	{
		free(buf);
		return (MS_ALLOCATION_ERR);
	}
	gen_list_push_back(tokens, token);
	return (MS_OK);
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