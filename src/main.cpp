#include "lpsmagic.h"


int main(int argc,char **argv){
    LpsMagic magic(argc,argv);
    
    if(!magic.oneshot)
        return magic.exec();
    else
        return 0;
}