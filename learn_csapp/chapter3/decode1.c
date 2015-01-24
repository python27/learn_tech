void decode1(int *px, int *py, int *pz)
{
	int t = *px;
	*px = *py;
	*py = *pz;
	*pz = t;
}
