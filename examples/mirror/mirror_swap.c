
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

void swap (COLORTRIPLE *pa, COLORTRIPLE *pb);
BITMAP mirror (BITMAP bmp);
                   
int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmp;
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

   bmp = ReadBitmap (fpin);

   mirror (bmp);

   WriteBitmap (bmp, fpout);
   ReleaseBitmapData (&bmp);
   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP mirror (BITMAP bmp)
{
   int row, col_left, col_right;

   for (row = 0; row < bmp.height; row++)
   {
      col_left = 0;
      col_right = bmp.width - 1;
      while (col_left < col_right)
      {
         swap (&(PIXEL(bmp, row, col_left)), &(PIXEL(bmp, row, col_right)));
         col_left++;
         col_right--;
      }
   }

   return;
}


void swap (COLORTRIPLE *pa, COLORTRIPLE *pb)
{
   COLORTRIPLE t;

   t = *pa;
   *pa = *pb;
   *pb = t;

   return;
}

