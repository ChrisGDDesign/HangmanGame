int ft_atoi(char *str)
{
    int res;
    int i;

    i = 0;
    res = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + (str[i] - 48);
        i++;
    }
    return (res);
}