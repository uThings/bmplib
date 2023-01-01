
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

#define RPIXEL(image, i, j) PIXEL(image, i, j).red
#define GPIXEL(image, i, j) PIXEL(image, i, j).green
#define BPIXEL(image, i, j) PIXEL(image, i, j).blue


BITMAP chromakey (BITMAP bmpkey, BITMAP bmpbackground, 
                  int redkey, int greenkey, int bluekey, int fuzziness);

int main (int argc, char *argv[])
{
   FILE *fpk, *fpb, *fpout;
   BITMAP bmpk, bmpb, bmpout;
   int kr, kg, kb;
   double fuzziness;
   int i, j;


   if (argc != 8)
   {
      printf ("USO: chromakey <immagine con key> <immagine di sfondo>"
              " <file di output>\n"
              "       <key_color.r> <key_color.g>"
              " <key_color.b> <fuzziness>\n");

      exit (EXIT_FAILURE);
   }

   if ((fpk = fopen (argv[1], "rb")) == NULL)
   {
      printf ("Error opening input file\n");
      exit (EXIT_FAILURE);
   }

   if ((fpb = fopen (argv[2], "rb")) == NULL)
   {
      printf ("Error opening input file\n");
      exit (EXIT_FAILURE);
   }

   if ((fpout = fopen (argv[3], "wb")) == NULL)
   {
      printf ("Error opening output file\n");
      exit (EXIT_FAILURE);
   }

   bmpk = ReadBitmap (fpk);
   bmpb = ReadBitmap (fpb);

   bmpout = chromakey (bmpk, bmpb, atoi (argv[4]), atoi (argv[5]), atoi (argv[6]), atoi (argv[7]));

   WriteBitmap (bmpout, fpout);

   ReleaseBitmapData (&bmpk);
   ReleaseBitmapData (&bmpb);
   ReleaseBitmapData (&bmpout);

   fclose (fpk);
   fclose (fpb);
   fclose (fpout);

   return EXIT_SUCCESS;
}


BITMAP chromakey (BITMAP bmpkey, BITMAP bmpbackground, 
                  int redkey, int greenkey, int bluekey, int fuzziness)
{
   BITMAP bmpout;
   int i, j;

   if (bmpkey.width != bmpbackground.width || bmpkey.height != bmpbackground.height) 
   {
      printf ("Immagini di dimensioni differenti!\n");
      exit (EXIT_FAILURE);
   }

   bmpout = CreateEmptyBitmap (bmpkey.height, bmpkey.width);

   for (i = 0; i < bmpkey.height; i++)
      for (j = 0; j < bmpkey.width; j++)
      {
         if ((RPIXEL(bmpkey, i, j) <= redkey * (1 + fuzziness/100.0)) &&
             (RPIXEL(bmpkey, i, j) >= redkey * (1 - fuzziness/100.0)) &&
             (GPIXEL(bmpkey, i, j) <= greenkey * (1 + fuzziness/100.0)) &&
             (GPIXEL(bmpkey, i, j) >= greenkey * (1 - fuzziness/100.0)) &&
             (BPIXEL(bmpkey, i, j) <= bluekey * (1 + fuzziness/100.0)) &&
             (BPIXEL(bmpkey, i, j) >= bluekey * (1 - fuzziness/100.0)))
         {
            PIXEL(bmpout, i, j) = PIXEL(bmpbackground, i, j);
         }
         else
         {
            PIXEL(bmpout, i, j) = PIXEL(bmpkey, i, j);
         }
      }

   return bmpout;
}

