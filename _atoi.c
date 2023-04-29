#include "main.h"

/**
 * _atoi - convert the number in string to integer values
 * @s: string variable pointer
 * Return: the ineger value of the number, if there is no number in s return 0
 */

int _atoi(char *s)
{
	int i = 0, sign = 1;
	unsigned int num = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign = sign * -1;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = num * 10 + (s[i] - '0');
		}
		if (num > 0 && (s[i] < '0' || s[i] > '9'))
		{
			break;
		}
		i++;
	}
	return (num * sign);
}
