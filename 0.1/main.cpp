#include "PlayGround.hpp"


int main(int argc, char * argv[]) {
    
    PlayGround * playground = PlayGround::getPlayGround();
    playground->init(argc, argv);
    
}


