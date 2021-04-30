#include "header/Controller.h"

int main(){
   modelSql* m = new modelSql();
   View* v = new View();
   Controller *c = new Controller(m, v);
   return 0;
}
