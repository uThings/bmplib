
/*****************************************************************

 Copyright 2006   PIER LUCA MONTESSORO

 University of Udine
 ITALY

 montessoro@uniud.it
 www.montessoro.it

 This file is part of a freeware open source software package.
 It can be freely used (as it is or modified) as long as this
 copyright note is not removed.

******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

BITMAP sharpen (BITMAP bmp);
COLORTRIPLE average_square3x3 (BITMAP b, int r, int c);

int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmp, bmp_out;

   if (argc != 3)
   {
      printf ("USO: sharpen <bmp in> <bmp out>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpin = fopen (argv[1], "rb")) == NULL)
   {
      printf ("Error opening input file\n");
      exit (EXIT_FAILURE);
   }

   if ((fpout = fopen (argv[2], "wb")) == NULL)
   {
      printf ("Error opening output file\n");
      exit (EXIT_FAILURE);
   }
 
   bmp = ReadBitmap (fpin);

   bmp_out = sharpen (bmp);

   /* write the file */
   WriteBitmap (bmp_out, fpout);

   ReleaseBitmapData (&bmp);
   ReleaseBitmapData (&bmp_out);

   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP sharpen (BITMAP bmp)
{
   int row, col, v;
   COLORTRIPLE a;
   BITMAP bmp_out;
   
   bmp_out = CreateEmptyBitmap (bmp.height, bmp.width);

   for (row = 0; row < bmp.height; row++)
   {
      for (col = 0; col < bmp.width; col++)
      {
         /* cornice */
         if (row == 0 || row == bmp.height - 1 || col == 0 || col == bmp.width - 1)
         {
            PIXEL (bmp_out, row, col) = PIXEL (bmp, row, col);
         }
         else
         {
            /* interno */
            a = average_square3x3 (bmp, row, col);
            
            v = (2 * PIXEL (bmp, row, col).red) - a.red;
            if (v > 255) PIXEL (bmp_out, row, col).red = 255;
            else if (v < 0) PIXEL (bmp_out, row, col).red = 0;
            else PIXEL (bmp_out, row, col).red = v;

            v = (2 * PIXEL (bmp, row, col).green) - a.green;
            if (v > 255) PIXEL (bmp_out, row, col).green = 255;
            else if (v < 0) PIXEL (bmp_out, row, col).green = 0;
            else PIXEL (bmp_out, row, col).green = v;
            
            v = (2 * PIXEL (bmp, row, col).blue) - a.blue;
            if (v > 255) PIXEL (bmp_out, row, col).blue = 255;
            else if (v < 0) PIXEL (bmp_out, row, col).blue = 0;
            else PIXEL (bmp_out, row, col).blue = v;
         }
      }
   }
      
   return bmp_out;
}

COLORTRIPLE average_square3x3 (BITMAP b, int r, int c)
{
   int i, j, sum_r, sum_g, sum_b;
   COLORTRIPLE a;
   
   sum_r = sum_g = sum_b = 0;
   
   for (i = r-1; i <= r+1; i++)
      for (j = c-1; j <= c+1; j++)
         if (i <= 0 || j <= 0 || i >= b.height || j >= b.width)
         {
            sum_r += PIXEL (b, r, c).red;
            sum_g += PIXEL (b, r, c).green;
            sum_b += PIXEL (b, r, c).blue;
         }
         else
         {
            sum_r += PIXEL (b, i, j).red;
            sum_g += PIXEL (b, i, j).green;
            sum_b += PIXEL (b, i, j).blue;
         }            

   a.red = sum_r / 9.0;
   a.green = sum_g / 9.0;
   a.blue = sum_b / 9.0;

   return a;
}
