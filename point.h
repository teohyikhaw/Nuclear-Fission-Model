#include <array>
#include <math.h>

class Point{
public:
    Point(std::array<int,3> c):coords(c){}
    int getvalue(int index) const{
        return coords[index];
    }
    void operator=(const Point &p){
        coords = p.coords;
    }
    double distance(const Point &pt){
        double dist = 0;
        for (int i=0; i<3; i++){
            dist += pow((pt.getvalue(i)-getvalue(i)),2);
        }
        return sqrt(dist);
    }
    unsigned int distance_squared(const Point &pt){
        unsigned int dist = 0;
        for (int i=0; i<3; i++){
            dist += pow((pt.getvalue(i)-getvalue(i)),2);
        }
        return dist;
    }
    bool samePoint(const Point &pt){
        return (pt.getvalue(0)==getvalue(0) && pt.getvalue(1)==getvalue(1) && pt.getvalue(2)==getvalue(2));
    }

    std::array<int,3> getCoords(){
        return coords;
    }

private:
    std::array<int,3> coords;
};