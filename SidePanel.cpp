#include "Sidepanel.h"
#include <cstdlib>

SidePanel::SidePanel(int w,int h,const char *title):Fl_Double_Window(w,h,title)
{
    choice_tab = new Fl_Choice(150,20,200,25,"Compostion Techniques");
    choice_tab->add("None");
    choice_tab->add("Rule of Thirds");
    choice_tab->add("Centered Compostion");
    choice_tab->add("Frame within the Frame");
    choice_tab->add("Leading Lines");
    choice_tab->add("Patterns and Textrues");
    choice_tab->add("Break the Pattern");
    choice_tab->add("Rule of Odds");
    choice_tab->add("Fill the Frame");
    choice_tab->add("Leave Negative Space");
    choice_tab->add("Minimalism");
    choice_tab->add("use Black and white");
    choice_tab->add("Shoot from below");
    choice_tab->add("Shoot from Above");
    choice_tab->add("Rule of Space");
    choice_tab->add("Left to Right rule");
    choice_tab->add("Juxtaposition");
    choice_tab->add("Golden Triangles");
    choice_tab->add("Golden Ratio");
    choice_tab->add("Add Human Interest");
    choice_tab->value(0);
    choice_tab->box(FL_UP_BOX);      
    choice_tab->down_box(FL_BORDER_BOX); 


    light_menu = new Fl_Choice(150,50,200,25,"Light Modes");
    light_menu->add("None");
    light_menu->add("Flat Light");
    light_menu->add("Broad Light");
    light_menu->add("Short Light");
    light_menu->add("Split Light");
    light_menu->add("Backlight");
    light_menu->value(0);

    POV_menu = new Fl_Choice(150,80,200,25,"Point of Visualization");
    POV_menu->add("None");
    POV_menu->add("Bird Eye View");
    POV_menu->add("Becoming the Subject");
    POV_menu->add("Eye Level");
    POV_menu->add("Dutch Angle");
    POV_menu->add("Close up");
    POV_menu->add("Long Angle");
    POV_menu->add("High Angle");
    POV_menu->add("Worm's Eye View");
    POV_menu->value(0);
    
    
    Prompt_strength_dial = new Fl_Dial(30,110,120,100,"Follow the prompt");
    Prompt_strength_dial->type(FL_FILL_DIAL);
    Prompt_strength_dial->color(FL_DARK2,FL_SELECTION_COLOR);
    Prompt_strength_dial->angles(0,360);
    Prompt_strength_dial->range(0,100);
    Prompt_strength_dial->value(0);
    Prompt_strength_dial->when(FL_WHEN_CHANGED);
    Prompt_strength_dial->callback(Prompt_strength_dial_cb,this);

    Prompt_strength_output = new Fl_Box(30,220,120,25,"Chaos Mode");
    Prompt_strength_output->labelsize(14);
    Prompt_strength_output->labelfont(FL_BOLD);
    Prompt_strength_output->align(FL_ALIGN_CENTER);

    Detail_level_dial = new Fl_Dial(210,110,120,100,"Level of detailing");
    Detail_level_dial->type(FL_FILL_DIAL);
    Detail_level_dial->color(FL_DARK2,FL_SELECTION_COLOR);
    Detail_level_dial->angles(0,360);
    Detail_level_dial->range(0,100);
    Detail_level_dial->value(0);
    Detail_level_dial->when(FL_WHEN_CHANGED);
    Detail_level_dial->callback(Detail_level_dial_cb,this);
    
    Detail_level_output = new Fl_Box(210,220,120,25,"Rough Sketch");
    Detail_level_output->labelsize(14);
    Detail_level_output->labelfont(FL_BOLD);
    Detail_level_output->align(FL_ALIGN_CENTER);

    Imagination_dial = new Fl_Dial(30,275,120,100,"Imagination meter");
    Imagination_dial->type(FL_LINE_DIAL);
    Imagination_dial->color(FL_DARK2,FL_SELECTION_COLOR);
    Imagination_dial->angles(0,360);
    Imagination_dial->range(0,100);
    Imagination_dial->value(0);
    Imagination_dial->when(FL_WHEN_CHANGED);
    Imagination_dial->callback(Imagination_dial_cb,this);

    Imagination_output = new Fl_Box(30,385,120,25,"Reality");
    Imagination_output->labelsize(14);
    Imagination_output->labelfont(FL_BOLD);
    Imagination_output->align(FL_ALIGN_CENTER);

    Weirdness_dial = new Fl_Dial(210,275,120,100,"Weirdness meter");
    Weirdness_dial->type(FL_LINE_DIAL);
    Weirdness_dial->color(FL_DARK2,FL_SELECTION_COLOR);
    Weirdness_dial->angles(0,360);
    Weirdness_dial->range(0,100);
    Weirdness_dial->value(0);
    Weirdness_dial->when(FL_WHEN_CHANGED);
    Weirdness_dial->callback(Weirdness_cb,this);

    Weirdness_output = new Fl_Box(210,385,120,25,"Normal");
    Weirdness_output->labelsize(14);
    Weirdness_output->labelfont(FL_BOLD);
    Weirdness_output->align(FL_ALIGN_CENTER);

    end();
}



