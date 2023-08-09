/*
 * Copyright  (c) xxx Technologies Co., Ltd. 2022. All rights reserved.
 * Description: DGBTRF computes an LU factorization of a real m-by-n band matrix A.
 * Author: cqupt
 * Create: 2022-09-25
 */
#include <complex.h>
#ifdef SINGLE
typedef float dataType;
#define GBTRF sgbtrf
#define GBTF2 sgbtf2
#define LASWP slaswp
#define IAMAX isamax_
#define SWAP sswap_
#define SCAL sscal_
#define GER sger_
#define COPY scopy_
#define TRSM strsm_
#define GEMM sgemm_
#endif
#ifdef DOUBLE
typedef double dataType;
#define GBTRF dgbtrf
#define GBTF2 dgbtf2
#define LASWP dlaswp
#define IAMAX idamax_
#define SWAP dswap_
#define SCAL dscal_
#define GER dger_
#define COPY dcopy_
#define TRSM dtrsm_
#define GEMM dgemm_
#endif
#ifdef COMPLEX
typedef float _Complex dataType;
#define GBTRF cgbtrf
#define GBTF2 cgbtf2
#define LASWP claswp
#define IAMAX icamax_
#define SWAP cswap_
#define SCAL cscal_
#define GER cgeru_
#define COPY ccopy_
#define TRSM ctrsm_
#define GEMM cgemm_
#endif
#ifdef COMPLEX16
typedef double _Complex dataType;
#define GBTRF zgbtrf
#define GBTF2 zgbtf2
#define LASWP zlaswp
#define IAMAX izamax_
#define SWAP zswap_
#define SCAL zscal_
#define GER zgeru_
#define COPY zcopy_
#define TRSM ztrsm_
#define GEMM zgemm_
#endif
// Function interface of GBTRF.
void GBTRF(const int *m, const int *n, const int *kl, const int *ku,
           dataType *AB_2, const int *ldab, int *ipiv, int *info)
{
    const int NBMAX = 64;
    const int LDWORK = 65;
    dataType one = 1.0 + 0 * I, zero = 0.0 + 0 * I;
    int i, i2, i3, ii, ip, j, j2, j3, jb, jj, jm, jp, ju, k2, km, kv, nb, nw;
    dataType temp;
    dataType work13[LDWORK * NBMAX], work31[LDWORK * NBMAX];
    int ld, ispec, incx;
    ld = *ldab - 1;
    ispec = 1;
    incx = 1;
    dataType one1;
    one1 = -one;
    // kv is the number of superdiagonals in the factor U, allowing for fill-in.
    kv = *kl + *ku;
    // Test whether the input parameter is null pointer
    int infoTrf = 0;
    const int mNull = -1;
    const int nNull = -2;
    const int klNull = -3;
    const int kuNull = -4;
    const int AB_2Null = -5;
    const int ldabNull = -6;
    const int ipivNull = -7;
    const int infoNull = -8;
    if (!m) {
        infoTrf = mNull;
    } else if (!n) {
        infoTrf = nNull;
    } else if (!kl) {
        infoTrf = klNull;
    } else if (!ku) {
        infoTrf = kuNull;
    } else if (!AB_2) {
        infoTrf = AB_2Null;
    } else if (!ldab) {
        infoTrf = ldabNull;
    } else if (!ipiv) {
        infoTrf = ipivNull;
    } else if (!info) {
        infoTrf = infoNull;
    }
    if (infoTrf != 0) {
        infoTrf = -infoTrf;
        int info2;
        info2 = infoTrf; 
        xerbla_("GBTRF ", &info2);
        return;
    }
    // Test the input parameters.
    int info1 = 0;
    *info = 0;
    if (*m < 0) {
        info1 = mNull;
    } else if (*n < 0) {
        info1 = nNull;
    } else if (*kl < 0) {
        info1 = klNull;
    } else if (*ku < 0) {
        info1 = kuNull;
    } else if (*ldab < *kl + kv + 1) {
        info1 = ldabNull;
    }
    info1 = -info1;
    if (info1 != 0) {
        int info5;
        info5=info1;
        xerbla_("GBTRF ", &info5);
        return;
    }
    // Quick return.
    if (*m == 0 || *n == 0) {
        return;
    }
    int rowBlockLine, remainingRows, i4;
    rowBlockLine = *kl / omp_get_max_threads();
    remainingRows = *kl % omp_get_max_threads();
#ifdef SINGLE
    char name[16] = "SGBTRF";
    nb = ilaenv_(&ispec, &name, " ", &(*m), &(*n), &(*kl), &(*ku));
#endif
#ifdef DOUBLE
    char name[16] = "DGBTRF"; 
    nb = ilaenv_(&ispec, &name, " ", &(*m), &(*n), &(*kl), &(*ku));
#endif
#ifdef COMPLEX
    char name[16] = "CGBTRF";
    nb = ilaenv_(&ispec, &name, " ", &(*m), &(*n), &(*kl), &(*ku));
#endif
#ifdef COMPLEX16
    char name[16] = "ZGBTRF";
    nb = ilaenv_(&ispec, &name, " ", &(*m), &(*n), &(*kl), &(*ku));
#endif
    nb = Min(nb, NBMAX);
    if (*n>900) {
        nb = 1;
    }
    if (nb <= 1 || nb > *kl) {
        GBTF2(&(*m), &(*n), &(*kl), &(*ku), AB_2, &(*ldab), ipiv, &(*info));
    } else {
        // Sets the superdiagonal elements of the work array WORK13 to zero.
#pragma gcc loop unroll(enable)
        for (j = 1; j <= nb; j++) {
            for (i = 1; i <= j - 1; i++) {
                work13[LDWORK * (j - 1) + i - 1] = zero;
            }
        }
        // Sets the subdiagonal elements of the work array WORK31 to zero.
#pragma gcc loop unroll(enable)
        for (j = 1; j <= nb; j++) {
            for (i = j + 1; i <= nb; i++) {
                work31[LDWORK * (j - 1) + i - 1] = zero;
            }
        }
        // Gaussian elimination of partial rotation.
        // Set the filling elements in columns KU+2 to KV to be zero.
#pragma gcc loop unroll(enable)
        for (j = *ku + 2; j <= Min(kv, *n); j++) {
            for (i = kv - j + 2; i <= *kl; i++) {
                AB_2[(*ldab) * (j - 1) + i - 1] = zero;
            }
        }
        // JU is the index of the last column affected by the current.
        ju = 1;
        for (j = 1; j <= Min(*m, *n); j += nb) {
            jb = Min(nb, (Min(*m, *n) - j + 1));
            i2 = Min(*kl - jb, *m - j - jb + 1);
            i3 = Min(jb, *m - j - *kl + 1);
            //  Calculate J2 and J3 after JU updates.
            //  Decompose the current block of the JB columns.
            for (jj = j; jj <= j + jb - 1; jj++) {
                // Set the filling elements in column JJ+KV to zero.
                if (jj + kv <= *n) {
#pragma gcc loop unroll(enable)
                    for (i = 1; i <= *kl; i++) {
                        AB_2[(*ldab) * (jj + kv - 1) + i - 1] = zero;
                    }
                }
                // KM is the number of subdiagonal elements in the current column.
                km = Min(*kl, *m - jj);
                int k = km + 1;
                jp = IAMAX(&k, &AB_2[(*ldab) * (jj - 1) + kv], &incx);
                ipiv[jj - 1] = jp + jj - j;
                if (AB_2[(*ldab) * (jj - 1) + kv + jp - 1] != 0) {
                    ju = Max(ju, Min(jj + *ku + jp - 1, *n));
                    if (jp != 1) {
                        // SWAP interchanges columns J to J+JB-1.
                        if ((jp + jj - 1) < (j + *kl)) {
                            SWAP(&jb, &AB_2[(*ldab) * (j - 1) + kv + jj - j], &ld,
                                 &AB_2[(*ldab) * (j - 1) + kv + jp + jj - j - 1], &ld);
                        } else {
                            // The exchange affects columns J to JJ-1 of A31, which are stored in the work array WORK31.
                            int j1 = jj - j;
                            SWAP(&j1, &AB_2[(*ldab) * (j - 1) + kv + jj - j], &ld,
                                 &work31[jp + jj - j - *kl - 1], &LDWORK);
                            int b = j + jb - jj;
                            SWAP(&b, &AB_2[(*ldab) * (jj - 1) + kv], &ld,
                                 &AB_2[(*ldab) * (jj - 1) + kv + jp - 1], &ld);
                        }
                    }
                    dataType a = one / AB_2[(*ldab) * (jj - 1) + kv];
                    SCAL(&km, &a, &AB_2[(*ldab) * (jj - 1) + kv + 1], &incx);
                    // Updates trailing submatrices in the band and in the current block.
                    // JM is the index of the last column to be updated.
                    jm = Min(ju, j + jb - 1);
                    if (jm > jj) {
                        int j4 = jm - jj;
                        if (km < *kl) {
                            GER(&km, &j4, &one1, &AB_2[(*ldab) * (jj - 1) + kv + 1], &incx,
                                &AB_2[(*ldab) * jj + kv - 1], &ld, &AB_2[(*ldab) * jj + kv], &ld);
                        } else {
#pragma omp parallel for
                        for (i4 = 0; i4 < omp_get_max_threads(); i4++) {
                            GER(&rowBlockLine, &j4, &one1, &AB_2[(*ldab) * (jj - 1) + kv + 1+i4*rowBlockLine], &incx,
                                &AB_2[(*ldab) * jj + kv - 1], &ld, &AB_2[(*ldab) * jj + kv+i4*rowBlockLine], &ld);
                        }
                        i4 = omp_get_max_threads();
                        GER(&remainingRows, &j4, &one1, &AB_2[(*ldab) * (jj - 1) + kv + 1+i4*rowBlockLine], &incx,
                            &AB_2[(*ldab) * jj + kv - 1], &ld, &AB_2[(*ldab) * jj + kv+i4*rowBlockLine], &ld);
                        }
                    }
                } else {
                    // If pivot is zero, INFO is set to the index of the pivot unless a zero pivot has been found.
                    if (*info == 0) {
                        *info = jj;
                    }
                }
                // The current column of A31 is copied into the array WORK31.
                nw = Min(jj - j + 1, i3);
                if (nw > 0) {
                    COPY(&nw, &AB_2[(*ldab) * (jj - 1) + kv + *kl - jj + j], &incx,
                         &work31[LDWORK * (jj - j)], &incx);
                }
            }
            if ((j + jb) <= *n) {
                // Apply row swapping to other blocks.
                j2 = Min(ju - j + 1, kv) - jb;
                j3 = Max(0, ju - j - kv + 1);
                LASWP(&j2, &AB_2[(*ldab) * (j + jb - 1) + kv - jb], &ld, &incx, &jb, &ipiv[j - 1], &incx);
                // Adjust the pivot indices.
                for (i = j; i <= j + jb - 1; i++) {
                    ipiv[i - 1] = ipiv[i - 1] + j - 1;
                }
                // Apply the row interchanges to A13, A23, and A33 columnwise.
                k2 = j - 1 + jb + j2;
                for (i = 1; i <= j3; i++) {
                    jj = k2 + i;
                    for (ii = j + i - 1; ii <= (j + jb - 1); ii++) {
                        ip = ipiv[ii - 1];
                        if (ip != ii - 1) {
                            temp = AB_2[(*ldab) * (jj - 1) + kv + ii - jj];
                            AB_2[(*ldab) * (jj - 1) + kv + ii - jj] = AB_2[(*ldab) * (jj - 1) + kv + ip - jj];
                            AB_2[(*ldab) * (jj - 1) + kv + ip - jj] = temp;
                        }
                    }
                }
// Update the relevant part of the trailing submatrix.
#pragma omp parallel sections
                {
#pragma omp section
                    if (j2 > 0) {
                        // Update A12
                        TRSM("Left", "Lower", "No transpose", "Unit", &jb, &j2, &one, &AB_2[(*ldab) * (j - 1) + kv],
                             &ld, &AB_2[(*ldab) * (j + jb - 1) + kv - jb], &ld);
                        if (i2 > 0) {
                            // Update A22
                            GEMM("No transpose", "No transpose", &i2, &j2, &jb, &one1,
                              &AB_2[(*ldab) * (j - 1) + kv + jb], &ld, &AB_2[(*ldab) * (j + jb - 1) + kv - jb], &ld,
                                 &one, &AB_2[(*ldab) * (j + jb - 1) + kv], &ld);
                        }
                        if (i3 > 0) {
                            // Update A32
                            GEMM("No transpose", "No transpose", &i3, &j2, &jb, &one1, work31, &LDWORK,
                                 &AB_2[(*ldab) * (j + jb - 1) + kv - jb], &ld, &one,
                                 &AB_2[(*ldab) * (j + jb - 1) + kv + *kl - jb], &ld);
                        }
                    }
#pragma omp section
                    if (j3 > 0) {
                        //  Copy the lower triangle of A13 into the work array WORK13.
                        for (jj = 1; jj <= j3; jj++) {
                            for (ii = jj; ii <= jb; ii++) {
                                work13[LDWORK * (jj - 1) + ii - 1] = AB_2[(jj + j + kv - 2) * (*ldab) + ii - jj];
                            }
                        }
                        // Update A13 in the work array.
                        TRSM("Left", "Lower", "No transpose", "Unit", &jb, &j3, &one,
                             &AB_2[(*ldab) * (j - 1) + kv], &ld, work13, &LDWORK);
                        if (i2 > 0) {
                            // Update A23
                            GEMM("No transpose", "No transpose", &i2, &j3, &jb, &one1,
                               &AB_2[(*ldab) * (j - 1) + kv + jb], &ld, work13, &LDWORK,
                               &one, &AB_2[(*ldab) * (j + kv - 1) + jb], &ld);
                        }
                        if (i3 > 0) {
                            // Update A33
                            GEMM("No transpose", "No transpose", &i3, &j3, &jb, &one1, work31, &LDWORK, work13,
                                 &LDWORK, &one, &AB_2[(*ldab) * (j + kv - 1) + *kl], &ld);
                        }
                        // The lower triangle of A13 is copied back into place.
                        for (jj = 1; jj <= j3; jj++) {
                            for (ii = jj; ii <= jb; ii++) {
                                AB_2[(jj + j + kv - 2) * (*ldab) + ii - jj] = work13[LDWORK * (jj - 1) + ii - 1];
                            }
                        }
                    }
                }
            } else {
                // Adjust the pivot indices.
                for (i = j; i <= j + jb - 1; i++) {
                    ipiv[i - 1] = ipiv[i - 1] + j - 1;
                }
            }
            // Shape A31 and copy the upper triangle of A31 into normal position.
            for (jj = j + jb - 1; jj >= j; jj--) {
                jp = ipiv[jj - 1] - jj + 1;
                if (jp != 1) {
                    // Apply the swap of column J to JJ - 1.
                    if ((jp + jj - 1) < (j + *kl)) {
                        // If the interchange does not affect A31.
                        int j1 = jj - j;
                        SWAP(&j1, &AB_2[(*ldab) * (j - 1) + kv + jj - j], &ld,
                             &AB_2[(*ldab) * (j - 1) + kv + jp + jj - j - 1], &ld);
                    } else {
                        // If the interchange does affect A31.
                        int j1 = jj - j;
                        SWAP(&j1, &AB_2[(*ldab) * (j - 1) + kv + jj - j], &ld,
                             &work31[jp + jj - j - *kl - 1], &LDWORK);
                    }
                }
                // Copy the current front of A31 back to the original position.
                nw = Min(i3, jj - j + 1);
                if (nw > 0) {
                    COPY(&nw, &work31[LDWORK * (jj - j)], &incx,
                         &AB_2[(*ldab) * (jj - 1) + kv + *kl - jj + j], &incx);
                }
            }
        }
    }
    return;
    // END OF DGBTRF
}
