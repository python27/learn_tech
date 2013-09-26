/******************************************************************************************************
 * GF(2) LDPC encoding/decoding simulator
 * (c) 2005-2006 by Seishi Takamura @ Stanford University / NTT (Nippon Telegraph and Telephone)
 * 
 * Update: Xinfeng Li
 * Date: 2013/06/04
 * License: GPLv2
*********************************************************************************************************/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include "GF2_LDPC.h"

using namespace std;

int n, m;
int rmax, cmax;
int *row_weight, *col_weight;
int **row_col;

//static unsigned int rndm = 2815UL;
void SRand(int n) {
  rndm = n;
}

unsigned int Rand(void)           // simple pseudo rand Î±Ëæ»úÊý
{
  return rndm = (77UL * rndm + 1243UL) & 0x7fffffffUL; // 31bit
}
double atanh2(double x)
{
  return log((1.0 + x) / (1.0 - x));  // returns 2*atanh(x)
}
double logtanh2(double x)
{
  return log(tanh(fabs(x*0.5)));  // returns log tanh |x|
}

#define INT	6/*8*/              // int part
#define DECI	14/*13*/              // fraction part
#define FMUL	(1<<DECI)       // multiplier
#define PREC	(1.0/FMUL)      // precision
#define LEVELS	(1<<(INT+DECI))
//static int flogtanh[LEVELS];
//static int fgallag[LEVELS];

int float2fix(double x)
{
  if (x >= 0) {
    return (int)(x * FMUL + 0.5);
  } else {
    return -(int)((-x) * FMUL + 0.5);
  }
}

unsigned int float2fixu(double x)
{
  return (unsigned int)(x * FMUL + 0.5);
}

#define fix2float(x) ((x)*PREC)

void inittab(void)
{
  int i = 1;
  double right = logtanh2(fix2float(i) - 0.5*PREC);
  flogtanh[0] = -FMUL*14;
  for ( ; i < LEVELS; i++) {
    double d = fix2float(i);
    double left = logtanh2(d+0.5*PREC);
    flogtanh[i] = float2fix((4*logtanh2(d)+right+left) / 6.0);
    right = left;
  }

  i = 1;
  fgallag[0] = FMUL*14;
  right = atanh2(exp(fix2float(-i) - 0.5*PREC));
  for ( ; i < LEVELS; i++) {
    double d = fix2float(-i);
    double expd = atanh2(exp(d));
    double left = atanh2(exp(d+0.5*PREC));
    fgallag[i] = float2fix((4*expd+right+left) / 6.0);
    right = left;
  }
}

#if 1
int Flogtanh(int x)
{
  assert(x>=0);//if (x < 0) return 0;
  if (x >= LEVELS)
    return 0;
  return flogtanh[x];
}
#else
  #define Flogtanh(x) flogtanh[x]
#endif

#if 1
int Fgallag(int x)
{
  assert(x <= 0);//  if (x >= 0) return -FMUL*14; //-115000
  if (x <= -LEVELS)
    return 0;
  return fgallag[-x];
}
#else
  #define Fgallag(x) fgallag[-(x)]
#endif

int HamDist(int *x, int *y, int len)
{
  int i, sum = 0;
  for (i = 0; i < len; i++) {
    if (*x++ != *y++) sum++;
  }
  return sum;
}

int bsc(int x[], int y[], double p, int q0[])
{
  int i, num = 0, modified = 0;
  int *err = (int*)malloc(sizeof(int) * n);
  memset(err, 0, sizeof(int) * n);
  modified = int(n * p + 0.5);
  p = modified / (double)n; // correct error probability
  printf("m/n=%g, ", (double)m/n);
  printf("BSC channel entropy(rate) = %g (bits)\n",
         (-p*log(p)-(1-p)*log(1-p)) / log(2.0));
  while (num < modified) {
    i = Rand() % n;
    if (err[i] == 1) continue;
    err[i] = 1;
    num++;
  }
  for (i = 0; i < n; i++) {
    y[i] = x[i] ^ err[i];
  }
  free(err);

  for (i = 0; i < n; i++) {
    double d = (1 - 2 * y[i]) * log((1.0 - p) / p);
    q0[i] = float2fix(d);
  }
  return modified;
}

