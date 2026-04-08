#include "ImageGenApp.h"
#include "PythonRunner.h"

#include <FL/fl_ask.H>
#include <Fl/Fl_JPEG_Image.H>
#include <Fl/Fl.H>

#include <string>

//Constructor
ImageGenApp::ImageGenApp(int w,int h,const char* title) : Fl_Double_Window(w,h,title){
    
    prompt_input = new Fl_Input(100,20,480,30,"Prompt:");

    gen_button = new Fl_Button(100,60,140,30,"Generate Image");
    gen_button->callback(generate_cb, this);

    profeesinal_button = new Fl_Button(250,60,140,30,"Proffesional");
    profeesinal_button->callback(open_side_menu_cb,this);

    reset_button = new Fl_Button(410,60,47,30,"Reset");
    reset_button->callback(reset_cb,this);

    image_box = new Fl_Box(100,110,400,400,"No image generated yet");
    image_box->box(FL_BORDER_BOX);
    image_box->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);

    gallery = new Fl_Button(590,20,20,30);
    gallery->callback(gallery_cb,this);
    gallery->label("@menu");

    progress_bar = new Fl_Progress(100,520,400,25);
    progress_bar->minimum(0);
    progress_bar->maximum(100);
    progress_bar->value(0);
    progress_bar->label("Generating...");
    progress_bar->color(FL_DARK2,FL_SELECTION_COLOR);
    progress_bar->hide();

    side = new SidePanel(360,420,"Settings");
    side->hide();

    end();
}

ImageGenApp::~ImageGenApp()
{
    delete current_image;
    delete side;
}

void ImageGenApp::open_side_menu_cb(Fl_Widget*,void* data){
    ImageGenApp* app = (ImageGenApp*)data;
    if(!app->side) return ;
    if(app->side->visible()){
        app->side->hide();
    }else{
        app->side->position(
            app->x()+app->w(),
            app->y()
        );
        app->side->show();
    }
    
}

void ImageGenApp::gallery_cb(Fl_Widget*, void*)
{
    ShellExecute(
        NULL,
        "open",
        "output_gallery",
        NULL,
        NULL,
        SW_SHOWNORMAL
    );
}
void ImageGenApp::generate_cb(Fl_Widget*,void* data)
{
    // Recover main application pointer
    ImageGenApp* app = (ImageGenApp*)data;

    // ---- Read prompt ----
    app->image_ready = false;
    app->image_box->image(nullptr);
    std::string prompt = std::string("Main prompt: ") + app->prompt_input->value();

    if (prompt.empty()) {
        fl_alert("Please enter a prompt!");
        return;
    }

    // ---- UI feedback ----
    app->progress_bar->value(0);
    app->progress_bar->show();
    app->gen_button->deactivate();
    app->image_box->label("Generating... please wait...");
    Fl::redraw();

    // ---- Read settings from SidePanel ----
    if(app->side)
        prompt += std::string("Detials about the prompt-> ")+  app->side->build_prompt();

    // fl_message("%s", prompt.c_str()); // turn it on when you need to debug what type of prompt is input internally
    
    Fl::add_timeout(0.04, progress_tick_cb, app);
    //run in backround 
    std::thread([app,prompt]()
    {
        std::string command =
        "python\\python.exe generate_image.py \"" +
        prompt + "\" ";
        // ---- Run backend process ----
        run_python_hidden(command);
        app->image_ready = true ;
    }).detach();
    Fl::add_timeout(0.1, check_ready_cb, app);    

            
    
}

void ImageGenApp::check_ready_cb(void* data)//this checks if the status is ready 
{
    ImageGenApp* app = (ImageGenApp*)data;
    if(app->image_ready)
    {
        app->load_generated_image();
        return ;
    }
    Fl::repeat_timeout(0.1,check_ready_cb,data);

}
void ImageGenApp::progress_tick_cb(void* data)//this animate the progress bar
{
    ImageGenApp* app = (ImageGenApp*)data;

    if(app->image_ready)
        return;

    double v = app->progress_bar->value();
    if(v < 75)
    v += 0.5;
    else
        v += 0.1;   // slow near finish
    if(v>=95) v+=0.000001 ;
    if(v >= 100)
        v = 98; 
    app->progress_bar->value(v);

    Fl::repeat_timeout(0.1, progress_tick_cb, data);
}

void ImageGenApp::load_generated_image()
{
    Fl_JPEG_Image* img = new Fl_JPEG_Image("currently_generated.jpg");
    if (!img || img->fail()) {
                fl_alert("Failed to load generated image!");
                delete img;
                gen_button->activate();
                return;
            }

    
    img->scale(image_box->w(), image_box->h(), 1, 1);

    // ---- Show image ----
    image_box->image(img);
    image_box->label(nullptr);

    // ---- Re-enable UI ----
    progress_bar->hide();
    gen_button->activate();
    redraw();
}


void ImageGenApp::reset_cb(Fl_Widget* w,void* data)
{
    ImageGenApp* app = (ImageGenApp*)data;
    app->image_box->image(nullptr);
    app->prompt_input->value("");
    app->image_box->label("No image generated yet");
    app->image_box->redraw();
    app->side->reset_panel();
    app->progress_bar->hide();
}