#include "simple_shell.h"

/**
 * _atoi - converts a string to an integer
 * @str: string to be converted
 * Return: integer value of the string
 */

int	_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

/**
 * _itoa - converts an integer to a string
 * @n: integer to be converted
 * Return: pointer to the converted string
 */

char	*_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = (long int) n;
	i = ft_nbrlen(nb);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	if (nb == 0)
		str[0] = nb + 48;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	return (str);
}
