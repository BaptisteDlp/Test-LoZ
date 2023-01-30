#ifndef DEF_CHARACTER
#define DEF_CHARACTER

#include"Map.hpp"

typedef struct{

    int direction; //Direction of the character
    int animation; //represents the number of the tile to blit
    bool stop; //true if the character is not moving

}MotionCharacteritic;


typedef struct{

    SDL_Surface *tileCharacter; //Tile of the character
    SDL_Rect rectCharacter; //define the tile dimension
    SDL_Rect position; //Position of the character in the grid
    int widthTile; //width of the tile in the tileSet
    int heigthTile; // heigth of the tile in the tileSet


}TileCharacteritic;

enum{UP, DOWN, LEFT, RIGHT};




class Character{

    public:
        Character(SDL_Surface *screen, int width, int heigth);
        ~Character();
        void change_motion() const;
        void blit_Character(SDL_Surface *screen);
        void event_Analysis(SDL_Event event, Map const& map1, bool *keepOnGame);
        bool detection(Map const& map1,int vectorPos);

    private:
        TileCharacteritic m_tileCharacteristic;
        MotionCharacteritic m_motionCharacteristic;

};




#endif
