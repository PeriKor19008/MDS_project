#include "KDtree.hpp"
#include <vector>
#include <math.h>

//////////////////////
///INSERT
node* insertNode(node* root, node* point,int depth){
    //dimensions
    int k=point->coordinates.size();
    //tree empty
    if(root==NULL)
        return point;
    int dimension=depth%k;

    if(point->coordinates.at(dimension)<=(root->coordinates.at(dimension)))
        root->left= insertNode(root->left,point,depth+1);
    else
        root->right= insertNode(root->right,point,depth+1);
    return root;
}

//interface like function that calls insertNode with depth==0
node* insert(node* root,vector<int> point,int pos){

    return insertNode(root, createNode(point,pos),0);
}

node* createNode(vector<int>point,int pos){

    node* tmp=new node;
    for(int i=0;i<point.size();i++)
        tmp->coordinates.push_back(point.at(i));
    tmp->left=tmp->right=NULL;
    tmp->pos=pos;
    return tmp;

}


////////////////////////
///SEARCH
bool areSame(node* point1,node* point2){
    for(int i=0;i<point1->coordinates.size();i++){
        if(point1->coordinates.at(i)!=point2->coordinates.at(i))
            return false;
    }
    return true;
}

node* searchNode(node* root,node* point,int depth){
    if(root==NULL)
        return NULL;
    if(areSame(point,root))
        return root;
    int dimensions=depth%(point->coordinates.size());
    if(point->coordinates.at(dimensions)<root->coordinates.at(dimensions))
        return searchNode(root->left,point,depth+1);
    else
        return searchNode(root->right,point,depth+1);

}

//interface like function that calls searchNode with depth==0
node* search(node* root,vector<int>point){
    int size=root->coordinates.size();
    point.resize(size,0);
    node* Point= createNode(point,-1);
    return searchNode(root, Point,0);
}

int searchNode(node* root, node* point,int depth,int hits){
    if(root==NULL)
        return hits;
    if(areSame(point,root)){
        hits++;
        return searchNode(root->left,point,depth+1,hits);
    }
    int dimensions=depth%(point->coordinates.size());
    if(point->coordinates.at(dimensions)<root->coordinates.at(dimensions))
        return searchNode(root->left,point,depth+1,hits);
    else
        return searchNode(root->right,point,depth+1,hits);
}

int searchAll(node* root,vector<int>point){
    int size=root->coordinates.size();
    point.resize(size,0);
    node* Point= createNode(point,-1);
    return searchNode(root, Point,0,0);
}



//////////////////////////
///DELETE
node* findMin(node* root,int d,int depth){
    if (root==NULL)
        return NULL;
    int dimension=depth%root->coordinates.size();
    node* tmpL=findMin(root->left,d,depth+1);
    if(dimension==d){
        if(root->left==NULL)
            return root;


        if((root->coordinates.at(d))<tmpL->coordinates.at(d))
            return root;

        return tmpL;
    }
    node* tmpR=findMin(root->right,d,depth+1);
    if((root->coordinates.at(d)<tmpL->coordinates.at(d))&&
       (root->coordinates.at(d)<tmpR->coordinates.at(d))){
        return root;
    }
    else if((tmpL->coordinates.at(d)<tmpR->coordinates.at(d))&&
            (tmpL->coordinates.at(d)<root->coordinates.at(d))){
        return tmpL;
    }
    else
        return tmpR;
}

///interface like function that calls findMin with depth==0
node* Min(node* root,int d){
    findMin(root,d,0);
}


///////////////////////////
//NearestNeighbor SEARCH

//returns the squared distance between two points (squared to save cpu cycles)
double dist(node* n1,node* n2){
    double dist=0;
    for(int i=0;i<n1->coordinates.size();i++){
        dist=dist+pow(((n1->coordinates.at(i))-(n2->coordinates.at(i))),2);
    }
    return dist;
}

node* closest(node* n1,node* n2,node* point){
    if(dist(n1,point)<dist(n2,point))
        return n1;
    else
        return n2;
}

node* NN_search(node* root,node* point,int depth){

    if(root==NULL)
        return NULL;
    point->coordinates.resize(root->coordinates.size(),0);
    node* nextBranch=NULL;
    node* otherBranch=NULL;
    int d=depth%point->coordinates.size();
    node* best=NULL;
    node* tmp=NULL;

    if(point->coordinates.at(d)<root->coordinates.at(d)){
        nextBranch=root->left;
        otherBranch=root->right;
    }
    else{
        nextBranch=root->right;
        otherBranch=root->left;
    }
    if(nextBranch==NULL)
        return root;
    tmp= NN_search(nextBranch,point,depth+1);
    best= closest(tmp,root,point);

    double radius=dist(best,point);
    double distance=point->coordinates.at(d)-root->coordinates.at(d);
    if(radius>distance*distance){
        if(otherBranch==NULL)
            return root;
        tmp= NN_search(otherBranch,point,depth+1);
        best= closest(tmp,root,point);
    }
    return best;
}