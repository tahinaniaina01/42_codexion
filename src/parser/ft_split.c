/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:36:19 by trakotos          #+#    #+#             */
/*   Updated: 2026/09/26 15:52:20 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

static char	*ft_substr(char *s, int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > (size_t)ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		sub[0] = '\0';
		return (sub);
	}
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static size_t	ft_count_word(char const *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] != c)
		count++;
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i - 1] == c && str[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_cleanup_2d(char **strs, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		if (strs[i] != NULL)
			free(strs[i]);
		i++;
	}
	if (strs != NULL)
		free(strs);
	return (NULL);
}

static size_t	ft_strlen_word(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	strs = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			strs[j] = ft_substr(&s[i], 0, ft_strlen_word((char *)&s[i], c));
			if (strs[j] == NULL)
				return (ft_cleanup_2d(strs, j));
			i += ft_strlen_word((char *)&s[i], c) - 1;
			j++;
		}
		i++;
	}
	strs[j] = NULL;
	return (strs);
}
