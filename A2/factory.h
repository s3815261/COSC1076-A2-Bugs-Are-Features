#define FACTORY_MAX_ARRAY_SIZE 5

class Tile;


class Factory{

public:
    Factory();

    ~Factory();

    Factory(Factory& other);

    int size();

    //add a tile to the end of the factory
    void addTile(Tile* tile);

    //clear the factory tiles ----> done at the end of a round???
    void clear();



private:
    Tile* tiles[FACTORY_MAX_ARRAY_SIZE];
    int length;



};