void enc(int y[], int s[])
{
  int i, j;
  for (j = 0; j < m; j++) {
    register int k = 0;
    for (i = 0; i < row_weight[j]; i++)
      k ^= y[row_col[j][i]];

    s[j] = k;
  }
}

/*****************************************************
 * Function: inputFile2Binary 
 * Description: given a file named filename, convert the contents of the file
 *                     to binary bit stream.
 * Author: XinFeng Li
 * Date: 2013/06/07
 *****************************************************/
vector<bool> inputFile2Binary(const char* filename)
{
        
        FILE* pfile; 
        pfile = fopen(filename, "rb");
        if (pfile == NULL)
        {
                printf("Cannot open file ! \n");
                exit(1);
        }

        char ch;
        vector<bool> bvec;
        // read char from a file, push every bit to the binary vector.
        while ( (ch = getc(pfile) ) != EOF)
        {
                for (size_t i = 0; i < 8; i++)
                {
                        bvec.push_back( (ch>>i)&1 );
                }
        }
        fclose(pfile);

        return bvec;
}


/******************************************************************
 * Function: binary2OutputFile
 * Description: convert a binary bit stream to a normal file named filename
 * Author: Xinfeng Li
 * Date: 2013/06/07
 *******************************************************************/
void binary2OutputFile(vector<bool> bvec, const char* filename)
{
        
        FILE* pfile = fopen(filename, "w");
        if (pfile == NULL)
        {
                printf("\nCannot open file to write !\n");
                exit(1);
        }
        char ch;
        for (vector<bool>::iterator iter2 = bvec.begin(); iter2 != bvec.end(); iter2 = iter2 + 8)
        {
                int tmp = 0;
                for (int i = 0; i < 8; i++)
                {
                        tmp += static_cast<int>(pow(2.0f, i)) * ( *(iter2 + i) );
                }
                ch = static_cast<char>(tmp);
                fputc(ch, pfile);
        }
        fclose(pfile);
}

/************************************
 * Function: input2Binary
 * Description: convert input string to the binary stream
 * Author: Xinfeng Li
 * Date: 2013/06/06
 ************************************/
vector<bool> input2Binary(string s)
{
	vector<bool> bvec;
	for (size_t i = 0; i < s.size(); i++)
	{
		bitset<8> binary(s[i]);
		// bitset store the binary from low bit to high bit, so need to reverse.
		for (int j = 8 - 1; j >= 0; j--)
		{
			bvec.push_back(binary[j]);
		}
	}

	return bvec;
}


int **malloc2Dint(int a, int b) // allocates array[a][b]
{
  int i;
  int **pp = (int**)malloc(sizeof(int *) * a);
  int *p = (int*)malloc(sizeof(int) * a * b);
  if (pp == NULL || p == NULL) exit(-1);
  for (i = 0; i < a; i++) {
    pp[i] = p + b*i;
  }
  return pp;
}
int ***malloc2Dintp(int a, int b) //
{
  int i;
  int ***pp = (int***)malloc(sizeof(int **) * a);
  int **p = (int**)malloc(sizeof(int*) * a * b);
  if (pp == NULL || p == NULL) exit(-1);
  for (i = 0; i < a; i++) {
    pp[i] = p + b*i;
  }
  return pp;
}

int **qin, ***qin_row;
int **LogTanhtin, ***LogTanhtin_row;
int **Sgntin, ***Sgntin_row;
int *tmp_bit;
int *tmp_s;

