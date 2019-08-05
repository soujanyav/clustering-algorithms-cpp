void quickSort(double* numbers, int* index,int array_size);
void q_sort(double* numbers, int* index, int left, int right);

void quickSort(double* numbers, int* index,int array_size)
{
  	q_sort(numbers, index, 0, array_size - 1);
}

void q_sort(double* numbers, int* index, int left, int right)
{
	double pivot;
	int temp;
	int l_hold, r_hold;
	int index_pivot;

	l_hold = left;
	r_hold = right;
	pivot = numbers[left];
	index_pivot = index[left];

	while (left < right)
	{
		while ((numbers[right] >= pivot) && (left < right))
			right--;
		if (left != right)
		{
			numbers[left] = numbers[right];
			index[left] = index[right];
			left++;
		}

		while ((numbers[left] <= pivot) && (left < right))
			left++;
		if (left != right)
		{
			numbers[right] = numbers[left];
			index[right] = index[left];
			right--;
		}
	}
	numbers[left] = pivot;
	index[left] = index_pivot;

	temp = left;
	left = l_hold;
	right = r_hold;

	if (left < temp)
		q_sort(numbers, index,left, temp-1);

	if (right > temp)
		q_sort(numbers, index,temp+1, right);
}
