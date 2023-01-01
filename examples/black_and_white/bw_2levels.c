
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

BITMAP black_and_white_2_levels (BITMAP bmpcolor);

int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmpin, bmpout;

   if (argc != 3)
   {
      printf ("USAGE: bw <input file> <output file>\n");
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
   bmpout = black_and_white_2_levels (bmpin);

   WriteBitmap (bmpout, fpout);
   ReleaseBitmapData (&bmpin);
   ReleaseBitmapData (&bmpout);
   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP black_and_white_2_levels (BITMAP bmpcolor)
{
   BITMAP bmpbw;
   int i, j, average;
   COLORTRIPLE black = { 0, 0, 0 };
   COLORTRIPLE white = { 255, 255, 255 };


   bmpbw = CreateEmptyBitmap (bmpcolor.height, bmpcolor.width);

   for (i = 0; i < bmpcolor.height; i++)
      for (j = 0; j < bmpcolor.width; j++)
      {
         average = (PIXEL(bmpcolor, i, j).red +
                   PIXEL(bmpcolor, i, j).green +
                   PIXEL(bmpcolor, i, j).blue) / 3.0;
         if (average > 127)
            PIXEL(bmpbw, i, j) = white;
         else
            PIXEL(bmpbw, i, j) = black;
      }

   return bmpbw;
}
