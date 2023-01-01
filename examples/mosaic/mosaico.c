
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

void Mosaico (BITMAP bmp, int k);


int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmp;

   if (argc != 4)
   {
      printf ("USO: mosaico <bmp in> <bmp out> "
              "<dimensione tessere (pixel)>\n");
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

   Mosaico (bmp, atoi (argv[3]));

   /* write the file */
   WriteBitmap (bmp, fpout);

   ReleaseBitmapData (&bmp);

   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


void Mosaico (BITMAP bmp, int k)
{
   int row, col, i, j, cnt;
   int rsomma, gsomma, bsomma, rmedia, bmedia, gmedia;

   row = 0;
   col = 0;

   while (row < bmp.height)
   {
      while (col < bmp.width)
      {
         cnt = 0;
         rsomma = gsomma = bsomma = 0;

         for (i = 0; i < k && row + i < bmp.height; i++)
            for (j = 0; j < k && col + j < bmp.width; j++)
            {
               rsomma += PIXEL(bmp, row + i, col + j).red;
               gsomma += PIXEL(bmp, row + i, col + j).green;
               bsomma += PIXEL(bmp, row + i, col + j).blue;
               cnt++;
            }

         rmedia = rsomma / (double) cnt;
         gmedia = gsomma / (double) cnt;
         bmedia = bsomma / (double) cnt;

         for (i = 0; i < k && row + i < bmp.height; i++)
            for (j = 0; j < k && col + j < bmp.width; j++)
            {
               PIXEL(bmp, row + i, col + j).red = rmedia;
               PIXEL(bmp, row + i, col + j).green = gmedia;
               PIXEL(bmp, row + i, col + j).blue = bmedia;
            }

         col += k;
      }
      row += k;
      col = 0;
   }

   return;
}
