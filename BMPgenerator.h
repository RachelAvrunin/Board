#include <stdio.h>
#include <stdlib.h>
#include  <vector>
#include <string.h>
#include <tgmath.h>
 

typedef int LONG;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;

typedef struct tagBITMAPFILEHEADER{
    WORD    bfType; // 2  /* Magic identifier */
    DWORD   bfSize; // 4  /* File size in bytes */
    WORD    bfReserved1; // 2
    WORD    bfReserved2; // 2
    DWORD   bfOffBits; // 4 /* Offset to image data, bytes */
} __attribute__((packed)) BITMAPFILEHEADER;

 

typedef struct tagBITMAPINFOHEADER{
    DWORD    biSize; // 4 /* Header size in bytes */
    LONG     biWidth; // 4 /* Width of image */
    LONG     biHeight; // 4 /* Height of image */
    WORD     biPlanes; // 2 /* Number of colour planes */
    WORD     biBitCount; // 2 /* Bits per pixel */
    DWORD    biCompress; // 4 /* Compression type */
    DWORD    biSizeImage; // 4 /* Image size in bytes */
    LONG     biXPelsPerMeter; // 4
    LONG     biYPelsPerMeter; // 4 /* Pixels per meter */
    DWORD    biClrUsed; // 4 /* Number of colours */
    DWORD    biClrImportant; // 4 /* Important colours */
} __attribute__((packed)) BITMAPINFOHEADER;

typedef struct{
        BYTE    b;
        BYTE    g;
        BYTE    r;
} RGB_data; // RGB TYPE

 

int bmp_generator(char* filename, int width, int height, unsigned char *data)

{
    BITMAPFILEHEADER bmp_head;
    BITMAPINFOHEADER bmp_info;
    int size = width * height * 3;

    //initialize bmp head
    bmp_head.bfType = 0x4D42; 
    bmp_head.bfSize= size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);   
    bmp_head.bfReserved1 = bmp_head.bfReserved2 = 0;
    bmp_head.bfOffBits = bmp_head.bfSize - size;

    bmp_info.biSize = 40;
    bmp_info.biWidth = width;
    bmp_info.biHeight = height;
    bmp_info.biPlanes = 1;
    bmp_info.biBitCount = 24; // bit(s) per pixel
    bmp_info.biCompress = 0;
    bmp_info.biSizeImage = size;
    bmp_info.biXPelsPerMeter = 0;
    bmp_info.biYPelsPerMeter = 0;
    bmp_info.biClrUsed = 0 ;
    bmp_info.biClrImportant = 0;
    // finish the initial of infohead;

 

    // copy the data
    FILE *fp;

    if (!(fp = fopen(filename,"wb"))) return 0;
    fwrite(&bmp_head, 1, sizeof(BITMAPFILEHEADER), fp);
    fwrite(&bmp_info, 1, sizeof(BITMAPINFOHEADER), fp);
    fwrite(data, 1, size, fp);
    fclose(fp);

    return 1;
}

//Draw an X from center
void drawX(vector<vector<RGB_data>> &buffer, int x, int y){
    
    for(int i=0; i< 10; i++){
        buffer[x-i][y-i].g = 0x00;
        buffer[x-i][y-i].b = 0x00;//0x07;
        buffer[x-i][y-i].r = 0x00;
   
        buffer[x+i][y+i].g = 0x00;
        buffer[x+i][y+i].b = 0x00;//0x07;
        buffer[x+i][y+i].r = 0x00;
    
        buffer[x+i][y-i].g = 0x00;
        buffer[x+i][y-i].b = 0x00;//0x07;
        buffer[x+i][y-i].r = 0x00;
   
        buffer[x-i][y+i].g = 0x00;
        buffer[x-i][y+i].b = 0x00;//0x07;
        buffer[x-i][y+i].r = 0x00;
    }
}

