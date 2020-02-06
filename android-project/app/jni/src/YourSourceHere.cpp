#include <cstdio>
#include <SDL.h>
#include <android/native_window.h>
#include <android/native_activity.h>
#include <android/log.h>
#define TAGS "Test"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAGS,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAGS,__VA_ARGS__)
using namespace std;
int main(int argc,char** args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    LOGD("Initialized");
    SDL_Window *window;
    window = SDL_CreateWindow("MotherFuck",0,0,1440,2560,SDL_WINDOW_SHOWN);
    if(!window)
    {
        LOGE("Error Creating Window%s",SDL_GetError());
        return 1;
    }
    SDL_Surface *winSurface = SDL_GetWindowSurface(window);
    if(!winSurface)
    {
        LOGE("Error Creating winSurface%s",SDL_GetError());
        return 1;
    }
    //绘画
    char path[128];
    unsigned char* src;
    sprintf(path,"%s/test.bmp",SDL_AndroidGetInternalStoragePath());
    LOGD("path:%s",path);
    SDL_Surface* image = SDL_LoadBMP(path);
    if(!image)
        LOGE("image open error:%s",SDL_GetError());
    SDL_Rect dest;
    dest.x=0;
    dest.y=0;
    SDL_FillRect(winSurface,NULL,SDL_MapRGB(winSurface->format,255,90,120));
    if(SDL_BlitSurface(image,nullptr,winSurface,&dest)<0)
        LOGE("Can't blit");
    SDL_UpdateWindowSurface(window);
    SDL_Delay(3000);
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    window = NULL;
    winSurface = NULL;
    SDL_Quit();
    return 0;
}