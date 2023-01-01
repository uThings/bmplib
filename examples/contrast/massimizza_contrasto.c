
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

void MassimizzaContrasto (BITMAP bmp);
int min_del_pixel (COLORTRIPLE p);
int max_del_pixel (COLORTRIPLE p);


int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bmp;

   if (argc != 3)
   {
      printf ("USO: massimizza_contrasto <bmp in> <bmp out>\n");
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

   MassimizzaContrasto (bmp);

   /* write the file */
   WriteBitmap (bmp, fpout);

   ReleaseBitmapData (&bmp);

   fclose (fpin);
   fclose (fpout);

   return EXIT_SUCCESS;
}


void MassimizzaContrasto (BITMAP bmp)
{
   double k;
   int max, min, max_pixel, min_pixel;
   int row, col;

   max = 0;
   min = 255;
   
   for (row = 0; row < bmp.height; row++)
   {
      for (col = 0; col < bmp.width; col++)
      {
         min_pixel = min_del_pixel (PIXEL (bmp, row, col));
         max_pixel = max_del_pixel (PIXEL (bmp, row, col));

         if (max_pixel > max)
            max = max_pixel;
            
         if (min_pixel < min)
            min = min_pixel;
      }
   }
      
   k = 255 / (double) (max - min);            
            
   for (row = 0; row < bmp.height; row++)
   {
      for (col = 0; col < bmp.width; col++)
      {
         PIXEL(bmp, row, col).red = (PIXEL(bmp, row, col).red - min) * k;
         PIXEL(bmp, row, col).green = (PIXEL(bmp, row, col).green - min) * k;
         PIXEL(bmp, row, col).blue = (PIXEL(bmp, row, col).blue - min) * k;
      }
   }
   
   return;
}



int min_del_pixel (COLORTRIPLE p)
{
   int min;

   min = p.red;

   if (p.green < min)
      min = p.green;

   if (p.blue < min)
      min = p.blue;

   return min;
}


int max_del_pixel (COLORTRIPLE p)
{
   int max;

   max = p.red;

   if (p.green > max)
      max = p.green;

   if (p.blue > max)
      max = p.blue;

   return max;
}



