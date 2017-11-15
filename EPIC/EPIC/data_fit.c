#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "data_fit.h"

uint8_t dim = 1;

uint8_t average(uint8_t data[MAX_DATA], uint8_t L)
{
	uint16_t sum = 0;
	for(uint8_t i = 0; i < L; i++)
		sum += data[dim * i];
	return sum / L;
}

uint8_t distance(uint8_t data, uint8_t average)
{
	uint8_t d = abs(data-average);
	//printf("\ndata=%d, avarage=%d disatnce=%d\n\n", data, avareage, d);
	return d;
}

void order_data_distance(uint8_t data_dist[MAX_DATA][2], uint8_t L)
{
	uint8_t temp_1 = 0;
	uint8_t temp_2 = 0;
	
	for(uint8_t i = 0; i < L; i++)
	{
		for(uint8_t j = i + 1; j < L; j++)
		{
			if (data_dist[i][1] > data_dist[j][1])
			{
				temp_1 =  data_dist[i][1];
				data_dist[i][1] = data_dist[j][1];
				data_dist[j][1] = temp_1;
				temp_2 =  data_dist[i][0];
				data_dist[i][0] = data_dist[j][0];
				data_dist[j][0] = temp_2;
			}
		}
	}

}

uint8_t data_fit(uint8_t data[MAX_DATA], uint8_t L, uint8_t n_iter, uint8_t lim, uint8_t n_elim)
{
	uint8_t data_dist[L][2];
	uint8_t i = 0, j = 0;
	dim = 1;
	uint8_t avar=average(data, L);
	for(i = 0; i < L; i++)
	{
		data_dist[i][0] = data[i];
		data_dist[i][1] = distance(data[i], avar);
	}
	dim = 2;
	order_data_distance(data_dist, L);

	for(i = 0; i < n_iter; i++)
	{
		if(L - i <= 2)
			i = n_iter;
		if(data_dist[L - 1][1] < lim)
			i = n_iter;
		if(L - n_elim >= 2)
			L -= n_elim;
		avar = average(data_dist[0], L);
		for (j = 0; j < L; j++)
		{
			data_dist[j][1] = distance(data_dist[j][0], avar);
		}
		order_data_distance(data_dist, L);
	}

	if(data_dist[0][1] >= lim)
		L -= n_elim;
	else if(data_dist[L - 1][1] > lim && data_dist[0][1] < lim)
		for(i = 0; i < L; i++)
			if(data_dist[i][1] > lim)
			{
				L = i - 1;
				i = L;
			}
	avar = average(data_dist[0], L);
	dim = 1;
	return avar;
}