//Draw O from center using bit shifts
void drawO(vector<vector<RGB_data>> &buffer,  int circlePosX, int circlePosY){
    int circleDiameter =30;
    const int FULL = (1 << 2);
    const int HALF = (FULL >> 1);
 
    int size = (circleDiameter << 2);// fixed point value for size
    int ray = (size >> 1);
    int dY2;
    int ray2 = ray * ray;
    int posmin,posmax;
    int Y,X;
    int x = ((circleDiameter&1)==1) ? ray : ray - HALF;
    int y = HALF;

    circlePosX -= (circleDiameter>>1);
    circlePosY -= (circleDiameter>>1);
 
    for (;; y+=FULL){
        dY2 = (ray - y) * (ray - y);
        for (;; x-=FULL){
            if (dY2 + (ray - x) * (ray - x) <= ray2) continue;
            if (x < y){
                Y = (y >> 2);
                posmin = Y;
                posmax = circleDiameter - Y;
                return;
            }

            // Draw the circle
            X = (x >> 2) + 1;
            Y = y >> 2;
            posmax = circleDiameter - X;
            int mirrorY = circleDiameter - Y - 1;
 
            while (X < posmax)
            {
            if(circlePosX+X < 600 && circlePosY+Y < 600 && circlePosY+mirrorY < 600 && 
                circlePosX+Y < 600 && circlePosY+X < 600 && circlePosX+mirrorY < 600 ) 
                {
              //  setPixel(circlePosX+X, circlePosY+Y);
                buffer[circlePosX+X][circlePosY+Y].g = 0x00;
                buffer[circlePosX+X][circlePosY+Y].b = 0x00;//0x07;
                buffer[circlePosX+X][circlePosY+Y].r = 0x00; 

                //setPixel(circlePosX+X, circlePosY+mirrorY);
                buffer[circlePosX+X][circlePosY+mirrorY].g = 0x00;
                buffer[circlePosX+X][circlePosY+mirrorY].b = 0x00;//0x07;
                buffer[circlePosX+X][circlePosY+mirrorY].r = 0x00;

                //setPixel(circlePosX+Y, circlePosY+X);
                buffer[circlePosX+Y][circlePosY+X].g = 0x00;
                buffer[circlePosX+Y][circlePosY+X].b = 0x00;//0x07;
                buffer[circlePosX+Y][circlePosY+X].r = 0x00;

                //setPixel(circlePosX+mirrorY, circlePosY+X);
                buffer[circlePosX+mirrorY][circlePosY+X].g = 0x00;
                buffer[circlePosX+mirrorY][circlePosY+X].b = 0x00;//0x07;
                buffer[circlePosX+mirrorY][circlePosY+X].r = 0x00;
                X++;
                }
            }
            break;
        }
    }
}

void drawDot(vector<vector<RGB_data>> &buffer, int circlePosX, int circlePosY){
    int circleDiameter =5;
    const int FULL = (1 << 2);
    const int HALF = (FULL >> 1);
 
    int size = (circleDiameter << 2);// fixed point value for size
    int ray = (size >> 1);
    int dY2;
    int ray2 = ray * ray;
    int posmin,posmax;
    int Y,X;
    int x = ((circleDiameter&1)==1) ? ray : ray - HALF;
    int y = HALF;

    circlePosX -= (circleDiameter>>1);
    circlePosY -= (circleDiameter>>1);
 
    for (;; y+=FULL){
        dY2 = (ray - y) * (ray - y);
        for (;; x-=FULL){
            if (dY2 + (ray - x) * (ray - x) <= ray2) continue;
            if (x < y){
                Y = (y >> 2);
                posmin = Y;
                posmax = circleDiameter - Y;

                // Draw inside square and break from the loop
                while (Y < posmax){
                    for (X = posmin; X < posmax; X++)
                        if(circlePosX+X < 600 && circlePosY+Y< 600){
                            buffer[circlePosX+X][circlePosY+Y].g = 0x00;
                            buffer[circlePosX+X][circlePosY+Y].b = 0x00;//0x07;
                            buffer[circlePosX+X][circlePosY+Y].r = 0x00; 
                        }
                    Y++;
                }
                return;
            }

 

            // Draw the circle around it
            X = (x >> 2) + 1;
            Y = y >> 2;
            posmax = circleDiameter - X;
            int mirrorY = circleDiameter - Y - 1;

            while (X < posmax){
            if(circlePosX+X < 600 && circlePosY+Y < 600 && circlePosY+mirrorY < 600 && 
                circlePosX+Y < 600 && circlePosY+X < 600 && circlePosX+mirrorY < 600 ) 
                {
              //  setPixel(circlePosX+X, circlePosY+Y);
                buffer[circlePosX+X][circlePosY+Y].g = 0x00;
                buffer[circlePosX+X][circlePosY+Y].b = 0x00;//0x07;
                buffer[circlePosX+X][circlePosY+Y].r = 0x00; 

                //setPixel(circlePosX+X, circlePosY+mirrorY);
                buffer[circlePosX+X][circlePosY+mirrorY].g = 0x00;
                buffer[circlePosX+X][circlePosY+mirrorY].b = 0x00;//0x07;
                buffer[circlePosX+X][circlePosY+mirrorY].r = 0x00;

                //setPixel(circlePosX+Y, circlePosY+X);
                buffer[circlePosX+Y][circlePosY+X].g = 0x00;
                buffer[circlePosX+Y][circlePosY+X].b = 0x00;//0x07;
                buffer[circlePosX+Y][circlePosY+X].r = 0x00;

                //setPixel(circlePosX+mirrorY, circlePosY+X);
                buffer[circlePosX+mirrorY][circlePosY+X].g = 0x00;
                buffer[circlePosX+mirrorY][circlePosY+X].b = 0x00;//0x07;
                buffer[circlePosX+mirrorY][circlePosY+X].r = 0x00;
                X++;
                }
            }
            break;
        }
    }
}