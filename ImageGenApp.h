#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Progress.H>

#include <thread>
#include <chrono>
#include <atomic>
#include <windows.h>

#include "ImageGenApp.h"
#include "SidePanel.h"

class SidePanel;   // forward declaration

class ImageGenApp : public Fl_Double_Window {
public:

    ImageGenApp(int w, int h, const char* title);

    ~ImageGenApp();

    Fl_Input* prompt_input;
    Fl_Button* gen_button;
    Fl_Box* image_box;
    Fl_JPEG_Image* current_image;
    Fl_Button* profeesinal_button;
    SidePanel* side;
    Fl_Progress* progress_bar;
    Fl_Button* reset_button;
    Fl_Button* gallery ; 
    std::atomic<bool> image_ready;
    static void progress_tick_cb(void*);
    static void check_ready_cb(void*);
    void load_generated_image();
    static void reset_cb(Fl_Widget*,void*);

    static void gallery_cb(Fl_Widget*,void*);
    static void generate_cb(Fl_Widget*, void*);
    static void open_side_menu_cb(Fl_Widget*,void*);
};