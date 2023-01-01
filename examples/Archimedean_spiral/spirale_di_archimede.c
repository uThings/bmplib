
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

#define STEP 0.01
#define FILENAME "spirale.bmp"

BITMAP spirale (int size, double ro);

int main (int argc, char *argv[])
{
   FILE *fpout;
   BITMAP bmpout;

   if (argc != 3)
   {
      printf ("USAGE: spirale <dimensione immagine> <ro>\n");
      exit (EXIT_FAILURE);
   }

   fpout = fopen(FILENAME, "wb");
   bmpout = spirale(atoi(argv[1]), atof(argv[2]));

   WriteBitmap (bmpout, fpout);
   ReleaseBitmapData (&bmpout);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP spirale (int size, double ro)
{
   BITMAP bmp;
   COLORTRIPLE blackpixel = {0, 0, 0};
   COLORTRIPLE whitepixel = {255, 255, 255};
   int x, y;
   double r, theta;

   /* create an empty bitmap data structure */
   bmp = CreateEmptyBitmap (size, size);

   /* creazione sfondo */
   for (x = 0; x < size; x++)
   {
      for (y = 0; y < size; y++)
      {
         PIXEL(bmp, x, y) = whitepixel;
      }
   }

   /* creazione spirale */
   r = 0;
   theta = 0;
   while (r < size/2.0)
   {
      x = size/2 + r*cos(theta);
      y = size/2 + r*sin(theta);
      PIXEL(bmp, x, y) = blackpixel;

      theta += STEP;
      r = ro*theta;
   }

   return bmp;
}
