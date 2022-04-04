// ZX-Spectrum SCREEN$ editor
// (c) 2004 Catalin Mihaila <mihaila_ac@yahoo.com>

#include "main.h"

SDL_Surface *scrbuf;
SDL_Window *sdl_window;
SDL_Texture *sdl_texture;
SDL_Renderer *sdl_renderer;

// init SDL:
int init_graphic_lib (void)
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
        {
            if(debug) { printf("FAILED\n"); }
            return 1;
        } else {
            if(debug) { printf("OK\n"); }
            return 0;
        }
}


// open window:
int init_graphic_window (void)
{
    char windowtitle[256];

    sprintf(windowtitle,CAPTION,MAJV,MINV);

    /* scrbuf = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, 16, SDL_SWSURFACE|SDL_ANYFORMAT);//|SDL_FULLSCREEN );
    if( scrbuf == NULL )
        {
            if(debug) { printf("FAILED\n"); }
            return(1);
        }
    */
    if (debug) {
      printf("Creating window %d x %d\n", SCREENWIDTH, SCREENHEIGHT);
    }
    sdl_window = SDL_CreateWindow(windowtitle, 
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREENWIDTH, SCREENHEIGHT,
                                  SDL_WINDOW_OPENGL);
    if ( ! sdl_window) {
      fprintf(stderr, "SDL_CreateWindow failed\n");
      return 1;
    }

    scrbuf = SDL_CreateRGBSurface(0, SCREENWIDTH, SCREENHEIGHT, 16, 0, 0, 0, 0);
    if ( ! scrbuf) {
      fprintf(stderr, "SDL_CreateRGBSurface failed\n");
      return 1;
    }
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    if ( ! sdl_renderer) {
      fprintf(stderr, "SDL_CreateRenderer failed\n");
      return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdl_renderer, SCREENWIDTH, SCREENHEIGHT);

    sdl_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STATIC, SCREENWIDTH, SCREENHEIGHT);
    if ( ! sdl_texture) {
      fprintf(stderr, "SDL_CreateTexture failed\n");
      return 1;
    }

    // scrbuf = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, 16, SDL_SWSURFACE|SDL_ANYFORMAT);//|SDL_FULLSCREEN );

    if(debug) { printf("OK\n"); }
    return 0;
}

// done... close SDL:
int close_graphic_lib (void)
{
    if(debug) { printf("Quit SDL...\n"); }
    SDL_Quit();
    return 0;
}

int update_screen (void)
{
    if(debug) { printf("Update all screen\n"); }
    SDL_UpdateTexture(sdl_texture, NULL, scrbuf->pixels, scrbuf->pitch);
    SDL_RenderCopy(sdl_renderer, sdl_texture, 0, 0);
    SDL_RenderPresent(sdl_renderer);
    return 0;
}
