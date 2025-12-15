/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:19:21 by mchiacha          #+#    #+#             */
/*   Updated: 2025/12/08 14:20:18 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "../Libft/libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr_base(unsigned long long nb, const char *base)
{
	unsigned long long	len;
	int					count;

	count = 0;
	len = ft_strlen(base);
	if (nb >= len)
		count += ft_putnbr_base(nb / len, base);
	count += ft_putchar(base[nb % len]);
	return (count);
}

int	ft_handle_int(va_list ap)
{
	long long	n;
	int			neg;

	n = va_arg(ap, int);
	neg = 0;
	if (n < 0)
	{
		n *= -1;
		neg++;
		write(1, "-", 1);
	}
	return (ft_putnbr_base(n, "0123456789") + neg);
}

static int	ft_specifier(char c, va_list ap)
{
	if (c == 'd')
		return (ft_handle_int(ap));
	return (write(1, &c, 1));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	if (!format)
		return (0);
	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && !*(format + 1))
			break ;
		else if (*format == '%')
			count += ft_specifier(*(++format), ap);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
