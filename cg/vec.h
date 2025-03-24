#include <math.h>

void add(float res[], float a[], float b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        res[i] = a[i] + b[i];
    }
}

void sub(float res[], float a[], float b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        res[i] = a[i] - b[i];
    }
}

void cross(float res[], float a[], float b[], int n)
{
    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = -(a[0] * b[2] - a[2] * b[0]);
    res[2] = a[0] * b[1] - a[1] * b[0];
}

float getMag(float vec[], int n)
{
    float mag = 0;
    for (int i = 0; i < n; mag += vec[i] * vec[i], i++)
        ;
    mag = sqrt(mag);
    return mag;
}

void normalize(float res[], float vec[], int n)
{
    float mag = getMag(vec, n);
    if (mag == 0)
        mag = 1;
    for (int i = 0; i < n; i++)
        res[i] /= mag;
}

float **Rx, **Ry, **Rz, **R, **I1;

void init_vec()
{
    Rx = (float **)malloc(3 * sizeof(float));
    Ry = (float **)malloc(3 * sizeof(float));
    Rz = (float **)malloc(3 * sizeof(float));

    R = (float **)malloc(3 * sizeof(float));
    I1 = (float **)malloc(3 * sizeof(float));

    for (int i = 0; i < 3; i++)
    {

        Rx[i] = (float *)malloc(3 * sizeof(float));
        Ry[i] = (float *)malloc(3 * sizeof(float));
        Rz[i] = (float *)malloc(3 * sizeof(float));

        R[i] = (float *)malloc(3 * sizeof(float));
        I1[i] = (float *)malloc(3 * sizeof(float));
    }
}

void fill(float **matrix, int r, int c, float val)
{
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            matrix[i][j] = val;
}

void fill_vec(float vec[], int n, float val)
{
    for (int i = 0; i < n; i++)
    {
        vec[i] = val;
    }
}

void clear(float **matrix, int r, int c)
{
    fill(matrix, r, c, 0.0f);
}

void mat_mul(float **res, float **A, int ar, int ac, float **B, int br, int bc)
{
    if (ac != br)
    {
        printf("Incompatible shapes for mat_mul : A : %d %d , B : %d %d", ar, ac, br, bc);
        return;
    }
    for (int resi = 0; resi < ar; resi++)
    {
        for (int resj = 0; resj < bc; resj++)
        {
            for (int c = 0; c < br; c++)
            {
                res[resi][resj] += A[resi][c] * B[c][resj];
            }
        }
    }
}

void mat_vec_mul(float res[], float **A, int r, int c, float vec[], int l)
{
    for (int res_idx = 0; res_idx < l; res_idx++)
    {
        for (int j = 0; j < c; j++)
        {
            res[res_idx] += A[res_idx][j] * vec[j];
        }
    }
}

void rotate(float res[], float vec[], float angles[])
{
    float **matrix_ptr = Rx;
    clear(Rx, 3, 3);
    clear(Ry, 3, 3);
    clear(Rz, 3, 3);
    clear(R, 3, 3);
    clear(I1, 3, 3);
    fill_vec(res, 3, 0.0f);

    Rx[0][0] = 1;
    Rx[1][1] = Rx[2][2] = cos(angles[0]);
    Rx[1][2] = -sin(angles[0]);
    Rx[2][1] = sin(angles[0]);

    Ry[1][1] = 1;
    Ry[0][0] = Ry[2][2] = cos(angles[1]);
    Ry[0][2] = sin(angles[1]);
    Ry[2][0] = -sin(angles[1]);

    Rz[2][2] = 1;
    Rz[0][0] = Rz[1][1] = cos(angles[2]);
    Rz[0][1] = -sin(angles[2]);
    Rz[1][0] = sin(angles[2]);

    mat_mul(I1, Rx, 3, 3, Ry, 3, 3);
    mat_mul(R, I1, 3, 3, Rz, 3, 3);

    printf("Rx\n");
    for (int i = 0; i < 3; i++, printf("\n"))
        for (int j = 0; j < 3; j++)
            printf("%f ", Rx[i][j]);
    printf("Ry\n");
    for (int i = 0; i < 3; i++, printf("\n"))
        for (int j = 0; j < 3; j++)
            printf("%f ", Ry[i][j]);
    printf("Rz\n");
    for (int i = 0; i < 3; i++, printf("\n"))
        for (int j = 0; j < 3; j++)
            printf("%f ", Rz[i][j]);
    printf("original res : (%f,%f,%f)\n", res[0], res[1], res[2]);
    for (int i = 0; i < 3; i++, printf("\n"))
        for (int j = 0; j < 3; j++)
            printf("%f ", R[i][j]);
    printf("times vec : (%f,%f,%f)\n", vec[0], vec[1], vec[2]);

    mat_vec_mul(res, R, 3, 3, vec, 3);

    printf("equals res : (%f,%f,%f)\n", res[0], res[1], res[2]);
}

// void add(float res[], float a[], float b[])
// {
//     add(res, a, b, 3);
// }

// void sub(float res[], float a[], float b[])
// {
//     sub(res, a, b, 3);
// }

// void normalize(float vec[])
// {
//     normalize(vec, 3);
// }

// void normalize(float res[], float vec[])
// {
//     normalize(res, vec, 3);
// }