void SidePanel::Prompt_strength_dial_cb(Fl_Widget* w,void*data)
{
    SidePanel* panel = (SidePanel*)data;
    panel->prompt_strength_value = ((Fl_Dial*)w)->value();
    panel->update_text(panel->prompt_strength_value,0);
    panel->update_color(0,panel->prompt_strength_value);
}

int SidePanel::dial_level(double value)
{
    if(value < 20) return 0;
    if(value < 40) return 1;
    if(value < 60) return 2;
    if(value < 80) return 3;
    return 4;
}

void SidePanel::update_color(int pos,int val)
{
    int value = dial_level((double)val);

    Fl_Color calm    = fl_rgb_color(120,140,170);
    Fl_Color blue    = fl_rgb_color(80,160,255);
    Fl_Color green   = fl_rgb_color(60,200,140);
    Fl_Color orange  = fl_rgb_color(255,140,40);   // ← your request
    Fl_Color extreme = fl_rgb_color(255,60,160);
    Fl_Color colors[5] = {
        calm,
        blue,
        green,
        orange,
        extreme
    };
    Fl_Box* target = nullptr ; 

    switch(pos) {
        case 0: target = Prompt_strength_output; break;
        case 1: target = Detail_level_output; break;
        case 2: target = Imagination_output; break;
        case 3: target = Weirdness_output; break;
    }

    if(target){
        target->labelcolor(colors[value]);
        target->redraw();
    }

}

void SidePanel::Detail_level_dial_cb(Fl_Widget* w,void* data)
{
    SidePanel* panel = (SidePanel*)data; 
    panel->detail_value = ((Fl_Dial*)w)->value();
    panel->update_text(panel->detail_value,1);
    panel->update_color(1,panel->detail_value);
}

void SidePanel::Imagination_dial_cb(Fl_Widget* w,void*data)
{
    SidePanel* panel = (SidePanel*)data;
    panel->imagination_value = ((Fl_Dial*)w)->value();
    panel->update_text(panel->imagination_value,2);
    panel->update_color(2,panel->imagination_value);
}

void SidePanel::Weirdness_cb(Fl_Widget* w,void*data)
{
    SidePanel* panel = (SidePanel*)data;
    panel->weirdness_value = ((Fl_Dial*)w)->value();
    panel->update_text(panel->weirdness_value,3);
    panel->update_color(3,panel->weirdness_value);
}

void SidePanel::update_text(double value,int dial)
{
    const char* text ;
    const char* dial_number[4] = {"Prompt_strength_dial","Detail_level_dial","Imagination_dial","Weirdness_dial"};//just for reference 
    const char* valueB20[4] = {"Chaos Mode","Rough Sketch","Reality","Normal"};
    const char* valueB40[4] = {"Creative Guess","Painterly","Stylized","Slightly Weird"};
    const char* valueB60[4] = {"Co-Creator","Studio quality","Fantasy","Creative"};
    const char* valueB80[4] = {"Director's cut","Ultra Detailed","Dreamscape","Surreal"};
    const char* valueA80[4] = {"God Mode Prompt","Unreal Precision","Cosmic Vision","Pure Dream"};

    if (value<20) text = valueB20[dial];
    else if (value < 40) text = valueB40[dial];
    else if (value < 60) text = valueB60[dial];
    else if (value < 80) text = valueB80[dial];
    else text = valueA80[dial] ; 

    switch(dial) {
        case 0:
            Prompt_strength_output->label(text);
            Prompt_strength_output->redraw();
            break;
        case 1:
            Detail_level_output->label(text);
            Detail_level_output->redraw();
            break;
        case 2:
            Imagination_output->label(text);
            Imagination_output->redraw();
            break;
        case 3:
            Weirdness_output->label(text);
            Weirdness_output->redraw();
            break;     
    }
    
}


