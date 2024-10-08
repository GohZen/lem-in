/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prossi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:38:15 by prossi            #+#    #+#             */
/*   Updated: 2021/09/20 16:10:38 by prossi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compare les deux chaînes de caractères jusqu'à 'n' caractères ou jusqu'à ce qu'une différence soit trouvée. 
// Elle retourne :
//	- 0 si les chaînes sont identiques sur les n premiers caractères.
//	- Un nombre positif ou négatif selon la différence entre les deux chaînes (en fonction de l'ordre lexicographique des caractères).
int	ft_strncmp(const char *s1, char *s2, size_t n)
{
	while (*s1 != '\0' && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
