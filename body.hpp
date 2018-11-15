#ifndef _BODY_HPP_
#define _BODY_HPP_

#include "core.hpp"
#include <cmath>

#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1./3)) // cube root

struct colorful : public core {
  unsigned char RD(int i,int j){
    return (char)(_sq(cos(atan2(j-512.,i-512)/2))*255);
  }
  unsigned char GR(int i,int j){
    return (char)(_sq(cos(atan2(j-512.,i-512)/2-2*acos(-1.)/3))*255);
  }
  unsigned char BL(int i,int j){
    return (char)(_sq(cos(atan2(j-512.,i-512)/2+2*acos(-1.)/3))*255);
  }
};
REG(colorful);

struct flat : public core {
  unsigned char RD(int i,int j){
    float s=3./(j+99);
    return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
  }
  unsigned char GR(int i,int j){
    float s=3./(j+99);
    return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
  }
  unsigned char BL(int i,int j){
    float s=3./(j+99);
    return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
  }
};
REG(flat);

struct ripple : public core {
  unsigned char RD(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
  }
  unsigned char GR(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
  }
  unsigned char BL(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
  }
};
REG(ripple);

struct cripple : public core {
  unsigned char RD(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
  }
  unsigned char GR(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int(5*((i+DIM)*s+y))%2+int(5*((DIM*2-i)*s+y))%2)*127;
  }
  unsigned char BL(int i,int j){
    float s=3./(j+99);
    float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
    return (int(29*((i+DIM)*s+y))%2+int(29*((DIM*2-i)*s+y))%2)*127;
  }
};
REG(cripple);

struct randx: public core {
#define r(n)(rand()%n)
  unsigned char RD(int i,int j){
    static char c[1024][1024];return!c[i][j]?c[i][j]=!r(999)?r(256):RD((i+r(2))%1024,(j+r(2))%1024):c[i][j];
  }
  unsigned char GR(int i,int j){
    static char c[1024][1024];return!c[i][j]?c[i][j]=!r(999)?r(256):GR((i+r(2))%1024,(j+r(2))%1024):c[i][j];
  }
  unsigned char BL(int i,int j){
    static char c[1024][1024];return!c[i][j]?c[i][j]=!r(999)?r(256):BL((i+r(2))%1024,(j+r(2))%1024):c[i][j];
  }
};
REG(randx);

struct omg1: public core {
  unsigned char RD(int i,int j){
    float x=0,y=0;int k;for(k=0;k++<256;){float a=x*x-y*y+(i-768.0)/512;y=2*x*y+(j-512.0)/512;x=a;if(x*x+y*y>4)break;}return k>31?256:k*8;
  }
  unsigned char GR(int i,int j){
    float x=0,y=0;int k;for(k=0;k++<256;){float a=x*x-y*y+(i-768.0)/512;y=2*x*y+(j-512.0)/512;x=a;if(x*x+y*y>4)break;}return k>63?256:k*4;
  }
  unsigned char BL(int i,int j){
    float x=0,y=0;int k;for(k=0;k++<256;){float a=x*x-y*y+(i-768.0)/512;y=2*x*y+(j-512.0)/512;x=a;if(x*x+y*y>4)break;}return k;
  }
};
REG(omg1);

struct omg2: public core {
  unsigned char RD(int i,int j){
    double a=0,b=0,c,d,n=0;
    while((c=a*a)+(d=b*b)<4&&n++<880)
    {b=2*a*b+j*8e-9-.645411;a=c-d+i*8e-9+.356888;}
    return 255*pow((n-80)/800,3.);
  }
  unsigned char GR(int i,int j){
    double a=0,b=0,c,d,n=0;
    while((c=a*a)+(d=b*b)<4&&n++<880)
    {b=2*a*b+j*8e-9-.645411;a=c-d+i*8e-9+.356888;}
    return 255*pow((n-80)/800,.7);
  }
  unsigned char BL(int i,int j){
    double a=0,b=0,c,d,n=0;
    while((c=a*a)+(d=b*b)<4&&n++<880)
    {b=2*a*b+j*8e-9-.645411;a=c-d+i*8e-9+.356888;}
    return 255*pow((n-80)/800,.5);
  }
};
REG(omg2);

struct size800 : public core {
  size800() { DIM = 640; }

  unsigned char RD(int i,int j){
    return (unsigned short)sqrt((double)(_sq(i-DIM/2)*_sq(j-DIM/2))*2.0);
  }
  unsigned char GR(int i,int j){
    return (unsigned short)sqrt((double)((_sq(i-DIM/2)|_sq(j-DIM/2))*(_sq(i-DIM/2)&_sq(j-DIM/2))));
  }
  unsigned char BL(int i,int j){
    return (unsigned short)sqrt((double)(_sq(i-DIM/2)&_sq(j-DIM/2))*2.0);
  }
};
REG(size800);

#endif