int dec(int q0[], int s[], int loop_max, int x[])
{
  int i, j, k, loop;
  int iir, prev = 999999, nodecr = 0;

  memset(*qin, 0, n * cmax * sizeof(int));

  for (loop = 0; loop < loop_max; loop++) {
    for (i = 0; i < n; i++) {
      int sum = q0[i];
      for (j = 0; j < col_weight[i]; j++)
        sum += qin[i][j];
      for (j = 0; j < col_weight[i]; j++) {
        int qout = sum - qin[i][j];
        if (qout < 0) {
          *LogTanhtin_row[i][j] = Flogtanh(-qout);
          *Sgntin_row[i][j] = 1;
        } else {
          *LogTanhtin_row[i][j] = Flogtanh(qout);
          *Sgntin_row[i][j] = 0;
        }
      }
    }

    for (j = 0; j < m; j++) {
      int sgnprod = s[j];
      int logprod = 0;
      for (k = 0; k < row_weight[j]; k++) {
        logprod += LogTanhtin[j][k];
        sgnprod ^= Sgntin[j][k];
      }

      for (k = 0; k < row_weight[j]; k++) {
        int tout = Fgallag(logprod - LogTanhtin[j][k]);
        if (sgnprod != Sgntin[j][k])
          *qin_row[j][k] = -tout;
        else
          *qin_row[j][k] = tout;
      }
    }

    for (i = 0; i < n; i++) {
      int sum = q0[i];
      for (j = 0; j < col_weight[i]; j++) {
        sum += qin[i][j];
      }

      tmp_bit[i] = (sum < 0) ? 1 : 0;
    }
    printf("%2d:HamDist(x)=%d ", loop+1, HamDist(x, tmp_bit, n));

    enc(tmp_bit, tmp_s);
    i = HamDist(s, tmp_s, m);
    printf("HamDist(s,synd(x^))=%d\n", i);
    if (i == 0)           // nothing more can be done
      return 0;

    // nonconvergence detection
    if (loop == 0) iir = i;
    else iir = (int)(iir * 0.85 + i * 0.15 + 0.5);

    if (prev <= i) nodecr++;
    else nodecr = 0;
    if (i > iir * 1.1 || nodecr > 10) break; // no conversion
    prev = i;
  }

  return -1;
}

void initdec(char *s)
{
  int **row_N;
  int **col_row, **col_N;
  int i, j, *count;
  FILE *fp = fopen(s, "rt");
  if (fp == NULL) {
    fprintf(stderr, "cannot open %s\n", s);
    exit(-2);
  }
  fscanf(fp, "%d%d", &n, &m);
  fscanf(fp, "%d%d", &cmax, &rmax);
  col_weight = (int*)malloc(sizeof(int) * n);
  for (i = 0; i < n; i++) {
    fscanf(fp, "%d", &col_weight[i]);
  }
  row_weight = (int*)malloc(sizeof(int) * m);
  for (j = 0; j < m; j++)
    fscanf(fp, "%d", &row_weight[j]);

  {//skip n lines
    for (i = 0; i < n; i++) {
      for (j = 0; j < cmax; j++)
        fscanf(fp, "%*d");
    }
  }

  count = (int*)malloc(sizeof(int) * n);
  memset(count, 0, sizeof(int) * n);
  qin = malloc2Dint(n, cmax);
  qin_row = malloc2Dintp(m, rmax);
  LogTanhtin     = malloc2Dint(m, rmax);
  LogTanhtin_row = malloc2Dintp(n, cmax);
  Sgntin     = malloc2Dint(m, rmax);
  Sgntin_row = malloc2Dintp(n, cmax);
  tmp_bit = (int*)malloc(sizeof(int) * n);
  tmp_s = (int*)malloc(sizeof(int) * m);

  row_col = malloc2Dint(m, rmax);
  row_N   = malloc2Dint(m, rmax);
  col_row = malloc2Dint(n, cmax);
  col_N   = malloc2Dint(n, cmax);
  for (j = 0; j < m; j++) {
    for (i = 0; i < row_weight[j]; i++) {
      int v;
      fscanf(fp, "%d", &v);
      v--;
      row_col[j][i] = v;	// col address
      row_N[j][i] = count[v];	// vertical count of non-zero coef
      col_row[v][count[v]] = j;	// row address
      col_N[v][count[v]] = i;	// horizontal count of non-zero coef
      count[v]++;
      qin_row[j][i] = &qin[row_col[j][i]][row_N[j][i]];
    }
    // following block added on 02/05/2008 according to Mr. David Elkouss' comment
    for ( ; i < rmax; i++) {
      fscanf(fp, "%*d"); // skip the 0s (fillers)
    }
  }
  fclose(fp);

  for (i = 0; i < n; i++) {
    for (j = 0; j < col_weight[i]; j++) {
      LogTanhtin_row[i][j] = &LogTanhtin[col_row[i][j]][col_N[i][j]];
      Sgntin_row[i][j] =     &Sgntin    [col_row[i][j]][col_N[i][j]];
    }
  }

  free(count);
  free(*row_N);
  free( row_N);
  free(*col_row);
  free( col_row);
  free(*col_N);
  free( col_N);
}

