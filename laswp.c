/*
 * Copyright (c) xxx Technologies Co., Ltd. 2022. All rights reserved.
 * Description: DLASWP performs a series of row interchanges on the matrix A.
 * Author:  cqupt
 * Create:  2022-09-25
 */
// Function interface of DLASWP.
#ifdef SINGLE
typedef float dataType;
#define LASWP slaswp
#endif
#ifdef DOUBLE
typedef double dataType;
#define LASWP dlaswp
#endif
#ifdef COMPLEX
typedef float _Complex dataType;
#define LASWP claswp
#endif
#ifdef COMPLEX16
typedef double _Complex dataType;
#define LASWP zlaswp
#endif
void LASWP(const int *n, dataType *a, const int *lda, const int *k1, const int *k2, int *ipiv, int *incx)
{
    int i, i1, i2, inc, ip, ix, ix0, j, k, n32;
    dataType temp;
    int infoWp = 0;
    const int nNull = -1;
    const int aNull = -2;
    const int ldaNull = -3;
    const int k1Null = -4;
    const int k2Null = -5;
    const int ipivNull = -6;
    const int incxNull = -7;
    if (!n) {
        infoWp = nNull;
    } else if (!a) {
        infoWp = aNull;
    } else if (!lda) {
        infoWp = ldaNull;
    } else if (!k1) {
        infoWp = k1Null;
    } else if (!k2) {
        infoWp = k2Null;
    } else if (!ipiv) {
        infoWp = ipivNull;
    } else if (!incx) {
        infoWp = incxNull;
    }
    if (infoWp != 0) {
        infoWp = -infoWp;
        int *p;
        *p = infoWp;
        xerbla_("LASWP ", p);
        return;
    }
    // Interchange row I with row IPIV(K1+(I-K1)*abs(INCX)) for each of rows K1 through K2.
    if (*incx > 0) {
        ix0 = *k1;
        i1 = *k1;
        i2 = *k2;
        inc = 1;
    } else if (*incx < 0) {
        ix0 = *k1 + (*k1 - *k2) * (*incx);
        i1 = *k2;
        i2 = *k1;
        inc = -1;
    } else {
        return;
    }
    n32 = (*n / 32) * 32;
    if (n32 != 0) {
        for (j = 1; j <= n32; j += 32) {
            ix = ix0;
            for (i = i1; i <= i2; i += inc) {
                ip = ipiv[ix - 1];
                if (ip != i) {
                    for (k = j; k <= (j + 31); k++) {
                        temp = a[(k - 1) * (*lda) + i - 1];
                        a[(k - 1) * (*lda) + i - 1] = a[(k - 1) * (*lda) + ip - 1];
                        a[(k - 1) * (*lda) + ip - 1] = temp;
                    }
                }
                ix = ix + (*incx);
            }
        }
    }
    if (n32 != *n) {
        n32 = n32 + 1;
        ix = ix0;
        for (i = i1; i <= i2; i += inc) {
            ip = ipiv[ix - 1];
            if (ip != i) {
                for (k = n32; k <= *n; k++) {
                    temp = a[(k - 1) * (*lda) + i - 1];
                    a[(k - 1) * (*lda) + i - 1] = a[(k - 1) * (*lda) + ip - 1];
                    a[(k - 1) * (*lda) + ip - 1] = temp;
                }
            }
            ix = ix + (*incx);
        }
    }
    return;
    // END OF DLASWP
}
