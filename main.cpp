#include <cstdio>
#include <unistd.h>

#include "log.h"
#include "PanelConfig.h"
#include "PanelController.h"

#include "MachineService.h"

#include <wiringPi.h>
#include <chrono>

#include "RemoteControlServer.h"

#include "SDL.h"
int testSDL()
{
    SDL_Surface* screen = NULL;
    //Start SDL
    SDL_Init( SDL_INIT_VIDEO );

   const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo ();
   
   int systemX = videoInfo->current_w ;
   int systemY = videoInfo->current_h ;
   Uint8 bpp = videoInfo->vfmt->BitsPerPixel ;
   
    //Set up screen
    screen = SDL_SetVideoMode( systemX, systemY, bpp, SDL_SWSURFACE );
    if (!screen)
    {
        printf("SDL_SetVideoMode failed\n");
        return 0;
    }
    
    SDL_ShowCursor(SDL_DISABLE);
    SDL_Rect r = {0,0,240,320};
    SDL_FillRect(screen,&r, SDL_MapRGB(screen->format, 200,200,0) );

    //Update Screen
    SDL_Flip( screen );
    //Pause
    SDL_Delay( 2000 );

    //Quit SDL
    SDL_Quit();

    return 0;
}




bool enableLog = true;
bool enableLogDebug = false;

int main(int argc, char** argv)
{
  LOG("");
  
  testSDL();

  wiringPiSetup();
  
  LOG("");

  auto machineService = mach::MachineRegistry::getMachineService();
  machineService->start();

  auto panelConfig = std::make_shared<cfg::PanelConfig>();
  try
  {
    panelConfig->tryReadConfig("/home/pi/panel.config");
  }  catch (cfg::ConfigParseException& e)
  {
    LOG("Cannot read config. What: %s\nBye bye.", e.what());
    exit(-1);
  }

  auto panelController = std::make_shared<ctrl::PanelController>(panelConfig);
  panelController->start();

  auto remoteControlServer = std::make_shared<net::RemoteControlServer>(2014);
  remoteControlServer->start();



  while (1)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }

  LOG("Bye bye.");
  return 0;
}

