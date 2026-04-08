#include "ImageGenApp.h"
#include "setup.h"

int main(int argc , char** argv){
    run_first_time_setup();
    ImageGenApp app(640,550,"Vision Forge");
    app.show(argc,argv);
    return Fl::run();
}