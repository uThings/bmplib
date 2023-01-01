
/*****************************************************************

 Copyright 2001   PIER LUCA MONTESSORO

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

BITMAP square (int size);

int main (int argc, char *argv[])
{
   FILE *fpout;
   BITMAP bmpout;

   if (argc != 3)
   {
      printf ("USAGE: square <bmp destination file> <size>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpout = fopen (argv[1], "wb")) == NULL)
   {
      printf ("Error opening output file\n");
      exit (EXIT_FAILURE);
   }

   bmpout = square (atoi(argv[2]));

   WriteBitmap (bmpout, fpout);
   ReleaseBitmapData (&bmpout);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP square (int size)
{
   BITMAP bmp;
   COLORTRIPLE blackpixel = {0, 0, 0};
   COLORTRIPLE whitepixel = {255, 255, 255};
   int i, j, hsize;

   /* create an empty bitmap data structure */
   bmp = CreateEmptyBitmap (size, size);

   /* color the pixels */
   hsize = size / 2;
   for (i = 0; i < hsize; i++)   /* rows */
      for (j = 0; j < hsize; j++)   /* columns */
         if (i + j < hsize)
         {
            PIXEL(bmp, i, j) = whitepixel;
            PIXEL(bmp, i, size - j - 1) = whitepixel;
            PIXEL(bmp, size - i - 1, j) = whitepixel;
            PIXEL(bmp, size - i - 1, size - j - 1) = whitepixel;
         }
         else
         {
            PIXEL(bmp, i, j) = blackpixel;
            PIXEL(bmp, i, size - j - 1) = blackpixel;
            PIXEL(bmp, size - i - 1, j) = blackpixel;
            PIXEL(bmp, size - i - 1, size - j - 1) = blackpixel;
         }

   return bmp;
}

