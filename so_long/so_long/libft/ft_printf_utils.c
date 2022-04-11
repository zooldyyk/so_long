/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 11:36:08 by zoldyyk           #+#    #+#             */
/*   Updated: 2022/03/20 15:31:49 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

void  ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
      write(1, &str[i], 1);
      i++;
    }
}

int ft_printstr(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
    {
        ft_putstr("(null)");
        return (6);
    }
    while (str[i])
    {
      write(1, &str[i], 1);
      i++;
    }
    return (i);
}

int ft_printnbr(int n)
{
  int   len;
  char  *num;

  len = 0;
  num = ft_itoa(n);
  len = ft_printstr(num);
    free(num);
  return (len);
}

int ft_printpercent()
{
    write (1, "%" , 1);
    return (1);
}

    
