
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

/*
   steganografia: occulta un messaggio di testo in un file bitmap
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


void encode (BITMAP b, char s[]);


int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bitmap;
   char message[1024];

   if (argc != 4)
   {
      printf ("USO: steganografia_bmp_encoder "
              "<file in> <file out> <messaggio>\n");
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

   /* read the bitmap */
   bitmap = ReadBitmap (fpin);
   fclose (fpin);

   encode (bitmap, argv[3]);

   /* write the file */
   WriteBitmap (bitmap, fpout);
   fclose (fpout);

   ReleaseBitmapData (&bitmap);

   return EXIT_SUCCESS;
}


void encode (BITMAP b, char s[])
{
   short int bit;
   int i, j, k, bit_counter, nextcolor;

   if (strlen(s) > b.height * b.width * 3)
   {
      printf ("attenzione: messaggio troppo lungo, verra` troncato\n");
   }

   i = 0;
   j = 0;
   k = 0;
   nextcolor = 0;
   bit_counter = 0;
   while (k <= strlen(s))
   {
      bit = GETBIT (s[k], bit_counter);
      switch (nextcolor)
      {
         case 0: SETBIT ((PIXEL(b, i, j).red), 0, bit);
                 nextcolor = 1;
                 break;

         case 1: SETBIT ((PIXEL(b, i, j).green), 0, bit);
                 nextcolor = 2;
                 break;

         case 2: SETBIT ((PIXEL(b, i, j).blue), 0, bit);
                 nextcolor = 0;
                 break;
      }

      if (nextcolor == 0)
      {
         if (j < b.width-1)
         {
            j++;
         }
         else
         {
            if (i < b.height-1)
            {
               i++;
               j = 0;
            }
            else
            {
               printf ("attenzione: messaggio troppo lungo\n");
               return;
            }
         }
      }

      bit_counter++;
      bit_counter = bit_counter % 8;

      if (bit_counter == 0)
      {
         k++;
      }
   }

   return;
}

