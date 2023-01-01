
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

BITMAP mirror (BITMAP bmp);
                   
int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmpout, bmpin;
   int row, col_left, col_right, average;

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

   bmpout = mirror (bmpin);

   WriteBitmap (bmpout, fpout);
   ReleaseBitmapData (&bmpout);
   ReleaseBitmapData (&bmpin);
   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP mirror (BITMAP bmp)
{
   BITMAP bmpm;
   int row, col;

   bmpm = CreateEmptyBitmap (bmp.height, bmp.width);

   for (row = 0; row < bmp.height; row++)
      for (col = 0; col < bmp.width; col++)
         PIXEL(bmpm, row, col) = PIXEL(bmp, row, bmp.width - col - 1);

   return bmpm;
}

