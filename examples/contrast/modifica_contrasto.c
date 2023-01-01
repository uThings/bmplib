
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

void ModificaContrasto (BITMAP bmp, double k);


int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmp;

   if (argc != 4)
   {
      printf ("USO: modifica_contrasto <bmp in> <bmp out> "
              "<quantita` [%%]>\n");
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

   ModificaContrasto (bmp, atof (argv[3]));

   /* write the file */
   WriteBitmap (bmp, fpout);

   ReleaseBitmapData (&bmp);

   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


void ModificaContrasto (BITMAP bmp, double k)
{
   int row, col;
   COLORTRIPLE white = { 255, 255, 255 };
   COLORTRIPLE black = { 0, 0, 0 };

   k = k / 100.0;

   for (row = 0; row < bmp.height; row++)
   {
      for (col = 0; col < bmp.width; col++)
      {
         if (127 + (PIXEL(bmp, row, col).red - 127) * (1+k) > 255 ||
             127 + (PIXEL(bmp, row, col).green - 127) * (1+k) > 255 ||
             127 + (PIXEL(bmp, row, col).blue - 127) * k > 255)
         {
             PIXEL(bmp, row, col) = white;
         }
         else if (127 + (PIXEL(bmp, row, col).red - 127) * (1+k) < 0 ||
                  127 + (PIXEL(bmp, row, col).green - 127) * (1+k) < 0 ||
                  127 + (PIXEL(bmp, row, col).blue - 127) * k < 0)
         {
             PIXEL(bmp, row, col) = black;
         }
         else
         {
             PIXEL(bmp, row, col).red = 127 + (PIXEL(bmp, row, col).red - 127) * (1+k);
             PIXEL(bmp, row, col).green = 127 + (PIXEL(bmp, row, col).green - 127) * (1+k);
             PIXEL(bmp, row, col).blue = 127 + (PIXEL(bmp, row, col).blue - 127) * (1+k);
         }
      }
   }

   return;
}
