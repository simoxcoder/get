#include "get_next_line.h"

char	*fill_stock(char *stock, int fd)
{
	char	*str;
	int		i;

	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (i != 0 && !ft_strchr(stock, '\n'))
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			if (stock)
				free(stock);
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		stock = ft_strjoin(stock, str);
	}
	free(str);
	return (stock);
}

char	*fill_line(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!*stock)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i += 1;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		str[j++] = stock[i++];
	if (stock[i] == '\n')
		str[j++] = stock[i++];
	str[j] = '\0';
	return (str);
}

char	*sec_save(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!*stock)
	{
		free(stock);
		return (NULL);
	}
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	str = malloc(ft_strlen(stock) - i + 1);
	j = 0;
	i += 1;
	while (stock[i])
		str[j++] = stock[i++];
	str[j] = '\0';
	free(stock);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stock = fill_stock(stock, fd);
	if (!stock)
		return (NULL);
	line = fill_line(stock);
	stock = sec_save(stock);
	return (line);
}
