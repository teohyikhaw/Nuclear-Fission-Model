const int damage_point = 4;

class Particle{
public:
    Particle(){
        lifespan = 30;
    }

    void operator=(const Particle &p){
        lifespan = p.lifespan;
    }
    bool alive(){
        return (lifespan>0);
    }
    void hit(){
        lifespan -= damage_point;
    }
    int health(){
        return lifespan;
    }
private:
    int lifespan;
};