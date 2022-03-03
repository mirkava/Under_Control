#include "image.h"
#include "event.h"
#include <SDL/SDL_mixer.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv)
{ 

//initialisation
if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO)!=0)
{
printf("erreur:%s \n",SDL_GetError());
return 1;
}
if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
{
printf("%s",Mix_GetError());
}


Mix_Music *music;
Mix_Chunk *son;
button button[3];
backg backg;
int change=0,done=0;
float curframe=0;
int maxframe=54;
image bkg,terre,start,settings,leave,volume,logo,start_s,settings_s,leave_s,parametres;
SDL_Event event;
atexit(SDL_Quit);
Mix_AllocateChannels(20);

SDL_Surface *ecran;
ecran=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA);
if(ecran==NULL)
{
printf("unable to set 1532*864 video:%s\n",SDL_GetError());
return 1;
}
  
  
initbkg(&bkg);
initstart(&start);
initsettings(&settings); 
initleave(&leave);
initstart_s(&start_s);
initsettings_s(&settings_s); 
initleave_s(&leave_s);
initearth(&terre);
initlogo(&logo);
son=Mix_LoadWAV("gun.wav");
music=Mix_LoadMUS("backsound.mp3");
if(music==NULL || son==NULL) return 1;

//jouer son continu
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(MIX_MAX_VOLUME);

backg.niveau[0]=bkg;
backg.niveau[1]=parametres;

//game loop
while(done!=1)
{affichage(&change,ecran,bkg,&terre,logo,&curframe,maxframe);
//tableau des bouttons 
button[0].niveau=start;
button[1].niveau=settings;
button[2].niveau=leave;
while(SDL_PollEvent(&event))
{
play_event(&done,event,bkg,start,settings,leave,volume,ecran,son,start_s,settings_s,leave_s,button,&change);
}
//affichage des boutons
afficher_img(button[0].niveau,ecran);
afficher_img(button[1].niveau,ecran);
afficher_img(button[2].niveau,ecran);
SDL_Flip(ecran);

}

//liberer memoire
liberer_img(bkg);
liberer_img(start);
liberer_img(settings);
liberer_img(leave);
liberer_img(logo);
liberer_img(start_s);
liberer_img(settings_s);
liberer_img(leave_s);
liberer_img(terre);
Mix_FreeMusic(music);
Mix_FreeChunk(son);

return 0;
}
