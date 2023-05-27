#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    if(x<0){
        x=0;
    }
    else if(x>im.w){
        x=im.w-1;
    }
    else if(y<0){
        y=0;
    }
    else if(y>im.h){
        y=im.h-1;
    }
    int p;
    p=x + (y*im.w) + (c*im.w*im.h);
    return im.data[p];

    // TODO Fill this in
    
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if(y<0||y>im.h||x<0||x>im.w||c<0||c>im.c){
        return;
    }
    int m =x + (y*im.w) + (c*im.w*im.h);
    im.data[m]=v;
    // TODO Fill this in
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    int m=im.w*im.h*im.c;
    for(int i=0;i<m;i++){
        copy.data[i]=im.data[i];
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for(int i=0;i<im.w*im.h*1;i++){
        float r = im.data[i];
        float g = im.data[i+im.w*im.h];
        float b = im.data[i+2*im.w*im.h];
        float y = 0.299*r + 0.587*g + 0.114*b;
        gray.data[i]=y;
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for(int i=0;i<(im.w);i++){
        for(int j=0;j<(im.h);j++){
            int k = i+j*im.w+c*im.h*im.w;
            im.data[k]+=v;
        }

    }
}

void clamp_image(image im)
{
    // TODO Fill this in
    for(int i=0;i<(im.w*im.h*im.c);i++){
        if(im.data[i]<0){
            im.data[i]=0;
        }
        else if(im.data[i]>1){
      im.data[i]=1;
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    for(int i=0;i<im.h*im.w;i++){
    // TODO Fill this in
    float r=im.data[i];
    float g=im.data[i+im.h*im.w];
    float b = im.data[i+2*im.h*im.w];
    float v = three_way_max(r,g,b);
    float m = three_way_min(r,g,b);
    float c = v-m;
    float x,y,z;
    if(r==0&&g==0&&b==0)
    x=0;
    
    else
    x=c/v;
    if(c==0){
        z=0;
    }
    else if(v==r)
    z=(g-b)/c;
    else if(v==g)
    z=(g-b)/c+2;
    else if(v==b)
    z=(r-g)/c+4;

    if(z<0)
    y=(z/6)+1;
    else
    y=z/6;
    im.data[i] = y;
    im.data[i+im.h*im.w]=x;
    im.data[i+2*im.h*im.w]=v;
}
}

void hsv_to_rgb(image im)
{
      for(int i=0;i<im.h*im.w;i++)
    {
        float h=im.data[i];
        float s =im.data[i + im.h*im.w];
        float v=im.data[i + 2*im.h*im.w];
        float hueSector, hueFraction, p, q, t, r, g, b;
        hueSector = floor(h * 6);
    hueFraction = (h * 6) - hueSector;
    p = v * (1 - s);
   
    t = v * (1 - (1 - hueFraction) * s);
     q = v * (1 - hueFraction * s);
    
    switch ((int)hueSector) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
        break;
    }
     r=im.data[i];
     g =im.data[i + im.h*im.w];
     b=im.data[i + 2*im.h*im.w];
}
   
}
