#ifndef DATA_FIT_H_
#define DATA_FIT_H_

#define MAX_DATA 100

/* fit L datapoints by eliminating off track data points and averaging the remaining data */
int data_fit(int data[MAX_DATA], int L, int n_iter, int lim, int n_elim);

#endif