std::string SidePanel::build_prompt()
{
    std::string prompt;

    if(const Fl_Menu_Item* item = choice_tab->mvalue())
        if(strcmp(item->label(),"None")!=0)
            prompt+= "Follow this photography rule: " + std::string(item->label())+",";
    

    if(const Fl_Menu_Item* item = light_menu->mvalue())
        if(strcmp(item->label(),"None")!=0)
            prompt+= "Keep this light settings in the image: "+ std::string(item->label())+",";

    if(const Fl_Menu_Item* item = POV_menu->mvalue())
        if(strcmp(item->label(),"None") != 0)
            prompt += "Set this point of visualization: " + std::string(item->label()) + ", ";


    double prompt_strength = Prompt_strength_dial->value();
    double detail          = Detail_level_dial->value();
    double imagination     = Imagination_dial->value();
    double weirdness       = Weirdness_dial->value();

    prompt += dial_prompt_text(prompt_strength,0);
    prompt += dial_prompt_text(detail,1);
    prompt += dial_prompt_text(imagination,2);
    prompt += dial_prompt_text(weirdness,3);

    return prompt;
}




std::string SidePanel::dial_prompt_text(double value,int dial)
{
    std::string text;

    /* ===============================
       PROMPT STRENGTH
    ===============================*/
    if(dial==0)
    {
        if(value<20)
            text = "loose interpretation, abstract freedom, artistic liberty, experimental composition, ";
        else if(value<40)
            text = "creative interpretation, inspired by prompt, stylistic variation, ";
        else if(value<60)
            text = "balanced prompt adherence, coherent composition, refined structure, ";
        else if(value<80)
            text = "strong prompt adherence, accurate subject rendering, controlled generation, ";
        else
            text = "perfect prompt alignment, highly controlled generation, cinematic precision, master composition, ";
    }

    /* ===============================
       DETAIL LEVEL
    ===============================*/
    else if(dial==1)
    {
        if(value<20)
            text = "rough sketch, minimal detail, soft forms, painterly strokes, ";
        else if(value<40)
            text = "illustrative detail, artistic rendering, textured surfaces, ";
        else if(value<60)
            text = "highly detailed, sharp focus, refined textures, realistic shading, ";
        else if(value<80)
            text = "ultra detailed, intricate textures, cinematic lighting, professional rendering, ";
        else
            text = "hyperrealistic, 8k resolution, microscopic detail, studio quality render, masterpiece quality, ";
    }

    /* ===============================
       IMAGINATION
    ===============================*/
    else if(dial==2)
    {
        if(value<20)
            text = "real world physics, natural realism, believable environment, ";
        else if(value<40)
            text = "stylized realism, artistic interpretation, enhanced reality, ";
        else if(value<60)
            text = "fantasy elements, imaginative atmosphere, creative worldbuilding, ";
        else if(value<80)
            text = "dreamlike environment, surreal storytelling, cinematic fantasy visuals, ";
        else
            text = "cosmic imagination, impossible geometry, surreal dream universe, visionary art, ";
    }

    /* ===============================
       WEIRDNESS
    ===============================*/
    else if(dial==3)
    {
        if(value<20)
            text = "natural composition, grounded aesthetics, realistic proportions, ";
        else if(value<40)
            text = "subtle surreal touch, unusual framing, artistic abstraction, ";
        else if(value<60)
            text = "creative distortion, surreal elements, unexpected visuals, ";
        else if(value<80)
            text = "high surrealism, dream logic visuals, unconventional perspective, ";
        else
            text = "psychedelic surrealism, bizarre dreamscape, reality bending visuals, avant-garde art style, ";
    }

    return text;
}
void SidePanel::reset_panel()
{
    choice_tab->value(0);
    light_menu->value(0);
    POV_menu->value(0);
    Prompt_strength_dial->value(0);
    Detail_level_dial->value(0);
    Imagination_dial->value(0);
    Weirdness_dial->value(0); 
    Prompt_strength_dial->do_callback();
    Detail_level_dial->do_callback();
    Imagination_dial->do_callback();
    Weirdness_dial->do_callback();
    
    redraw();
}