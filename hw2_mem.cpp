#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <cstring>

using namespace std;
const int TIMES = 10;
const int T = (1 << 26);
double a[T];

double test_empty(int S) {
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
	for (int j = 0; j < TIMES; j++) {
        for (int k = 0; k < S; k++) {
            for (int i = k; i < T; i += S) {
            }
        }
	}
	gettimeofday(&t2, NULL);
	double esc = (double)(t2.tv_sec - t1.tv_sec)*1000.0 + (double)(t2.tv_usec - t1.tv_usec)/1000.0;
	esc /= 1000.0;
    return esc;
}

double test_write(int S, double x) {
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
	for (int j = 0; j < TIMES; j++) {
        for (int k = 0; k < S; k++) {
            for (int i = k; i < T; i += S) {
                a[i] = x;
            }
        }
	}
	gettimeofday(&t2, NULL);
	double esc = (double)(t2.tv_sec - t1.tv_sec)*1000.0 + (double)(t2.tv_usec - t1.tv_usec)/1000.0;
	esc /= 1000.0;
    return esc;
}

double test_read(int S) {
    struct timeval t1, t2;
    double x;
    gettimeofday(&t1, NULL);
	for (int j = 0; j < TIMES; j++) {
        for (int k = 0; k < S; k++) {
            for (int i = k; i < T; i += S) {
                x = a[i];
            }
        }
	}
	gettimeofday(&t2, NULL);
	double esc = (double)(t2.tv_sec - t1.tv_sec)*1000.0 + (double)(t2.tv_usec - t1.tv_usec)/1000.0;
	esc /= 1000.0;
    return esc;
}

int main()
{
    for (int S = 1; S <= 512; S *= 2) {
        printf("Step = %d Byte\n", S * 8);
        double esc, esc2, esc3, sum_mbyte, speed;
        esc = test_empty(S);
        
        esc2 = test_write(S, 1024.0) - esc;
        esc2 /= TIMES;
        sum_mbyte = T * 8.0 / 1024.0 / 1024.0;
        speed = sum_mbyte / esc2;
        printf("Memory to CPU: write %.3lfMB/s\n", speed);
    
        esc3 = test_read(S)- esc;
        esc3 /= TIMES;
        sum_mbyte =  T * 8.0/ 1024.0 / 1024.0;
        speed = sum_mbyte / esc3;
        printf("Memory to CPU: read  %.3lfMB/s\n", speed);
    }
	return 0;
}