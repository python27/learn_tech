#ifndef GF2_LDPC_INCLUDE
#define GF2_LDPC_INCLUDE

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define INT	6/*8*/              // int part
#define DECI	14/*13*/              // fraction part
#define FMUL	(1<<DECI)       // multiplier
#define PREC	(1.0/FMUL)      // precision
#define LEVELS	(1<<(INT+DECI))
#define fix2float(x) ((x)*PREC)

extern int n, m;
extern int rmax, cmax;
extern int *row_weight, *col_weight;
extern int **row_col;
static unsigned int rndm = 2815UL;

void SRand(int n);
unsigned int Rand(void);
double atanh2(double x);
double logtanh2(double x);


static int flogtanh[LEVELS];
static int fgallag[LEVELS];
int float2fix(double x);
unsigned int float2fixu(double x);
void inittab(void);
int Flogtanh(int x);
int Fgallag(int x);
int HamDist(int *x, int *y, int len);
int bsc(int x[], int y[], double p, int q0[]);
void enc(int y[], int s[]);
vector<bool> inputFile2Binary(const char* filename);
void binary2OutputFile(vector<bool> bvec, const char* filename);
vector<bool> input2Binary(string s);
int **malloc2Dint(int a, int b);
int ***malloc2Dintp(int a, int b);

extern int **qin, ***qin_row;
extern int **LogTanhtin, ***LogTanhtin_row;
extern int **Sgntin, ***Sgntin_row;
extern int *tmp_bit;
extern int *tmp_s;
int dec(int q0[], int s[], int loop_max, int x[]);
void initdec(char *s);
int LDPC_final(int iteration, double prob, char* file);




#endif //GF2_LDPC_INCLUDE