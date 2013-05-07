#ifndef FOLLOWER_H_INCLUDED
#define FOLLOWER_H_INCLUDED

class CFollower{
    private:
    float dx,dy,dz,px,py,pz,kx,ky,kz;
    long lastTimestamp;

    public:

    CFollower(){
        dx = dy = dz = px = py = pz = 0;
        kx = ky = kz = 0.05f;
        long timestamp = GetTickCount();
    }

    CFollower(float x, float y, float z, float k){
        dx = px = x;
        dy = py = y;
        dz = pz = z;
        kx = ky = kz = k;
        lastTimestamp = GetTickCount();
    }

    CFollower(float x, float y, float k){
        dx = px = x;
        dy = py = y;
        dz = pz = 0;
        kx = ky = kz = k;
        lastTimestamp = GetTickCount();
    }

    CFollower(float x, float k){
        dx = px = x;
        dy = dz = py = pz = 0;
        kx = ky = kz = k;
        lastTimestamp = GetTickCount();
    }

    void setDestination(float x,float y,float z){
        dx=x;
        dy=y;
        dz=z;
    }

    void setDestination(float x,float y){
        dx=x;
        dy=y;
    }

    void setDestination(float x){
        dx=x;
    }

    void setPosition(float x, float y, float z){
        px = x;
        py = y;
        pz = z;
    }

    void setPosition(float x, float y){
        px = x;
        py = y;
    }

    void setPosition(float x){
        px = x;
    }

    void resetPosition(){
        setPosition(dx,dy,dz);
    }

    void getPosition(float &x, float &y , float &z){
        x = px;
        y = py;
        z = pz;
    }

    void getPosition(float &x, float &y){
        x = px;
        y = py;
    }

    void getPosition(float &x){
        x = px;
    }

    void setK(float x, float y, float z){
        kx = x;
        ky = y;
        kz = z;
    }

    void setK(float x, float y){
        kx = x;
        ky = y;
        kz = 0;
    }

    void setK(float k){
        kx = ky = kz = k;
    }

    void update(){
        long timestamp = GetTickCount();

        px = px+(dx-px)*kx;
        py = py+(dy-py)*ky;
        pz = pz+(dz-pz)*kz;

        lastTimestamp = timestamp;
    }

    void updateAndGetPosition(float &x, float &y , float &z){
        update();

        x = px;
        y = py;
        z = pz;
    }

    void updateAndGetPosition(float &x, float &y){
        update();

        x = px;
        y = py;
    }

    void updateAndGetPosition(float &x){
        update();

        x = px;
    }

    float getPositionX(){
        return px;
    }

    float getPositionY(){
        return py;
    }

    float getPositionZ(){
        return pz;
    }

};

#endif // FOLLOWER_H_INCLUDED
