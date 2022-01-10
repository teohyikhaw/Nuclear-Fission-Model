#include <iostream>
#include "point.h"
#include "particle.h"
#include <random>
#define width 10
#define height 10
#define length 10

struct Node{
    Node (const Point &pt):localpoint(pt),left(nullptr),right(nullptr){}
    Node *left;
    Node *right;
    Point localpoint;
    Particle localparticle;

    ~Node(){
        delete left;
        delete right;
    }
};

struct Node* newNode(std::array<int, 3> a){
    Point temp_point(a);
    //SmartPtr<Node> temp(new Node(temp_point));
    //std::shared_ptr<Node> temp(new Node(temp_point));
    Node* temp = new Node(temp_point);
    temp->left = nullptr;
    temp->right = nullptr;  
    return temp;
}

void printNode(Node* node){
    std::cout<<"(";
    for (int i=0; i<3; i++){
        std::cout<<node->localpoint.getvalue(i);
        if (i!=2) std::cout<<",";
    }
    std::cout<<")"<<std::endl;
}

class KDtree{
public:
    KDtree(Node* node){
        root = node;
        allNodes.push_back(root->localpoint.getCoords());
        entityCount = 1;
        includeCore = false;
    }
    ~KDtree(){
        delete root;
    }
    Node* insertRec(Node *source, Node* p, int depth){
        if (source == nullptr){
            allNodes.push_back(p->localpoint.getCoords());
            entityCount++;
            return p;
        }
        if (sameNode(source,p)) return source;

        int level = (depth+1) % 3;

        if ((p->localpoint.getvalue(depth))<(source->localpoint.getvalue(depth))){
            source -> left = insertRec(source->left,p,level);
        }
        else{
            source -> right = insertRec(source->right,p,level);
        }
        return source;
    }

    void insert(std::array<int, 3> a){
        root = insertRec(root,newNode(a),0);
    }

    void print(Node *node, int space = 0)const{
        if (node==nullptr) return;
        space+=5;
        print(node->right , space);
        for (int i=0; i<space;i++)
            std::cout<<" ";
        std::cout<<"(";
        for (int i=0; i<3; i++){
            std::cout<<node->localpoint.getvalue(i);
            if (i!=2) std::cout<<",";
        }
        std::cout<<")"<<std::endl;
        print(node->left , space);
    }

    void print() const{
        print(root,0);
    }

    void printVector() const{
        for(int i=0;i<allNodes.size();i++){
            std::cout<<"(";
            for (int j=0; j<3; j++){
                std::cout<<allNodes[i][j];
                if (j!=2) std::cout<<",";
            }
            std::cout<<")"<<std::endl;
        }
    }

    int inRange (Node *source , std::array<int, 3> target_point, int distance, int depth){
        if(source==nullptr) return 0;
        int a = source->localpoint.getvalue(0);
        int b = source->localpoint.getvalue(1);
        int c = source->localpoint.getvalue(2);
        if(target_point[0]-distance<=a  && target_point[0]+distance>= a){
            if(target_point[1]-distance<=b  && target_point[1]+distance>= b){
                if(target_point[2]-distance<=c  && target_point[2]+distance>= c){
                    int success = 0;
                    Point temp_point(target_point);
                    if (source->localpoint.distance_squared(temp_point)<=distance*distance) ++success;
                    return inRange(source->left, target_point, distance, depth+1)+inRange(source->right, target_point, distance, depth+1)+success;
                }
            }
        }
        int level = depth % 3;
        if(target_point[level]-distance<source->localpoint.getvalue(level))
            return inRange(source->right, target_point, distance, depth+1);
        else
            return inRange(source->left, target_point, distance, depth+1);
    }

    int inRange (std::array<int, 3> target_point, int distance){
        return inRange(root,target_point,distance,0)-1;
    }

    bool sameNode(Node* n1, Node *n2){
        return (n1->localpoint).samePoint(n2->localpoint);
    }

    Node* smallestNode(Node* x, Node* y, Node*z, int index){
        if(y!=nullptr && x->localpoint.getvalue(index) > y->localpoint.getvalue(index)){
            if(z!=nullptr && y->localpoint.getvalue(index) > z->localpoint.getvalue(index)) return z;
            else return y;
        }
        else{
            if(z!=nullptr && x->localpoint.getvalue(index) > z->localpoint.getvalue(index)) return z;
            else return x;
        }
    }

    Node* smallestNode(Node* x, Node* y, int index){
        if(y!=nullptr && y->localpoint.getvalue(index) < x->localpoint.getvalue(index)) return y;
        else return x;
    }

    Node* findMin(Node* source, int dimension, int depth){
        if (source==nullptr) return nullptr;
        //int level = depth % 3;
        if (depth==dimension){
            if (source->left == nullptr) return source;
            else return smallestNode(source,findMin(source->left, dimension, (depth+1)%3),dimension);
        }
        return smallestNode(source,findMin(source->left, dimension, (depth+1)%3),findMin(source->right, dimension, (depth+1)%3),dimension);
    }

    Node* findMin(Node* p, int dimension){
        return findMin(p,dimension,0);
    }

    Node* largestNode(Node* x, Node* y, Node*z, int index){
        if(y!=nullptr && y->localpoint.getvalue(index) > x->localpoint.getvalue(index)){
            if(z!=nullptr && z->localpoint.getvalue(index) > y->localpoint.getvalue(index)) return z;
            else return y;
        }
        else{
            if(z!=nullptr && z->localpoint.getvalue(index) > x->localpoint.getvalue(index)) return z;
            else return x;
        }
    }

