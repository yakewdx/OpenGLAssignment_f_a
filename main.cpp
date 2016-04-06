#ifdef _WIN32
#include "stdafx.h"
#endif
#include "PlayGround.h"


int main(int argc, char * argv[]) {
    
    PlayGround * playground = PlayGround::getPlayGround();
    playground->init(argc, argv);
    
}


