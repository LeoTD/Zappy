int		relative_east(int dir)
{
	if (dir < 7)
		return (dir + 2);
	return (dir - 6);
}

int		relative_west(int dir)
{
	if (dir < 5)
		return (dir + 4);
	return (dir - 4);
}

int		relative_south(int dir)
{
	if (dir < 3)
		return (dir + 6);
	return (dir - 2);
}
