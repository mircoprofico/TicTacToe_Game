#ifndef DISPLAYTTT_H
#define DISPLAYTTT_H

#include <string>   // #3 Should be only in the .cpp (as it is not used in .h)
#include <SDL.h>
#include "game.h"

class DisplayTTT
{
public:
    DisplayTTT(); // Default constructor not used
    DisplayTTT(Game logicGame);
    DisplayTTT(const DisplayTTT& srcs);   // Constructor by copy not used
    ~DisplayTTT();

    typedef struct {
        SDL_Texture* _imagePlayer;
        SDL_Rect rect;  // #5 Why rect cannot have a '_' as prefix?
    } ImageInfo;

    void run();

private:

    // #6 Const for class attributes are not recommended. Should not be in CAPITAL LETTER
    const size_t WIDTH_WINDOW  = 600;
    const size_t HEIGTH_WINDOW = 600;
    const size_t SDL_DELAY = 10;

    Game _logicGame;
    bool _appIsRunning;
    std::vector<ImageInfo> _images;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Event _event;
    SDL_Texture* _imagePlayer1;
    SDL_Texture* _imagePlayer2;

    void initWindow();
    SDL_Texture* initTexture(const char* path);
    void render();
    void addGrid(Uint8 r, Uint8 g, Uint8 b, Uint8 a);   // Nice to use unsigned values on 8 bits. Could have been directly uint8_t from <cstdint>
    void addImage(SDL_Texture* img, int x, int y);
    void handleEvents();
    void handleMouseClick(int mouseX, int mouseY);

    void resetDisplay();
};

#endif /* DISPLAYTTT_H */