/***************************************************
 * Function: LDPC_final
 * Description: given input data, encode, decode.
 * Author: Xinfeng Li
 * Date: 2013/06/06
 ****************************************************/
int LDPC_final(int iteration, double prob, char* file)
{
	int i, *s, *x, *y, *q0;
	inittab();
	initdec(file);
	q0= (int*)malloc(sizeof(int) * n);
	s = (int*)malloc(sizeof(int) * m);  // syndrome
	x = (int*)malloc(sizeof(int) * n);  // source
	y = (int*)malloc(sizeof(int) * n);  // side information
	printf("m = %d\n", m);
	printf("n = %d \n", n);

    // change the text file to be encoded
    string input_string;
    ifstream fin("test.txt", ios_base::in);
    if (fin.is_open())
    {
        fin.seekg(0, fin.end);
        long long length = fin.tellg();
        fin.seekg(0, fin.beg);

        char* buffer = new char[length + 1];
        fin.read(buffer, length);
        buffer[length] = '\0';
        input_string = buffer;

        delete[] buffer;
        // close ifstream
        fin.close();
    }
    else
    {
        cerr << "Cannot Open file:" << "test.txt" << endl;
        exit(1);
    }
    
	
    /*
    //  source message to be encoded. 
    std::cout<<"please enter the message you want to encode(end up with \'#\'):"<<std::endl;
	std::string input_str;
	std::getline(std::cin, input_str, '#');
	std::cout<<"====the message===="<<std::endl;
	std::cout<<input_str<<std::endl;
    */

	// convert source message to binary stream
	vector<bool>  bvec = input2Binary(input_string);
	for (i = 0; i < bvec.size(); i++)
	{
		x[i] = bvec[i];
	}
	for (i = bvec.size(); i < n; i++)
	{
		x[i] = Rand() & 1;
	}
	
	// encoding coverted binary message stream
	enc(x, s);

	for (i = 1; i <= 3; i++) {
		printf("\nBinary LDPC experiment %d:\n", i);
		SRand(i);
		bsc(x, y, prob, q0);
		printf("HamDist(x,y)=%3d \n", HamDist(x,y,n));
		puts(
		  dec(q0, s, iteration, x) ? // sum-product decode (3rd arg: max iteration)
		  "failed." : "converged."
		  );
	}
	return 0;
}

// == debug LDPC BMP comments.
/*
int main()
{
	printf("I am Main function.\n");
	LDPC_final(1000, 0.090, "4986.93xb.329.alist");
	return 0;
}
*/


/*
int main(int argc, char **argv)
{
  int i, *s, *x, *y, *q0;
  int iteration = 1000;

  if (argc == 5 && strcmp(argv[1], "-iter") == 0) {
    iteration = atoi(argv[2]);
    argc -= 2;
    argv += 2;
  }
  if (argc != 3) {
    fprintf(stderr, "GF2_LDPC - binary LDPC simulator\n");
    fprintf(stderr, "usage: GF2_LDPC [-iter num] BSC_crossover_prob ParityMatrix(alist format)\n");
    fprintf(stderr, "e.g.: GF2_LDPC 0.082 20000.10000.3.631.alist\n");
    fprintf(stderr, "e.g.: GF2_LDPC 0.085 4986.93xb.329.alist\n");
    return -1;
  }
  inittab();

  initdec(argv[2]);
  q0= malloc(sizeof(int) * n);
  s = malloc(sizeof(int) * m);  // syndrome
  x = malloc(sizeof(int) * n);  // source
  y = malloc(sizeof(int) * n);  // side information
  for (i = 0; i < n; i++) {
    x[i] = Rand() & 1;
  }
  enc(x, s);

  for (i = 1; i <= 3; i++) {
    printf("\nBinary LDPC experiment %d:\n", i);
    SRand(i);
    bsc(x, y, atof(argv[1]), q0);
    printf("HamDist(x,y)=%3d \n", HamDist(x,y,n));
    puts(
      dec(q0, s, iteration, x) ? // sum-product decode (3rd arg: max iteration)
      "failed." : "converged."
      );
  }

  return 0;
}
*/
