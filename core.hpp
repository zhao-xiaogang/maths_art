#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>

struct core {
  core():DIM(1024) {}
  virtual ~core() {}

  virtual unsigned char RD(int i, int j) = 0;
  virtual unsigned char GR(int i, int j) = 0;
  virtual unsigned char BL(int i, int j) = 0;

  unsigned int DIM;
};

typedef core * (*CTOR)();

struct name_ctor {
  char name[64];
  CTOR ctor;
};

static name_ctor nc[128];
static unsigned int nc_num = 0;

static int reg_nc(const char * name, CTOR ctor){
  if(strlen(name) >= sizeof(nc[0].name) || nc_num >= sizeof(nc)/sizeof(nc[0])) {
    printf("Error at %s line %d\n", __FILE__, __LINE__);
    exit(1);
  }

  strcpy(nc[nc_num].name, name);
  nc[nc_num].ctor = ctor;
  nc_num++;

  return 0;
}

#define REG(NAME) \
static core * NAME##_ctor_() { return new NAME; } \
static int NAME##_reg_ = reg_nc(#NAME, NAME##_ctor_);

#endif
