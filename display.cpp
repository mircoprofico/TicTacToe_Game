#include "display.h"

DisplayTTT::DisplayTTT()    // #2 What is this formatting?? Eurk
        : _logicGame(LogicTTT()), _appIsRunning(false)
        , _window(nullptr), _renderer(nullptr)  // These pointers could be initialized with a default value in the class instead of in each constructor
        ,_imagePlayer1(nullptr), _imagePlayer2(nullptr)
{
    initWindow();
}

DisplayTTT::DisplayTTT(Game logicGame)
        : _logicGame(logicGame), _appIsRunning(false)
        , _window(nullptr), _renderer(nullptr)
        ,_imagePlayer1(nullptr), _imagePlayer2(nullptr)
{
    initWindow();
}

DisplayTTT::DisplayTTT(const DisplayTTT& src)
        : _logicGame(src._logicGame), _appIsRunning(src._appIsRunning)
        ,_window(nullptr), _renderer(nullptr)
        ,_imagePlayer1(nullptr), _imagePlayer2(nullptr)
{
    initWindow();
}

DisplayTTT::~DisplayTTT()
{
    if (_window != nullptr) {
        SDL_DestroyWindow(_window);
        _window = nullptr;  // Good to have nullified the freed pointers!
    }
    if (_renderer != nullptr) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_imagePlayer1 != nullptr) {
        SDL_DestroyTexture(_imagePlayer1);
        _imagePlayer1 = nullptr;
    }
    if (_imagePlayer2 != nullptr) {
        SDL_DestroyTexture(_imagePlayer2);
        _imagePlayer2 = nullptr;
    }
}

void DisplayTTT::run()
{
    Game::GameState status;
    _appIsRunning = true;

    while (_appIsRunning)
    {
        handleEvents();
        render();
        status = _logicGame.getStatus();
        if (status != Game::GameState::IN_PROGRESS) {
            resetDisplay();
        }
        SDL_Delay(SDL_DELAY);   // #3 Why wait?
    }
}

void DisplayTTT::initWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("SDL initialization failed: "  + std::string(SDL_GetError()));
    }

    SDL_CreateWindowAndRenderer(WIDTH_WINDOW, HEIGTH_WINDOW, SDL_WINDOW_SHOWN, &_window, &_renderer);
    if (_window == nullptr or _renderer == nullptr) {
        throw std::runtime_error("SDL window/renderer creation failed "  + std::string(SDL_GetError()));
    }

    SDL_SetWindowTitle(_window, "Tic Tac Toe");
    _imagePlayer1 = initTexture("../assets/image_X_red.bmp");
    _imagePlayer2 = initTexture("../assets/image_O_blue.bmp");
    SDL_RenderPresent(_renderer);
}

SDL_Texture* DisplayTTT::initTexture(const char *path)
{
    SDL_Surface* imageSurface = SDL_LoadBMP(path);
    if (imageSurface == nullptr) {
        throw std::runtime_error("Failed to load image " + std::string(path) + ": " + std::string(SDL_GetError()));
    }
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(_renderer, imageSurface);
    if (imageTexture == nullptr)
        throw std::runtime_error("Failed to load image " + std::string(path) + ": " + std::string(SDL_GetError()));
    SDL_FreeSurface(imageSurface);
    return imageTexture;
}

void DisplayTTT::render()
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  // windows white
    SDL_RenderClear(_renderer);

    // Draw grid
    Game::GameState status = _logicGame.getStatus();;  // Oh! An additional ; on this line! :O
    if (status == Game::GameState::PLAYER_1_WIN)
        addGrid(255, 0, 0, SDL_ALPHA_OPAQUE);
    else if (status == LogicTTT::GameStatus::PLAYER_2_WIN)
        addGrid(0, 0, 255, SDL_ALPHA_OPAQUE);
    else if (status == LogicTTT::GameStatus::DRAW)
        addGrid(255, 0, 255, SDL_ALPHA_OPAQUE);
    else
        addGrid(0, 0, 0, SDL_ALPHA_OPAQUE);


    for (const auto& imageInfo : _images) { // #21 Should use DisplayTTT::ImageInfo
        SDL_RenderCopy(_renderer, imageInfo._imagePlayer, nullptr, &imageInfo.rect);
    }

    // Update screen
    SDL_RenderPresent(_renderer);
}

void DisplayTTT::addGrid(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    for (size_t i = 1; i < _logicGame.getRow(); ++i) {
        SDL_RenderDrawLine(_renderer, 0, i * (HEIGTH_WINDOW / _logicGame.getRow()), WIDTH_WINDOW,
                           i * (HEIGTH_WINDOW / _logicGame.getRow()));
    }
    for (size_t i = 1; i < _logicGame.getCol(); ++i) {
        SDL_RenderDrawLine(_renderer, i * (WIDTH_WINDOW / _logicGame.getCol()), 0,
                           i * (WIDTH_WINDOW / _logicGame.getCol()), HEIGTH_WINDOW);
    }
}

void DisplayTTT::addImage(SDL_Texture *img, int col, int row)
{
    if (img == nullptr) {
        return;
    }

    ImageInfo imageInfo;
    imageInfo._imagePlayer = img;

    imageInfo.rect.x = col * (WIDTH_WINDOW / _logicGame.getCol());
    imageInfo.rect.y = row * (HEIGTH_WINDOW / _logicGame.getRow());
    imageInfo.rect.w = WIDTH_WINDOW / _logicGame.getCol();
    imageInfo.rect.h = HEIGTH_WINDOW / _logicGame.getRow();

    _images.push_back(imageInfo);
}

void DisplayTTT::handleEvents()
{
    SDL_PollEvent(&_event);

    switch (_event.type) {
        case SDL_QUIT:
            _appIsRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (_event.button.button == SDL_BUTTON_LEFT) {
                handleMouseClick(_event.button.x, _event.button.y);
            }
            break;

        default:
            break;
    }
}

void DisplayTTT::handleMouseClick(int mouseX, int mouseY)
{
    int clickedCol = mouseX / (WIDTH_WINDOW / _logicGame.getCol());
    int clickedRow = mouseY / (HEIGTH_WINDOW / _logicGame.getRow());

    if (_logicGame.getCell(clickedRow, clickedCol) != Game::Player::NONE)   // #21 This check should be done in the logic part!
        return;

    Game::Player currentPlayer = _logicGame.getPlayer();
    _logicGame.play(clickedRow, clickedCol);

    if (currentPlayer == Game::Player::PLAYER_1)
        addImage(_imagePlayer1, clickedCol, clickedRow);
    else if (currentPlayer == Game::Player::PLAYER_2)
        addImage(_imagePlayer2, clickedCol, clickedRow);
}

void DisplayTTT::resetDisplay()
{
    SDL_Delay(2000);    // #6 This value should be a class attribute
    _logicGame.restart();
    _images.clear();
}