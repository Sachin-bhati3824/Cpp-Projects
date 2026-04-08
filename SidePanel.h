#pragma once 
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Dial.H>
#include <FL/Enumerations.H>
#include <FL/Fl_box.H>
#include <string>

class SidePanel : public Fl_Double_Window {
public:
    
    Fl_Choice* choice_tab = NULL ;
    Fl_Choice* light_menu = NULL ;
    Fl_Choice* POV_menu = NULL ;

    //all the dials 
    Fl_Dial* Imagination_dial ;
    Fl_Dial* Prompt_strength_dial;
    Fl_Dial* Detail_level_dial;
    Fl_Dial* Weirdness_dial ;

    //all the boxes of the dials 
    Fl_Box *Prompt_strength_output;
    Fl_Box *Detail_level_output;
    Fl_Box *Imagination_output;
    Fl_Box *Weirdness_output ;

    double prompt_strength_value;
    double detail_value;
    double imagination_value;
    double weirdness_value;

    int composition_choice;
    int lighting_choice;
    int pov_choice;

    static void Prompt_strength_dial_cb(Fl_Widget*,void*);
    static void Detail_level_dial_cb(Fl_Widget*,void*);
    static void Imagination_dial_cb(Fl_Widget*,void*);
    static void Weirdness_cb(Fl_Widget*,void*);

    void update_text(double value, int dial );
    std::string build_prompt();
    std::string dial_prompt_text(double,int);
    void update_color(int,int);
    int dial_level(double);
    void reset_panel();

    SidePanel(int w ,int h, const char* title);

    
};