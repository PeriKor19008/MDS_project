//
// Created by Gregory on 12/3/2021.
//

#ifndef MDS_PROJECT_QUADTREE_HPP
#define MDS_PROJECT_QUADTREE_HPP

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct DimensionSpace
{
    float start;
    float end;
public:
    DimensionSpace(float start, float end);
    DimensionSpace() {};
};

struct QuadLeaf
{
    bool used = false;
    vector<float> contents;
    QuadLeaf() {};
    //QuadLeaf(vector<int> numbers);
    QuadLeaf(vector<DimensionSpace> boundrySpace);
    vector<DimensionSpace> boundrySpace;
public:
    void printContent();
};

struct QuadNode
{
    vector<float> contents;
    QuadNode() {};
    QuadNode(vector<float> values);
    vector<QuadLeaf> leaves;
};

class Quadtree
{
    int dimension;
    QuadNode head;
    vector<Quadtree> subtrees;
    vector<DimensionSpace> boundrySpace;
public:
    vector<vector<DimensionSpace>> makeNewDimensionSpaces();
    Quadtree(int dimensions, vector<DimensionSpace> boundrySpace);
    Quadtree(int dimensions);
    void print();
    void print(QuadNode start);
    void insert(vector<float> number);
    void delete_element(vector<int> number);
    void update(QuadLeaf &leaf);
    void kNN(vector<int> number);
};

#endif //MDS_PROJECT_QUADTREE_HPP