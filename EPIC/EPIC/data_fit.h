#ifndef DATA_FIT_H_
#define DATA_FIT_H_

#define MAX_DATA 20

/* fit L datapoints by eliminating off track data points and averaging the remaining data */
uint8_t data_fit(uint8_t data[MAX_DATA], uint8_t L, uint8_t n_iter, uint8_t lim, uint8_t n_elim);

#endif
