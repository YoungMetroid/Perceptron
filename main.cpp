#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


#include "perceptron.h"
#include "mouselistener.h"

using namespace std;

const int width = 500;
const int height = 500;
const int FPS = 60;

int main()
{
    float f = 0.03;
    float g = 0.02;
    g+=f;
    std::cout << "f: " << f << std::endl;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *eventqueue = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_FONT * font_mana;


    bool gameLoop = false;
    bool redraw = false;
    bool calculate = false;

    if(!al_init())
    {return -1;}


    display = al_create_display(width,height);
    if(!display)
       { return -1;}


    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_COLOR background = al_map_rgb(243,238,217);
    ALLEGRO_COLOR blue = al_map_rgb(78,60,220);
    ALLEGRO_COLOR red = al_map_rgb(240,40,40);
    font_mana  = al_load_ttf_font("manaspc.ttf",15,0);

    int weights = 2;
    std::vector<double> new_Weights;
    std::vector<int> new_Y;
    perceptron *pCeptron = new perceptron(weights);
    mouseListener *mouseL = new mouseListener();

    al_clear_to_color(background);


    al_draw_line(width/2,0,width/2,height,al_map_rgb(50,10,10),3);
    al_draw_line(0,height/2,width,height/2,al_map_rgb(50,10,10),3);


    al_draw_text(font_mana,blue,width/2,height/2,1,"0");
    al_flip_display();


    eventqueue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    al_register_event_source(eventqueue,al_get_keyboard_event_source());
    al_register_event_source(eventqueue,al_get_timer_event_source(timer));
    al_register_event_source(eventqueue,al_get_display_event_source(display));
    al_register_event_source(eventqueue,al_get_mouse_event_source());

    al_start_timer(timer);
    while(!gameLoop)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventqueue,&event);

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            gameLoop = true;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_P:
                if(mouseL->getClassesSize()[0] > 0 and mouseL->getClassesSize()[1] > 0)
                {
                    if(!calculate)
                    {
                        std::cout << "In" << std::endl;
                        std::cout << mouseL->getObject().size() << std::endl;
                        pCeptron->setPoints(mouseL->getObject());

                        /*new_Weights = pCeptron->calculate();



                            int y1 = 0;
                            for(int i = 0; i < new_Weights.size();i++)
                            {

                                std::cout << "Weight: " << i << " : " << new_Weights[i] << std::endl;
                            }
                            y1= -(new_Weights[2]/new_Weights[1])-(new_Weights[0]/new_Weights[1]) * -250;
                            std::cout << "Y1: " << y1 << std::endl;
                            //

                            new_Y.push_back(y1);
                            int y2 = -(new_Weights[2]/new_Weights[1])-(new_Weights[0]/new_Weights[1]) * 250;
                            std::cout << "Y2: " << y2 << std::endl;
                            new_Y.push_back(y2);
                        */

                        calculate = !calculate;
                    }
                }
                break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(!calculate)
            if(event.mouse.button & 2)
            {
                mouseL->addObject(event.mouse.x,event.mouse.y,0);
                mouseL->print();
            }
            else if(event.mouse.button & 1)
            {
                mouseL->addObject(event.mouse.x,event.mouse.y,1);
                mouseL->print();
            }
        }
        if(redraw == true and al_is_event_queue_empty(eventqueue))
        {
            redraw = false;
            std::vector<std::vector<int>> temp;
            temp = mouseL->getObject();

            al_clear_to_color(background);
            al_draw_line(width/2,0,width/2,height,al_map_rgb(50,10,10),3);
            al_draw_line(0,height/2,width,height/2,al_map_rgb(50,10,10),3);
            al_draw_line(0,height,width,0,al_map_rgb(10,50,10),1);
            for(int x = 0; x < temp.size();x++)
            {
                    al_draw_filled_rectangle(
                                temp[x][0]+250-3,
                                temp[x][1]*-1+250-3,
                                temp[x][0]+250+3,
                                temp[x][1]*-1+250+3,
                                temp[x][2] == 1 ? red:blue);
            }
            if(calculate and pCeptron->getIterations() < pCeptron->getMaxIterations()+2)
            {

               new_Weights = pCeptron->calculate();
               int y1= -(new_Weights[2]/new_Weights[1])-(new_Weights[0]/new_Weights[1]) * -100;
               int y2 = -(new_Weights[2]/new_Weights[1])-(new_Weights[0]/new_Weights[1]) * 100;
                al_draw_line(0,(y1*-1+100),
                        499,
                        (y2*-1+100),
                        al_map_rgb(90,30,50),3);
            }
            al_flip_display();

        }
    }

}
