
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
   steganografia: occulta un file di testo in un file bitmap
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


BITMAP encode (BITMAP img, FILE *fp);


int main (int argc, char *argv[])
{
   FILE *fpin, *fpout, *fptxt;
   BITMAP img;

   if (argc != 4)
   {                                                         
      printf ("ARGOMENTI: <file in> <file out> <textfile>\n");
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

   if ((fptxt = fopen (argv[3], "r")) == NULL)
   {
      printf ("Error opening text file\n");
      exit (EXIT_FAILURE);
   }

   img = ReadBitmap (fpin);
   fclose (fpin);

   encode (img, fptxt);
   fclose (fptxt);

   WriteBitmap (img, fpout);
   fclose (fpout);

   ReleaseBitmapData (&img);

   return EXIT_SUCCESS;
}



BITMAP encode (BITMAP img, FILE *fp)
{
   int k = 0, j;
   char ch;

   /*  while (ci sono bit nel messaggio)  */
   do
   {
      ch = fgetc (fp);

      for (j = 0; j < 8; j++)
      {
         /* scrivi il bit j di s[i] */
         int bit;

         bit = GETBIT(ch, j);
         SETBIT (img.pixel[k].blue, 0, bit);
         k++;
         if (k >= img.width * img.height)
         {
            printf ("spazio terminato\n");
            exit (EXIT_FAILURE);
         }
       }
   } while (ch != EOF);

   return img;
}










