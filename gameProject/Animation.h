class Animation
{
public:
    std::string id;
    SDL_RendererFlip flip;
    int row;
    int AnimationSpeed;
    int frameCount;
    int frame;
    bool isAnimationDone;
    Uint32 startTime; 

    Animation() : startTime(0), isAnimationDone(false) {}

    Animation(std::string _id, SDL_RendererFlip _flip, int _row, int _AnimationSpeed, int _frameCount, int _frame)
        : id(_id), flip(_flip), row(_row), AnimationSpeed(_AnimationSpeed), frameCount(_frameCount), frame(_frame), startTime(0), isAnimationDone(false) {}

    void SetAnimation(std::string _id, SDL_RendererFlip _flip, int _row, int _AnimationSpeed, int _frameCount, int _frame)
    {
        if (id != _id) {
            id = _id;       
            flip = _flip;
            row = _row;
            AnimationSpeed = _AnimationSpeed;
            frameCount = _frameCount;
            frame = 0;
            startTime = SDL_GetTicks(); 
            isAnimationDone = false; 
        }
    }

    void UpdateAnimation()
    {
        Uint32 currentTime = SDL_GetTicks();
        frame = ((currentTime - startTime) / AnimationSpeed) % frameCount;
        if (frame == frameCount - 1) {
            isAnimationDone = true;
        }
        else {
            isAnimationDone = false;
        }
    }

    void DrawAnimation(std::string id, float x, float y, int width, int height, SDL_RendererFlip flip)
    {
        AssetManager::GetInstance()->renderObject(id, x, y, width, height, row, frame, flip);
    }

    bool IsAnimationDone() const {
        return isAnimationDone;
    }
};
