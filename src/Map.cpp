#include<cstdlib>
#include<iostream>
#include<fstream>
#include<SDL/SDL.h>
#include"Map.hpp"
#include<string>
#include<cassert>




    using namespace std;






Map::Map(char* const fileName,int bgx, int bgy){


    ifstream stream(fileName);

    if(!stream){
      cout<<"ERROR OPENING "<<fileName<<endl; exit(1);
    }
    string line;
    int nbTile,num;

    for(int i = 0;i<3;i++){
      getline(stream,line); cout<<line<<endl;
    }
    //===========================A remanier pour charger le bon ficher==========
    line = "data/"+line;
   
    char * cstr = new char [line.length()+1];
    strcpy (cstr, line.c_str());
    cout<<cstr<<endl;
    tileMap = SDL_LoadBMP("data/tileSetZelda.bmp");
    delete [] cstr;
    //============================================================================
   

    stream>>nbTileW;
    stream>>nbTileH;
    stream>>widthTile;
    stream>>heigthTile;

    beginGridx = widthTile * bgx;
    beginGridy = heigthTile * bgy;


    nbTile = nbTileW * nbTileH;
    tileProp = new Propreties[nbTile];

    for(int i = 0;i<nbTile;i++){
      stream>>num;

      stream>>num;

      if(num==1){
	tileProp[i].wall = true;
      }else{
	tileProp[i].wall = false;
      }
    }

    int n(0);
    for(int i = 0; i<nbTileW; i++){
      int width = i * widthTile;
      for(int j = 0; j<nbTileH; j++){
	tileProp[n].rectTile.w = widthTile;
	tileProp[n].rectTile.h = heigthTile;
	tileProp[n].rectTile.x = width;
	tileProp[n].rectTile.y = j*heigthTile;
	n++;
      }
    }

    getline(stream,line);
    getline(stream,line);
    stream>>gridW;
    stream>>gridH;

    grid = new int*[gridW];

    for(int i = 0;i<gridW;i++){
      grid[i] = new int[gridH];
    }

    for(int j = 0; j<gridH; j++){
      for(int i = 0; i<gridW; i++){
	stream>>grid[i][j];
      }
    }
    stream.close();

}


Map::Map(Map const& map1){

  tileMap = map1.gettileMap();
  widthTile = map1.getwidthTile();
  heigthTile = map1.getheigthTile();
  nbTileW = map1.getnbTileW();
  nbTileH = map1.getnbTileH();
  gridW = map1.getgridW();
  gridH = map1.getgridH();
  beginGridx = map1.getbeginX();
  beginGridy = map1.getbeginY();

  int nbTile = nbTileW * nbTileH;
  tileProp = new Propreties[nbTile];

  for(int i = 0;i<nbTile;i++){
    tileProp[i].wall = map1.getwall(i);
  }

  int n(0);
  for(int i = 0; i<nbTileW; i++){
    int width = i * widthTile;
    for(int j = 0; j<nbTileH; j++){
      tileProp[n].rectTile.w = widthTile;
      tileProp[n].rectTile.h = heigthTile;
      tileProp[n].rectTile.x = width;
      tileProp[n].rectTile.y = j*heigthTile;
      n++;
    }
  }

  grid = new int*[gridW];

  for(int i = 0;i<gridW;i++){
    grid[i] = new int[gridH];
  }

  for(int j = 0; j<gridH; j++){
    for(int i = 0; i<gridW; i++){
      grid[i][j] = map1.getgrid(i,j);
    }
  }


}




Map::~Map(){

  for (int i=0; i<gridW; i++){
    delete[] grid[i];
  }

  delete[] grid;
  delete[] tileProp;

  SDL_FreeSurface(tileMap);



}

void Map::clear_TileSetColorsKey(int red, int green, int blue){

    SDL_SetColorKey(tileMap, SDL_SRCCOLORKEY, SDL_MapRGB(tileMap->format, red, green, blue));

}



int Map::getwidthTile() const{ return widthTile;}
int Map::getheigthTile() const{ return heigthTile;}
int Map::getbeginX() const{ return beginGridx;};
int Map::getbeginY() const{ return beginGridy;};
int Map::getnbTileW() const{ return nbTileW;}
int Map::getnbTileH() const{ return nbTileH;}
int Map::getgridW() const{ return gridW;}
int Map::getgridH() const{ return gridH;}
bool Map::getwall(int i) const{ return tileProp[i].wall;}
int Map::getgrid(int i, int j) const{return grid[i][j];}
SDL_Surface* Map::gettileMap() const{return tileMap;}




void Map::setgrid(int i, int j, int numTile){

    assert(i > -1 && j > -1 && i < gridW && j < gridH);
    grid[i][j] = numTile;

}




void Map::setTileMap(char *const fileName, int colR, int colG, int colB){

    SDL_FreeSurface(tileMap);
    tileMap = SDL_LoadBMP(fileName);
    (*this).clear_TileSetColorsKey(colR,colG,colB);


}






int Map::print_Map(SDL_Surface *screen) const{

    SDL_Rect position;
    int numTile = 0;


    for(int i = 0; i<gridW; i++){

        for(int j = 0; j<gridH; j++){

            position.x = i * widthTile + beginGridx;
            position.y = j * heigthTile + beginGridy;
            numTile = grid[i][j];
            SDL_BlitSurface(tileMap, &tileProp[numTile].rectTile, screen, &position);
        }

    }

    return 1;

}



Map& Map::operator=(Map const& map1){

    Map m(map1);

    return m;

}

