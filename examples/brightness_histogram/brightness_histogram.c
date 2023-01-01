
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

void isto_lum (BITMAP bmp);
int lum_del_pixel (COLORTRIPLE p);
void istogramma_orizzontale (int v[], int dim);
int max_in_vettore (int v[], int dim);


int main (int argc, char *argv[])
{
   FILE *fpin;
   BITMAP bmp;

   if (argc != 2)
   {
      printf ("USO: isto_lum <bmp>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpin = fopen (argv[1], "rb")) == NULL)
   {
      printf ("Error opening input file\n");
      exit (EXIT_FAILURE);
   }

   bmp = ReadBitmap (fpin);
   isto_lum (bmp);
   ReleaseBitmapData (&bmp);
   fclose (fpin);

   return EXIT_SUCCESS;
}


void isto_lum (BITMAP bmp)
{
   int counters [32] = { 0 };
   int i, row, col;
 
   for (row = 0; row < bmp.height; row++)
   {
      for (col = 0; col < bmp.width; col++)
         counters [(int) (lum_del_pixel (PIXEL (bmp, row, col)) / 8)]++;
   }

   istogramma_orizzontale (counters, 32);

   return;
}


int lum_del_pixel (COLORTRIPLE p)
{
   return (int) ((p.red + p.green + p.blue) / 3.0);
}


void istogramma_orizzontale (int v[], int dim)
{
   int i, contatore_asterischi;
   double scala;

   scala = 60.0 / v[max_in_vettore (v, dim)];

   for (i = 0; i < dim; i++)
   {
      /* stampa l'intestazione della riga */
      printf ("%3d - %3d ", 8*i, 8*(i+1)-1);

      /* stampa gli asterischi */
      for (contatore_asterischi = 0; contatore_asterischi < v[i] * scala; contatore_asterischi++)
      {
         printf ("*");
      }

      /* vai a capo */
      printf ("\n");
   }

   return;
}


int max_in_vettore (int v[], int dim)
{
   int i, imax;

   imax = 0;
   i = 1;

   while (i < dim)
   {
      if (v[i] > v[imax])
         imax = i;
      i++;
   }

   return imax;
}

