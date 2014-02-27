/*
Author: Farsheed.Ashouri (at, no abuse) gmail.com
Copyright: 2001, 2014
Purpose: To compare two binary files of equal size, and display
differences in BYTES in a helpful matter for further
processing.

The MIT License (MIT)

Copyright (c) <2014> <Farsheed Ashouri>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

void fp_cleanup(FILE** f)
{
int c;
for (c = 0; c < 2; c++)
{
if (f[c] != NULL)
{
fclose(f[c]);
}
}
free(f);
}

void usage()
{
printf("Usage: bcmp file1 file2\n");
}

int main(int argc, char** argv)
{
FILE** file;
long len[2];
unsigned int t[2];
int c;

if (argc < 3)
{
usage();
return 1;
}

file = (FILE**) calloc(2, sizeof(FILE *));

for (c = 0; c < 2; c++)
{
file[c] = fopen(argv[c + 1], "rb");
if (file[c] == NULL)
{
fprintf(stderr, "Unable to open %s.\n", argv[c + 1]);
fp_cleanup(file);
return 1;
}
fseek(file[c], 0, SEEK_END);
len[c] = ftell(file[c]);
fseek(file[c], 0, SEEK_SET);
len[c] -= ftell(file[c]);
}

if (len[0] != len[1])
{
fprintf(stderr, "Error: File lengths are not equal.\n");
fp_cleanup(file);
return 1;
}

for(c = 0; c < len[0]; c++)
{
t[0] = fgetc(file[0]);
t[1] = fgetc(file[1]);

if (t[0] != t[1])
{
fprintf(stdout, "Difference at 0x%04X.\n", c);
fprintf(stdout, "\tfile 1:\t0x%02X\t%03d\n", t[0], t[0]);
fprintf(stdout, "\tfile 2:\t0x%02X\t%03d\n", t[1], t[1]);
fprintf(stdout, "Difference in numbers: %c%d\n", (t[0] > t[1]) ? '-' : '+', abs(t[0] - t[1]));
fprintf(stdout, "\n");
}

}

fp_cleanup(file);

return 0;
}
