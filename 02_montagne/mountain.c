/* La montagne mémoire: débit de lecture (Mo/s) en fonction de la taille du
 * jeu de données et du pas d'accès. D'après Bryant et O'Hallaron, Computer
 * Systems: A Programmer's Perspective, chapitre 6.
 *
 * Sortie: CSV sur stdout, colonnes size_bytes, stride, mbps.
 * Compiler avec -O2: ni plus (le compilateur vectoriserait et masquerait
 * la mémoire), ni moins (la boucle elle-même serait le goulot). */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINBYTES (1 << 13)          /* 8 Ko */
#define MAXBYTES (1 << 25)          /* 256 Mo */
#define MAXELEMS (MAXBYTES / sizeof(long))
#define MINREAD  (256L << 20)       /* lire au moins 256 Mo par mesure */
#define TRIALS   3                  /* on garde le meilleur essai */

static long data[MAXELEMS];

/* Lit elems éléments avec un pas de stride, en quatre accumulateurs
 * indépendants pour ne pas être limité par la latence de l'addition.
 * Le résultat est renvoyé pour que le compilateur ne supprime pas la boucle. */
static long test(long elems, long stride)
{
    long acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    long limit = elems - 4 * stride;
    long i;
    for (i = 0; i < limit; i += 4 * stride) {
        acc0 += data[i];
        acc1 += data[i + stride];
        acc2 += data[i + 2 * stride];
        acc3 += data[i + 3 * stride];
    }
    for (; i < elems; i += stride)
        acc0 += data[i];
    return acc0 + acc1 + acc2 + acc3;
}

static double now(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

static volatile long sink;

/* Débit en Mo/s pour un jeu de données de size octets lu avec un pas stride. */
static double run(long size, long stride)
{
    long elems = size / sizeof(long);
    long bytes_per_pass = (elems / stride) * sizeof(long);
    long passes = MINREAD / bytes_per_pass;
    if (passes < 1) passes = 1;
    double best = 1e30;
    sink = test(elems, stride);             /* échauffement: remplit les caches */
    for (int t = 0; t < TRIALS; t++) {
        double t0 = now();
        for (long p = 0; p < passes; p++)
            sink += test(elems, stride);
        double dt = now() - t0;
        if (dt < best) best = dt;
    }
    return (double)bytes_per_pass * passes / best / 1e6;
}

int main(void)
{
    static const int strides[] = {1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64};
    for (long i = 0; i < (long)MAXELEMS; i++) data[i] = i;   /* pages réellement allouées */
    printf("size_bytes,stride,mbps\n");
    for (long size = MAXBYTES; size >= MINBYTES; size /= 2) {
        for (size_t s = 0; s < sizeof strides / sizeof *strides; s++) {
            double mbps = run(size, strides[s]);
            printf("%ld,%d,%.0f\n", size, strides[s], mbps);
            fflush(stdout);
        }
        fprintf(stderr, "%ld Ko\n", size / 1024);
    }
    return 0;
}
