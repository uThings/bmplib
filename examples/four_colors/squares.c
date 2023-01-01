
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

void four_colors (FILE *fp, int size);

int main (int argc, char *argv[])
{
   FILE *fpout;

   if (argc != 3)
   {
      printf ("USAGE: squares <bmp destination file> <size>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpout = fopen (argv[1], "wb")) == NULL)
   {
      printf ("Error opening output file\n");
      exit (EXIT_FAILURE);
   }

   four_colors (fpout, atoi (argv[2]));

   fclose (fpout);

   return EXIT_SUCCESS;
}


void four_colors (FILE *fp, int size)
{
   BITMAP bmpout;
   COLORTRIPLE redpixel = {0, 0, 255};
   COLORTRIPLE greenpixel = {0, 255, 0};
   COLORTRIPLE bluepixel = {255, 0, 0};
   COLORTRIPLE whitepixel = {255, 255, 255};
   int i, j;

   /* create an empty bitmap data structure */
   bmpout = CreateEmptyBitmap (size, size);

   /* color the pixels */
   for (i = 0; i < bmpout.height; i++)   /* rows */
      for (j = 0; j < bmpout.width; j++)   /* columns */
         if (j < size / 2)
            if (i < size / 2)
               PIXEL(bmpout, i, j) = bluepixel;
            else
               PIXEL(bmpout, i, j) = redpixel;
         else
            if (i < size / 2)
               PIXEL(bmpout, i, j) = whitepixel;
            else
               PIXEL(bmpout, i, j) = greenpixel;

   /* write the file */
   WriteBitmap (bmpout, fp);

   ReleaseBitmapData (&bmpout);

   return;
}

