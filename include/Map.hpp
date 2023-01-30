#ifndef DEF_MAP
#define DEF_MAP



typedef struct{
    SDL_Rect rectTile;
    bool wall; // if true can not cross obstacle

}Propreties;



class Map{


    public:
        Map(char *const fileName,int bgx, int bgy);
        Map(Map const& map1);
        ~Map();

        void clear_TileSetColorsKey(int red, int green, int blue);
        int print_Map(SDL_Surface *screen) const;

        void setgrid(int i, int j, int numTile); //Change the number of the tile
        void setTileMap(char *const fileName, int colR, int colG, int colB);



        int getwidthTile() const;
        int getheigthTile() const;
        int getbeginX() const;
        int getbeginY() const;
        int getnbTileW() const;
        int getnbTileH() const;
        int getgridW() const;
        int getgridH() const;
        bool getwall(int i) const;
        int getgrid(int i, int j) const;
        SDL_Surface* gettileMap() const;

        Map& operator=(Map const& map1);


    private:
        int widthTile;
        int heigthTile;
        int nbTileW; //nb tiles within x
        int nbTileH; //nb tiles within y
        int gridW; //nb of square within x in the grid
        int gridH; //nb of square within y in the grid
        int beginGridx, beginGridy; //start of the grid in the screen
        int **grid; //grid for the game
        Propreties *tileProp;
        SDL_Surface *tileMap;
};

#endif // DEF_MAP

