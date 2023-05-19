/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:06:03 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 10:39:34 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_char_sstar(char **src)
{
	int	i;

	i = -1;
	while (src[++i])
	{
		free(src[i]);
	}
		free(src);
}
