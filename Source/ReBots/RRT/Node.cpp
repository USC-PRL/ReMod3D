// Fill out your copyright notice in the Description page of Project Settings.

 
#include "Node.h"

/**
 * @brief destructor
 */
Node::~Node(){}
/**
 * @brief default constructor
 */
Node::Node() {
    this->isFree = false;
    this->nodeName = -1;
    this->dimension = -1;
};
/**
 * @brief constructor with arguments
 * @param s state vector
 * @param f is in free space
 * @param n name
 * @param d node d
 */
Node::Node(std::vector<float>& s, bool f, int n, int d) {
    this->state = s;
    this->isFree = f;
    this->nodeName = n;
    this->dimension = d;
}
/**
 * @brief setter for state
 * @param s state vector
 */
void Node::setState(const std::vector<float>& s) {
    this->state = s;
    this->dimension = state.size();
}
/**
 * @brief setter for name
 * @param n name
 */
void Node::setName(const int n) {
    this->nodeName = n;
}
/**
 * @brief setter for isFree
 * @param f isFree value
 */
void Node::setIsFree(const bool f) {
    this->isFree = f;
}
/**
 * @brief set dimension
 * @param dimension
 */
void Node::setDimension(const int d) {
    this->dimension = d;
}
/**
 * @brief getter for state
 * @return state values
 */
std::vector<float>& Node::getState() {
    return this->state;
}
/**
 * @brief getter for name
 * @return name
 */
int Node::getName() {
    return this->nodeName;
}
/**
 * @brief getter for isFree
 * @return isFree
 */
bool Node::getIsFree() {
    return this->isFree;
}
/**
 * @brief getter for dimension
 * @return dimension of node
 */
int Node::getDimension() {
    return this->dimension;
}
