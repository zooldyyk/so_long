/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschmid <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:57:01 by eschmid           #+#    #+#             */
/*   Updated: 2021/10/19 13:49:50 by eschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int i)
{
	if (((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')
			|| (i >= '0' && i <= '9')))
		return (1);
	else
		return (0);
}
/*int main ()
{
    int i = 'e';
    
    printf("%d\n",ft_isalnum(i));
}*/