#include "engine/box/rectangle.h"

template<typename T>
Rectangle<T>::Rectangle(double x, double y){
    this->relVertices.push_back(point(0, 0));
    this->relVertices.push_back(point(x, 0));
    this->relVertices.push_back(point(x, y));
    this->relVertices.push_back(point(0, y));
}

//Bottom-left point first; then counter clockwise
// template<typename T>
// Rectangle<T>::Rectangle(int x1, int x2, int y1, int y2){
//     if (x1<x2)  //x1 is minx
//     {
//         if (y1<y2)  //y1 is miny
//         {
//             this->relVertices.push_back(point(x1, y1));
//             this->relVertices.push_back(point(x2, y1));
//             this->relVertices.push_back(point(x2, y2));
//             this->relVertices.push_back(point(x1, y2));
//         }else{  //y2 is miny
//             this->relVertices.push_back(point(x1, y2));
//             this->relVertices.push_back(point(x2, y2));
//             this->relVertices.push_back(point(x2, y1));
//             this->relVertices.push_back(point(x1, y1));
//         }
//     }else{
//         if (y1<y2)
//         {
//             this->relVertices.push_back(point(x2, y1));
//             this->relVertices.push_back(point(x1, y1));
//             this->relVertices.push_back(point(x1, y2));
//             this->relVertices.push_back(point(x2, y2));
//         }else{
//             this->relVertices.push_back(point(x2, y2));
//             this->relVertices.push_back(point(x1, y2));
//             this->relVertices.push_back(point(x1, y1));
//             this->relVertices.push_back(point(x2, y1));
//         }
//     }
    
// }

template<typename T>
Collision<T> Rectangle<T>::checkCollision(Rectangle<T>* r){
    point* this_pos = this->getPos();
    point* that_pos = r->getPos();

    Collision<T> coll = Collision<T>();

    int xcol1 = (this->relVertices.at(1).first + this_pos->first)
              - (r->getVertices().at(0).first + that_pos->first);

    int xcol2 = (r->getVertices().at(1).first + that_pos->first)
              - (this->relVertices.at(0).first + this_pos->first);
    int xcol = 0;

    int ycol1 = (this->relVertices.at(2).second + this_pos->second)
              - (r->getVertices().at(1).second + that_pos->second);

    int ycol2 = (r->getVertices().at(2).second + that_pos->second)
              - (this->relVertices.at(1).second + this_pos->second);

    int ycol = 0;

    std::cout<< xcol1 << " " << xcol2 << " " << ycol1 << " "<<ycol2<<"\n";
    if(xcol1 > 0 && xcol2 > 0){
        xcol1 < xcol2 ? (xcol = xcol1) : (xcol = -xcol2);
        // xcol = std::min(xcol1,xcol2);
    }
    if (ycol1 > 0 && ycol2 >0)
    {
        ycol1 < ycol2 ? (ycol = ycol1) : (ycol = -ycol2);
        // ycol = std::min(ycol1, ycol2);
    }
    
    coll.collisionVector = std::pair(xcol, ycol);
    if (ycol !=0 && xcol!=0)
    {
        coll.colliding = this->getOwner();
        coll.collided = r->getOwner();
        return coll;
    }else{
        coll.colliding = NULL;
        return coll;
    }

}