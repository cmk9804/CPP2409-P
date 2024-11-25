class Bullet {
protected:
    int b_posX;
    int b_posY;


    bool active;
public:
    Bullet();
    void setActive(bool flag);
    void initBullet(int x, int y, bool facing);
    bool isActive();
    bool B_Update();

    int getPosX();
    int getPosY();
};