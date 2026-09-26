/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 15:46:43 by trakotos          #+#    #+#             */
/*   Updated: 2026/09/26 15:54:45 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>

char	*ft_strjoin(int size, char **strs, char *sep);
char	**ft_split(char *s, char c);
char	**ft_cleanup_2d(char **strs, int l);

#endif