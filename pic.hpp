#ifndef _PIC_HPP_
#define _PIC_HPP_

#include <cstdio>
#include <cstring>

class pic {
public:
  pic() {}
  virtual ~pic() {}

  //  ----x--------->
  //  |
  //  y
  //  |
  //  v
  virtual void set(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) = 0;

  bool save(const char * fname) {
    char * new_name = new char[strlen(fname) + strlen(ext) + 2];
    sprintf(new_name, "%s.%s", fname, ext);

    FILE * f = fopen(new_name, "wb");
    delete [] new_name;

    if(f == NULL)
      return false;

    fwrite(p, 1, sz, f);
    fclose(f);
    return true;
  }

protected:
  unsigned char * p;
  unsigned int sz;
  unsigned int w;
  unsigned int h;
  char ext[8];
};

class ppm : public pic {
public:
  ppm(unsigned int width, unsigned int height) {
    w = width & 0xFFF;
    h = height & 0xFFF;

    char hdr[64];
    sprintf(hdr, "P6\n%u %u\n255\n", w, h);

    hdr_offset = strlen(hdr);
    sz = hdr_offset + (w * 3 * h);

    p = new unsigned char[sz];
    memcpy(p, hdr, hdr_offset);
    memset(p + hdr_offset, 0xFF, sz - hdr_offset);

    strcpy(ext, "ppm");
  }

  ~ppm() { delete [] p; }

  void set(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
    if(x < w && y < h) {
      unsigned int offset = hdr_offset + (w * 3 * y) + (x * 3);
      p[offset] = r;
      p[offset + 1] = g;
      p[offset + 2] = b;
    }
  }

private:
  unsigned int hdr_offset;
};

class bmp : public pic {
public:
  bmp(unsigned int width, unsigned int height) {
    w = width & 0xFFF;
    h = height & 0xFFF;
    w3 = (w * 3 + 3) & ~3;
    sz = 54 + (w3 * h);

    p = new unsigned char[sz];
    memset(p, 0, 54);
    memset(p + 54, 0xFF, sz - 54);

    p[0] = 'B';
    p[1] = 'M';
    p[2] = sz;
    p[3] = sz >> 8;
    p[4] = sz >> 16;
    p[5] = sz >> 24;
    p[10] = 54;
    p[14] = 40;
    p[18] = w;
    p[19] = w >> 8;
    p[22] = h;
    p[23] = h >> 8;
    p[26] = 1;
    p[28] = 24;
    p[34] = sz - 54;
    p[35] = (sz - 54) >> 8;
    p[36] = (sz - 54) >> 16;
    p[37] = (sz - 54) >> 24;

    strcpy(ext, "bmp");
  }

  ~bmp() { delete [] p; }

  void set(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
    if(x < w && y < h) {
      unsigned int offset = 54 + w3 * (h - 1 - y) + x * 3;
      p[offset] = b;
      p[offset + 1] = g;
      p[offset + 2] = r;
    }
  }

private:
  unsigned int w3;
};

#endif