    Node* largestNode(Node* x, Node* y, int index){
        if(y!=nullptr && y->localpoint.getvalue(index) > x->localpoint.getvalue(index)) return y;
        else return x;
    }

    Node* findMax(Node* source, int dimension, int depth){
        if (source==nullptr) return nullptr;
        //int level = depth % 3;
        if (depth==dimension){
            if (source->right == nullptr) return source;
            else return largestNode(source,findMax(source->right, dimension, (depth+1)%3),dimension);
        }
        return largestNode(source,findMax(source->left, dimension, (depth+1)%3),findMax(source->right, dimension, (depth+1)%3),dimension);
    }

    Node* findMax(Node* p, int dimension){
        return findMax(p,dimension,0);
    }

    Node* deleteNode(Node* source, Node* temp, int depth){
        if (source==nullptr) {
            std::cout<<"Point not found"<<std::endl;
            return nullptr;
        }

        if(sameNode(source,temp)){
            if(source->right != nullptr){
                Node *minimum = findMin(source->right,depth,(depth+1)%3);
                source->localpoint = minimum->localpoint;
                source->localparticle = minimum ->localparticle;
                source->right = deleteNode(source->right,minimum,(depth+1)%3);
            }
            else if (source->left != nullptr){
                Node *maximum = findMax(source->left,depth,(depth+1)%3);
                source->localpoint = maximum->localpoint;
                source->localparticle = maximum ->localparticle;
                source->left = deleteNode(source->left,maximum,(depth+1)%3);
            }
            else{
                entityCount--;
                delete source;
                source = nullptr;
                return nullptr;
            }
            return source;
        }
        if(temp->localpoint.getvalue(depth) < source->localpoint.getvalue(depth))
            source->left = deleteNode(source->left,temp,(depth+1)%3);
        else
            source->right = deleteNode(source->right,temp,(depth+1)%3);
        return source;
    }

    void deleteNode(Node* target_point){
        deleteNodeFromVector(target_point);
        deleteNode(root, target_point, 0);
    }

    void deleteNodeFromVector(Node* target_node){
        int x = target_node->localpoint.getvalue(0);
        int y = target_node->localpoint.getvalue(1);
        int z = target_node->localpoint.getvalue(2);
        for(int i=0; i<allNodes.size();i++){
            if(x==allNodes[i][0] && y==allNodes[i][1] && z==allNodes[i][2]) {
                allNodes.erase(allNodes.begin()+i);
                break;    
            } 
        }
    }

    Node* generateRandomNode(std::array<int, 3> target_point , int distance){
        Point target(target_point);
        std::array<int, 3> check_point;
        int x, y, z;
        bool bFlag = true;
        do{
            Point *temp;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> distribution_x(biggerValue(0,target_point[0]-distance),smallerValue(width,target_point[0]+distance));
            x = distribution_x(rng);
            if (x<0) x = x*-1;
            std::uniform_int_distribution<std::mt19937::result_type> distribution_y(biggerValue(0,target_point[1]-distance),smallerValue(height,target_point[1]+distance));
            y = distribution_y(rng);
            if (y<0) y = y*-1;
            std::uniform_int_distribution<std::mt19937::result_type> distribution_z(biggerValue(0,target_point[2]-distance),smallerValue(length,target_point[2]+distance));
            z = distribution_z(rng);
            if (z<0) z = z*-1;

            std::array<int, 3> temp_array = {x,y,z};
            check_point = temp_array;
            //use unique pointer here
            temp = new Point(check_point);
            if(!(target.samePoint(*temp) || target.distance_squared(*temp)>distance*distance)) bFlag = false;
            delete temp;
        }
        while(bFlag);
        return newNode(check_point);
    }

    int smallerValue(int first, int second){
        if (first<second) return first;
        return second;
    }

    int biggerValue(int first, int second){
        if(first>second) return first;
        return second;
    }

    Node* findNode(Node *source, Node* p, int depth){
        if (source == nullptr) return nullptr;
        if (sameNode(source,p)) return source;

        int level = (depth+1) % 3;

        if ((p->localpoint.getvalue(depth))<(source->localpoint.getvalue(depth))){
            return findNode(source->left,p,level);
        }
        else{
            return findNode(source->right,p,level);
        }
    }

    Node* findNode(Node* target_node){
        return findNode(root, target_node, 0);
    }

    Node* chooseRandomNode(){
        int size = allNodes.size();
        std::random_device dev;
        std::mt19937 rng(dev());
        int starting_value = 0;
        if(!includeCore) starting_value = 1;
        std::uniform_int_distribution<std::mt19937::result_type> distribution_x(starting_value,size-1);
        int chosenIndex = distribution_x(rng);
        Node* temp = newNode(allNodes[chosenIndex]);
        Node* returnNode = findNode(temp);
        delete temp;
        return returnNode;
    }

    //Getters

    int getNodeCount(){
        return allNodes.size();
    }

    int getEntityCount(){
        return entityCount;
    }
    int getWidth(){
        return width;
    }       

    int getHeight(){
        return height;
    }

    int getLength(){
        return length;
    }

    Node* getRootNode(){
        return root;
    }

protected:
    std::vector<std::array<int,3> > allNodes;
    
private:
    Node* root;
    int entityCount;
    bool includeCore;
};