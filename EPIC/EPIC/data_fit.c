#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "data_fit.h"

int dim=1;

int avareage (int data[MAX_DATA], int L)
{
	int i=0;
	int sum=0;
	for(i=0;i<L;i++)
		sum += data[dim*i];
	return sum/L;
}

int distance (int data, int avareage)
{
	int d=abs(data-avareage);
	//printf("\ndata=%d, avarage=%d disatnce=%d\n\n", data, avareage, d);
	return d;
}

void order_data_distance (int data_dist[MAX_DATA][2], int L)
{
	int temp_1=0;
	int temp_2=0;
	int j=0;
	int i=0;
	for(i=0;i<L;i++)
	{
		for(j=i+1;j<L;j++)
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
int data_fit(int data[MAX_DATA], int L, int n_iter, int lim, int n_elim)
{
	int data_dist[L][2];
	int i=0, j=0;
	dim=1;
	int avar=avareage(data, L);
	for (i=0;i<L;i++)
	{
		data_dist[i][0]=data[i];

		data_dist[i][1]=distance(data[i], avar);
	}
	dim=2;
	order_data_distance(data_dist, L);
	/*for(int p=0;p<L;p++)
			printf("data %d =%d, dist=%d \n", p, data_dist[p][0],data_dist[p][1]);
	printf("\n");*/
	for(i=0;i<n_iter;i++)
	{
		if(L-i<=2)
			i=n_iter;
		if(data_dist[L-1][1]<lim)
			i=n_iter;
		if(L-n_elim>=2)
			L-=n_elim;
		avar=avareage(data_dist[0], L);
		for (j=0;j<L;j++)
		{
			data_dist[j][1]=distance(data_dist[j][0], avar);
		}
		order_data_distance(data_dist, L);
	}
	if(data_dist[0][1]>=lim)
		L-=n_elim;
	else if(data_dist[L-1][1]>lim && data_dist[0][1]<lim)
		for(i=0;i<L;i++)
			if(data_dist[i][1]>lim)
			{
				L=i-1;
				i=L;
			}
	avar=avareage(data_dist[0], L);
	dim=1;
	return avar;
}
