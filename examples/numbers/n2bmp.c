
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


void load_digits (BITMAP digits[]);
BITMAP compose_number (char s[], BITMAP digits[]);


int main (int argc, char *argv[])
{
   FILE *fpout;
   BITMAP bmp, images[10];
   int i;

   if (argc != 3)
   {
      printf ("USAGE: n2bmp <num> <output file>\n");
      exit (EXIT_FAILURE);
   }

   if ((fpout = fopen (argv[2], "wb")) == NULL)
   {
      printf ("Error opening output file\n");
      exit (EXIT_FAILURE);
   }

   load_digits (images);
   bmp = compose_number (argv[1], images);

   WriteBitmap (bmp, fpout);

   ReleaseBitmapData (&bmp);
   for (i = 0; i < 10; i++)
      ReleaseBitmapData (&images[i]);

   fclose (fpout);

   return EXIT_SUCCESS;
}


void load_digits (BITMAP images[])
{
   FILE *fpin;
   int i, j, k, digit, offset;
   char filename[32];

   for (i = 0; i < 10; i++)
   {   
      sprintf (filename, "%1d.bmp", i);
	  
      if ((fpin = fopen (filename, "rb")) == NULL)
      {
         printf ("Error input file %s\n", filename);
         exit (EXIT_FAILURE);
      }
  
      images[i] = ReadBitmap (fpin);
      fclose (fpin);

      if (i > 0 && (images[i].height != images[0].height || 
	                images[i].width != images[0].width))
      {
         printf ("Wrong digit size (%d)\n", i);
         exit (EXIT_FAILURE);
      }			
   }

   return;
}


BITMAP compose_number (char s[], BITMAP images[])
{
   int i, j, k, slen, digit, offset;
   BITMAP bmp;

   slen = strlen (s);
   bmp = CreateEmptyBitmap (images[0].height, slen * images[0].width);

   offset = 0;
   for (k = 0; k < slen; k++)
   {
      digit = s[k] - '0';

      for (i = 0; i < images[digit].height; i++)
         for (j = 0; j < images[digit].width; j++)
            PIXEL(bmp, i, j + offset) = PIXEL(images[digit], i, j);
	
      offset += images[0].width;
   }
   
   return bmp;
}

