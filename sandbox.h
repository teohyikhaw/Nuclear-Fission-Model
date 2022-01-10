#include "kdtree.h"

class Sandbox : public KDtree{
public:
    Sandbox(Node* temp):KDtree(temp){
    }

    double probabilityFunction(int x){
        double probability = 1 - 0.2*x;
        return probability;
    }

    bool spawn(Node* root,int number_in_range){
        int value = int (probabilityFunction(number_in_range)*10);
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distribution_x(0,10);
        int x = distribution_x(rng);

        if (x<=value) return true;
        return false;
    }

    void hitparticle(Node* root){
        root->localparticle.hit();
        if(!root->localparticle.alive()) {
            deleteNode(root);
            return;
        }
        int numberInRange=inRange(root->localpoint.getCoords(),8);
        if(spawn(root,numberInRange)){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> distribution_x(5,10);
            int x = distribution_x(rng);
            Node* p = generateRandomNode(root->localpoint.getCoords(),x);
            insert(p->localpoint.getCoords());
        }
    }

    //Getters

    Node* getCore(){
        return getRootNode();
    }

private:

};