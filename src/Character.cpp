
#include<cstdlib>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"Character.hpp"




using namespace std;


Character::Character(SDL_Surface *screen, int width, int heigth){

    m_tileCharacteristic.tileCharacter = SDL_LoadBMP("data/link_bouclier.bmp");
    SDL_SetColorKey(m_tileCharacteristic.tileCharacter, SDL_SRCCOLORKEY, SDL_MapRGB(m_tileCharacteristic.tileCharacter->format, 255, 242, 0));

    m_tileCharacteristic.position.w = width;
    m_tileCharacteristic.position.h = heigth;
    m_tileCharacteristic.position.x = screen->w / 2 - width / 2;
    m_tileCharacteristic.position.y = screen->h / 2 - heigth / 2;

    m_tileCharacteristic.rectCharacter.w = width;
    m_tileCharacteristic.rectCharacter.h = heigth;
    m_tileCharacteristic.rectCharacter.x = 0;
    m_tileCharacteristic.rectCharacter.y = 0;

    m_tileCharacteristic.widthTile = width;
    m_tileCharacteristic.heigthTile = heigth;

    m_motionCharacteristic.direction = DOWN;
    m_motionCharacteristic.stop = true;
    m_motionCharacteristic.animation = 0;

}



Character::~Character(){

    SDL_FreeSurface(m_tileCharacteristic.tileCharacter);

}






void Character::blit_Character(SDL_Surface *screen){


    //choose the right row of the tileSet
    switch(m_motionCharacteristic.direction){

        case UP:
            m_tileCharacteristic.rectCharacter.y = m_tileCharacteristic.heigthTile;
            break;

        case DOWN:
            m_tileCharacteristic.rectCharacter.y = 0;
            break;

        case LEFT:
            m_tileCharacteristic.rectCharacter.y = m_tileCharacteristic.heigthTile*3;
            break;

        case RIGHT:
            m_tileCharacteristic.rectCharacter.y = m_tileCharacteristic.heigthTile*2;
            break;

    }

    //Choose the right column of the tileSet
     if(m_motionCharacteristic.stop){
        m_motionCharacteristic.animation = 3;
    }

    m_tileCharacteristic.rectCharacter.x = m_tileCharacteristic.widthTile*m_motionCharacteristic.animation;


    m_motionCharacteristic.animation++;

    if(m_motionCharacteristic.animation == 7){
        m_motionCharacteristic.animation = 0;
    }

    SDL_BlitSurface(m_tileCharacteristic.tileCharacter,&m_tileCharacteristic.rectCharacter,screen,&m_tileCharacteristic.position);



}




void Character::event_Analysis(SDL_Event event, Map const& map1, bool *keepOnGame){


    switch(event.type){

        case SDL_QUIT:
            *keepOnGame = false;
            break;

        case SDL_KEYDOWN:

            m_motionCharacteristic.stop = false;

            switch(event.key.keysym.sym){

                case SDLK_ESCAPE:
                    *keepOnGame = false;
                    break;

                case SDLK_UP:
                    m_motionCharacteristic.direction = UP;
                    if(!((*this).detection(map1,5)))
                        m_tileCharacteristic.position.y -= 5;
                    break;

                case SDLK_DOWN:
                    m_motionCharacteristic.direction = DOWN;
                    if(!((*this).detection(map1,5)))
                        m_tileCharacteristic.position.y += 5;
                    break;

                case SDLK_LEFT:
                    m_motionCharacteristic.direction = LEFT;
                    if(!((*this).detection(map1,5)))
                        m_tileCharacteristic.position.x -= 5;
                    break;

                case SDLK_RIGHT:
                    m_motionCharacteristic.direction = RIGHT;
                    if(!((*this).detection(map1,5)))
                        m_tileCharacteristic.position.x += 5;
                    break;

            }
            break;

        case SDL_KEYUP:
            m_motionCharacteristic.stop = true;
            m_motionCharacteristic.animation = 3;
            break;

    }



}







bool Character::detection(Map const& map1, int vectorPos){


    int xMin(0), xMax(0);
    int yMin(0), yMax(0);
    bool obstacle(false);
    int numTile(0);


    int posX(m_tileCharacteristic.position.x-vectorPos);
    int posW(m_tileCharacteristic.position.x+m_tileCharacteristic.position.w+vectorPos);
    int posY(m_tileCharacteristic.position.y-vectorPos);
    int posH(m_tileCharacteristic.position.y+m_tileCharacteristic.position.h+vectorPos);


    switch(m_motionCharacteristic.direction){
        case UP:
            if(posY<0){
                return true;
            }
            xMin = (m_tileCharacteristic.position.x + 4)  / map1.getwidthTile();
            xMax = (m_tileCharacteristic.position.x + m_tileCharacteristic.position.w - 4) / map1.getwidthTile();
            yMin = (m_tileCharacteristic.position.y - vectorPos + 10) / map1.getheigthTile();
            yMax = (m_tileCharacteristic.position.y + 10) / map1.getheigthTile();
            break;

        case DOWN:
            if(posH>map1.getheigthTile()*map1.getgridH()){
                return true;
            }
            xMin = (m_tileCharacteristic.position.x+4)  / map1.getwidthTile();
            xMax = (m_tileCharacteristic.position.x + m_tileCharacteristic.position.w - 4) / map1.getwidthTile();
            yMin = (m_tileCharacteristic.position.y + 20) / map1.getheigthTile();
            yMax = (m_tileCharacteristic.position.y + m_tileCharacteristic.position.h -5 + vectorPos) / map1.getheigthTile();
            break;

        case LEFT:
            if(posX<0){
                return true;
            }
            xMin = (m_tileCharacteristic.position.x - vectorPos + 4)  / map1.getwidthTile();
            xMax = (m_tileCharacteristic.position.x + m_tileCharacteristic.position.w - 4) / map1.getwidthTile();
            yMin = (m_tileCharacteristic.position.y + 10) / map1.getheigthTile();
            yMax = (m_tileCharacteristic.position.y + m_tileCharacteristic.position.h - 5) / map1.getheigthTile();
            break;

        case RIGHT:
            if(posW>map1.getwidthTile()*map1.getgridW()){
                return true;
            }
            xMin = (m_tileCharacteristic.position.x + 4)  / map1.getwidthTile();
            xMax = (m_tileCharacteristic.position.x + m_tileCharacteristic.position.w - 4 + vectorPos) / map1.getwidthTile();
            yMin = (m_tileCharacteristic.position.y + 10) / map1.getheigthTile();
            yMax = (m_tileCharacteristic.position.y + m_tileCharacteristic.position.h - 5) / map1.getheigthTile();
            break;

    }


    for(int i = xMin; i<= xMax; i++){
        for(int j = yMin; j<= yMax; j++){
            numTile = map1.getgrid(i,j);
            if(map1.getwall(numTile)){
                obstacle = true;
                break;
            }
        }
    }

    return obstacle;






}


