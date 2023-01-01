
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

/*
   steganografia: estrae un file di testo occultato in un file bitmap
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmp.h"


#define SETBIT(data, pos, value) \
           (data) = (((data) & ~(1 << (pos))) | (((value) & 1) << pos))

#define GETBIT(data, pos) \
           (((data) >> (pos)) & 1)


void decode (BITMAP img, FILE *fp);


int main (int argc, char *argv[])
{
   FILE *fpin, *fptxt;
   BITMAP img;


   if (argc != 3)
   {                                                         
      printf ("ARGOMENTI: <file in> <txtfile>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpin = fopen (argv[1], "rb")) == NULL)
   {
      printf ("Error opening input file\n");
      exit (EXIT_FAILURE);
   }

   if ((fptxt = fopen (argv[2], "w")) == NULL)
   {
      printf ("Error opening output file\n");
      exit (EXIT_FAILURE);
   }


   img = ReadBitmap (fpin);
   fclose (fpin);

   decode (img, fptxt);
   fclose (fptxt);

   ReleaseBitmapData (&img);

   return EXIT_SUCCESS;
}



void decode (BITMAP img, FILE *fp)
{
   int k = 0, j;
   char ch;

   /*  while (ci sono bit nel messaggio)  */
   do
   {
      for (j = 0; j < 8; j++)
      {
         /* leggi il bit j di s[i] */
         int bit;

         bit = GETBIT(img.pixel[k].blue, 0);
         SETBIT (ch, j, bit);
         k++;
       }
       if (ch != EOF)
          fputc (ch, fp);

   } while (ch != EOF && k < img.width * img.height);

   return;
}

