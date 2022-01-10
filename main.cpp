#include "sandbox.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono;

void ClearScreen(){
    for (int i=0; i<100; i++) std::cout << '\n';
}

int main(int argc, const char * argv[]) {
    // std::array<int, 3> a1 = {3,6,1} ;
    // std::array<int, 3> a2 = {2,5,2} ;
    // Node* temp1 = newNode(a1); 
    // KDtree tree3d(temp1);
    // tree3d.insert(a1);
    
    // for(int i=0; i<5; i++){
    //     Node* p = tree3d.generateRandomNode(a1,8);
    //     tree3d.insert(p->localpoint.getCoords());
    // }
    // tree3d.insert(a2);

    // std::array<int, 3> a3 = {1,7,4} ;
    // std::array<int, 3> a4 = {5,10,3} ;
    // std::array<int, 3> a5 = {10,9,1} ;
    // std::array<int, 3> a6 = {5,9,3} ;
    // std::array<int, 3> a7 = {8,1,2} ;
    // tree3d.insert(a3);
    // tree3d.insert(a4);
    // tree3d.insert(a5);
    // tree3d.insert(a6);
    // tree3d.insert(a7);

    // tree3d.print();
    // std::cout<<tree3d.inRange(a1,8)<<std::endl;

    // //tree3d.printNode(tree3d.findMin(tree3d.getRootNode(),2));
    // tree3d.deleteNode(tree3d.getRootNode());
    // tree3d.print();

    // for(int i=0;i<tree3d.getNodeCount();i++){
    //      tree3d.printNode(tree3d.allNodes.at(i));
    // }
    // std::array<int, 3> center = {10/2,10/2,10/2};
    // Node* temp = newNode(center);
    // Sandbox sandbox(temp);
    // Node* core = sandbox.getCore();
    // sandbox.hitparticle(core);

    // for(int i=0; i<1000; i++){
    //     sandbox.hitparticle(sandbox.chooseRandomNode());
    //     sandbox.print();
    //     std::cout<<'\n';
    //     std::cout<<'\n';
    //     //sleep_for(milliseconds(500));
    //     //ClearScreen();
    //     sandbox.printVector();
    //     std::cout<<"Iteration no: "<<i<<std::endl;
        

    //     if(sandbox.getEntityCount()==1){
    //         std::cout<<"Population died off"<<std::endl;
    //         //std::cout<<"Restarting";
    //         //sandbox.hitparticle(core);
    //         break;
    //     }
    // }

    // std::cout<<"Number of entities: "<<sandbox.getEntityCount()<<std::endl;
    // std::cout<<"Number of nodes: "<<sandbox.getNodeCount()<<std::endl;
    

    int n, flagPrint;
    std::cout<<"Nuclear Fission Model"<<'\n';
    std::cout<<"Number of iterations: ";
    //n=1;
    std::cin>>n;
    std::cout<<"Type 1 for real-time progress, type 0 for instant results: ";
    //flagPrint = 1;
    std::cin>>flagPrint;

    bool flagLoop = true;
    std::array<int, 3> center = {10/2,10/2,10/2};
    Node* core = newNode(center);
    Sandbox sandbox(core);
    sandbox.hitparticle(core);
    do{

        for(int i=0; i<n; i++){
            sandbox.hitparticle(sandbox.chooseRandomNode());

            if(flagPrint){
                sandbox.print();
                sleep_for(milliseconds(500));
                ClearScreen();
                //sandbox.printVector();
                std::cout<<"Iteration no: "<<i+1<<std::endl;
            }
            
            if(sandbox.getEntityCount()==1){
                std::cout<<"Population died off"<<std::endl;
                break;
            }
        }
        sandbox.print();
        std::cout<<"Simulation has ended"<<'\n';


        //User input
        bool loopAsk = false;
        do{
            std::cout<<"[0] Continue simulation"<<'\n';
            std::cout<<"[1] End simulation"<<'\n';
            std::cout<<"Selection: ";
            int selection;
            std::cin>>selection;
            //selection = 1;
            switch(selection){
                case 0:{
                    std::cout<<"Additional number of iterations: ";
                    std::cin>>n;
                    break;
                }
                case 1:{
                    flagLoop = false;
                    break;
                }
                default:{
                    loopAsk = true;
                    std::cout<<"Unknown input, please try again"<<'n';
                }
            }
        }
        while(loopAsk);
    }
    while(flagLoop);

    return 0;
}

