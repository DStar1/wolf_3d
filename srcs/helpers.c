/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:38:34 by dmendelo          #+#    #+#             */
/*   Updated: 2018/11/09 14:47:27 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_print_strings(char **strings)
{
	int			p;

	p = 0;
	while (strings[p])
	{
		ft_putstr(strings[p]);
		write(1, "\n", 1);
		p += 1;
	}
}

char		*replace_char(char *s, int old, int new_)
{
	int			p;
	char		*new;

	new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	p = 0;
	while (s[p])
	{
		if (s[p] == old)
		{
			new[p] = (char)new_;
		}
		else
		{
			new[p] = s[p];
		}
		p += 1;
	}
	new[p] = '\0';
	return (new);
}

int			ptr_count(char **s)
{
	int			p;

	p = 0;
	while (s[p])
	{
		p += 1;
	}
	return (p);
}

static int			skip_whitespaces(char *str, int p)
{
	while (str[p] && (str[p] == ' ' || str[p] == '\t'))
	{
		p += 1;
	}
	return (p);
}

char                *ft_strdup_range(const char *str, int begin, int end)
{
    char            *duplicate;
    int             dp;
    int             sp;

	if (begin > end)
		return (NULL);
    duplicate = (char*)ft_memalloc(sizeof(char) * (end - begin + 2));
	sp = begin;
    dp = 0;
    while (sp <= end)
    {
        duplicate[dp] = str[sp];
        dp += 1;
        sp += 1;
    }
    duplicate[dp] = '\0';
    return (duplicate);
}

static int			count_words(char *str)
{
	int				word_count;
	int				p;

	p = 0;
	word_count = 0;
	while (str[p])
	{
		if (str[p] == ' ' || str[p] == '\t')
		{
			p = skip_whitespaces(str, p);
		}
		else
		{
			word_count += 1;
			while (str[p] && str[p] != '\t' && str[p] != ' ')
			{
				p += 1;
			}
		}
	}
	return (word_count);
}

char				**strsplit(char *str)
{
	char			**words;
	int				word_count;
	int				begin;
	int				p;
	int				wp;

	word_count = count_words(str);
	words = (char **)malloc(sizeof(char *) * (word_count + 1));
	p = 0;
	wp = 0;
	while (str[p])
	{
		if (str[p] == ' ' || str[p] == '\t')
		{
			p = skip_whitespaces(str, p);
		}
		else
		{
			begin = p;
			while (str[p] && str[p] != '\t' && str[p] != ' ')
			{
				p += 1;
			}
			words[wp] = ft_strdup_range(str, begin, p - 1);
			wp += 1;
		}
	}
	words[wp] = NULL;
	return (words);
}
