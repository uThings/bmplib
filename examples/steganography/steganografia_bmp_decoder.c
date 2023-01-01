
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
   steganografia: estrae un messaggio di testo occultato in un file bitmap
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


void decode (BITMAP b, char s[]);


int main (int argc, char *argv[])
{
   FILE *fpin, *fpout;
   BITMAP bitmap;
   char message[1024];

   if (argc != 2)
   {                                                         
      printf ("USO: steganografia_bmp_decode <file in>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpin = fopen (argv[1], "rb")) == NULL)
   {
      printf ("Error opening input file\n");
      exit (EXIT_FAILURE);
   }

   bitmap = ReadBitmap (fpin);
   fclose (fpin);

   decode (bitmap, message);
   printf ("%s\n", message);

   ReleaseBitmapData (&bitmap);

   return EXIT_SUCCESS;
}


void decode (BITMAP b, char s[])
{
   short int bit;
   int i, j, k, bit_counter, nextcolor;

   k = 0;
   nextcolor = 0;
   bit_counter = 0;

   i = j = 0;

   while (i*j < b.height*b.width)
   {
      switch (nextcolor)
      {
         case 0: bit = GETBIT ((PIXEL(b, i, j).red), 0);
                 nextcolor = 1;
                 break;

         case 1: bit = GETBIT ((PIXEL(b, i, j).green), 0);
                 nextcolor = 2;
                 break;

         case 2: bit = GETBIT ((PIXEL(b, i, j).blue), 0);
                 nextcolor = 0;
                 break;
      }

      SETBIT (s[k], bit_counter, bit);

      bit_counter++;
      bit_counter = bit_counter % 8;

      if (bit_counter == 0)
      {
         if (s[k] == '\0')
            return;
         k++;
         s[k] = 0;
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
               printf ("attenzione: messaggio non terminato\n");
               return;
            }
         }
      }
   }

   return;
}

