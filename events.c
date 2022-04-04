// ZX-Spectrum SCREEN$ editor
// (c) 2004 Catalin Mihaila <mihaila_ac@yahoo.com>

#include "main.h"

SDL_Event event;

int want_exit       = 0;



// wait for one event:
int handle_events (void)
{
	int filenew;

    while( SDL_PollEvent(&event))
        {
            switch( event.type )
                {
                    case SDL_QUIT:
						if(screen_is_modif)
							{
								want_exit = 1;
								small_scr = 0;
								ask_for_save();
								return 1;
							} else {
								return 0;
							}
					break;

		    case SDL_KEYUP:
			switch(event.key.keysym.sym)
			    {
					case SDLK_ESCAPE:
					case SDLK_F10:
						if(screen_is_modif)
				    		{
								want_exit = 1;
								small_scr = 0;
								ask_for_save();
								return 1;
				    		} else {
								return 0;
				    		}
					break;

					case SDLK_F1:
						small_scr = 0;
						about();
						ask = 0;
					break;

					case SDLK_F2:
					    want_exit = 0;
						if(screen_is_modif)
							{
								want_new_file = 1;
								small_scr = 0;
								ask_for_save();
							} else {
								for(filenew=0;filenew<768;filenew++) square_draw[filenew] = 0;
								clear_rect(0,SCREENHEIGHT-192,256,192,7);
								new_empty_file();
								redraw_all();
							}
					break;

					case SDLK_F3:
						save_screen();
					break;

					case SDLK_F5:
					case SDLK_g:
					    if(grid_is_visible) { grid_is_visible = 0; }
						else { grid_is_visible = 1; }
						ask = 0;
						redraw_all();
					break;

					case SDLK_RIGHT:
			    		move_right();
			    	break;

					case SDLK_LEFT:
			    		move_left();
			    	break;

					case SDLK_DOWN:
			    		move_down();
			    	break;

					case SDLK_UP:
			    		move_up();
					break;
			    }
		    break;

			case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT)
			    {
// click on exit icon:
				if( event.button.x > SCREENWIDTH-65)
				    {
					if( event.button.x < SCREENWIDTH-32)
					    {
						if( event.button.y > SCREENHEIGHT-33)
						    {
							if(screen_is_modif)
							    {
								want_exit = 1;
								small_scr = 0;
								ask_for_save();
								return 1;
							    } else {
								return 0;
							    }
						    }
					    }
				    }
				mouse_button_release_left(event.button.x, event.button.y);
			    }
			if(event.button.button == SDL_BUTTON_RIGHT) { mouse_button_release_right(event.button.x, event.button.y); }
                    break;

		    case SDL_KEYDOWN:
            break;

            default:
            break;
                }
        }
    return 1;
}
