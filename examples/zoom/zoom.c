
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

BITMAP zoomX4 (BITMAP bmp);

int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmpin, bmpout;

   if (argc != 3)
   {
      printf ("USAGE: zoom <bmp source file> <bmp destination file>\n");
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

   bmpin = ReadBitmap (fpin);
   bmpout = zoomX4 (bmpin);

   WriteBitmap (bmpout, fpout);

   ReleaseBitmapData (&bmpin);
   ReleaseBitmapData (&bmpout);

   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP zoomX4 (BITMAP bmpin)
{
   int i, j;
   BITMAP bmptmp, bmpout;

   /* create an empty bitmap data structure */
   bmptmp = CreateEmptyBitmap (2 * bmpin.height, 2 * bmpin.width);

   /* copy the pixels */
   for (i = 0; i < bmpin.height; i++)   /* rows */
      for (j = 0; j < bmpin.width; j++)   /* columns */
      {
         PIXEL(bmptmp, 2 * i, 2 * j) =
         PIXEL(bmptmp, 2 * i + 1, 2 * j) =
         PIXEL(bmptmp, 2 * i, 2 * j + 1) =
         PIXEL(bmptmp, 2 * i + 1, 2 * j + 1) = PIXEL(bmpin, i, j);
      }

   /* create an empty bitmap data structure */
   bmpout = CreateEmptyBitmap (bmptmp.height, bmptmp.width);

   /* fill the pixels with average values */
   for (i = 0; i < bmptmp.height - 1; i++)   /* rows */
      for (j = 0; j < bmptmp.width - 1; j++)   /* columns */
      {
         PIXEL(bmpout, i, j).red =
            (PIXEL(bmptmp, i, j).red +
             PIXEL(bmptmp, i + 1, j).red +
             PIXEL(bmptmp, i, j + 1).red +
             PIXEL(bmptmp, i + 1, j + 1).red) / 4.0;

         PIXEL(bmpout, i, j).green =
            (PIXEL(bmptmp, i, j).green +
             PIXEL(bmptmp, i + 1, j).green +
             PIXEL(bmptmp, i, j + 1).green +
             PIXEL(bmptmp, i + 1, j + 1).green) / 4.0;

         PIXEL(bmpout, i, j).blue =
            (PIXEL(bmptmp, i, j).blue +
             PIXEL(bmptmp, i + 1, j).blue +
             PIXEL(bmptmp, i, j + 1).blue +
             PIXEL(bmptmp, i + 1, j + 1).blue) / 4.0;
      }

   /* copy the last row and the last column */
   for (j = 0; j < bmptmp.width; j++)   /* last row */
      PIXEL(bmpout, bmptmp.height - 1, j) =
                      PIXEL(bmptmp, bmptmp.height - 1, j);

   for (i = 0; i < bmpin.height; i++)   /* last column */
      PIXEL(bmpout, i, bmptmp.width - 1) =
                      PIXEL(bmptmp, i, bmptmp.width - 1);

   ReleaseBitmapData (&bmptmp);

   return bmpout;
}
