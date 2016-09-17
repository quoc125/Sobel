/*
Quoc Le
September 14, 2016
Cap4453 
*/
#include <stdio.h>                          /* Sobel.c */
#include <math.h>
#include <stdlib.h>
        int pic[256][256];
        int outpicx[256][256];
        int outpicy[256][256];
        int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        double ival[256][256], low[256][256], high[256][256],maxival;

void main(argc,argv)
int argc;
char **argv;
{
  int i,j,p,q,mr,sum1,sum2;
  double threshold;
  FILE *fo1, *fo2, *fo3, *fo4, *fo5, *fp1, *fopen();
  char *foobar;
  char throwaway[80];
  argc--; argv++;
  foobar = *argv;
  fp1=fopen(foobar,"rb");
  fo1 = fopen("sobelX.pgm", "wb");
  fo2 =fopen("sobelY.pgm", "wb");
  fo3 = fopen("sobel.pgm", "wb");
  fo4 = fopen("sobelLow.pgm", "wb");
  fo5 = fopen("sobelHigh.pgm", "wb");
  fgets(throwaway, 80, fp1);
  fgets(throwaway, 80, fp1);
  fgets(throwaway, 80, fp1);
  for (i=0;i<256;i++)
    {
      for (j=0;j<256;j++)
        {
          pic[i][j]  =  getc (fp1);
          pic[i][j]  &= 0377;
       }
   }
   mr = 1;
   for (i=mr;i<256-mr;i++)
    {
      for (j=mr;j<256-mr;j++)
        {
         sum1 = 0;
         sum2 = 0;
         for (p=-mr;p<=mr;p++)
          {
            for (q=-mr;q<=mr;q++)
              {
                 sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
                 sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
              }
          }
          outpicx[i][j] = sum1;
          outpicy[i][j] = sum2;
        }
      }

  maxival = 0;
  for (i=mr;i<256-mr;i++)
  {
     for (j=mr;j<256-mr;j++)
       {
         ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) +
                                  (outpicy[i][j]*outpicy[i][j])));
         if (ival[i][j] > maxival)
            maxival = ival[i][j];
        }
  }
  fprintf(fo1, "P5\n256 256\n255\n");
  fprintf(fo2, "P5\n256 256\n255\n");
  fprintf(fo3, "P5\n256 256\n255\n");
  fprintf(fo4, "P5\n256 256\n255\n");
  fprintf(fo5, "P5\n256 256\n255\n");
  for (i=0;i<256;i++)
    {
     for (j=0;j<256;j++)
        {
         ival[i][j] = (ival[i][j] / maxival) * 255;
         if (100 > ival[i][j])
            high[i][j] = 0;
         else
            high[i][j] = 255;
         if (45 > ival[i][j])
            low[i][j] = 0;
         else
            low[i][j] = 255;

         fprintf(fo1,"%c",(char)((int)(outpicx[i][j])));
         fprintf(fo2,"%c",(char)((int)(outpicy[i][j])));
         fprintf(fo3,"%c",(char)((int)(ival[i][j])));
         fprintf(fo4,"%c",(char)((int)(low[i][j])));
         fprintf(fo5,"%c",(char)((int)(high[i][j])));
          }
      }
}
