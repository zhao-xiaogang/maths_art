/*
http://www.zhihu.com/question/30262900
http://www.matrix67.com/blog/archives/6039
http://codegolf.stackexchange.com/questions/35569/tweetable-mathematical-art
*/

#include "body.hpp"
#include "pic.hpp"

int main(int argc, char * argv[]) {
  if(argc < 2) {
    printf("Usage: %s <-all|name> [bmp|ppm]\n", argv[0]);
    printf("name list:\n");
    for(unsigned int i = 0; i < nc_num; i++) {
      printf("\t%s\n", nc[i].name);
    }
    return 1;
  }

  for(unsigned int i = 0; i < nc_num; i++) {
    if(strcmp(argv[1], nc[i].name)==0 || strcmp(argv[1], "-all")==0) {
      core * c = nc[i].ctor();
      pic * p;

      if(argc > 2 && strcmp(argv[2],"ppm") == 0) {
        p = new ppm(c->DIM, c->DIM);
      } else {
        p = new bmp(c->DIM, c->DIM);
      }

      for(unsigned int y = 0; y < c->DIM; y++)
        for(unsigned int x = 0; x < c->DIM; x++)
          p->set(x, y, c->RD(x,y), c->GR(x,y), c->BL(x,y));

      p->save(nc[i].name);

      delete p;
      delete c;
    }
  }

  return 0;
}
