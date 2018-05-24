// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <vector>
/**
 * @class Node
 * @brief Class representing a tree node for path planning
 * @author Thomas Collins
 * @version 1.0
 * @date 04/11/2015
 * Contact: collinst@usc.edu
 * Created on: 04/11/2015
 */
class REBOTS_API Node {
private:
    int nodeName; /**< name of node */
    int dimension; /**< dimension of node */
    std::vector<float> state; /**< vector of state values */
    bool isFree; /**< is in free C-space */
public:
    /**
     * @brief destructor
     */
    ~Node();
    /**
     * @brief default constructor
     */
    Node();
    /**
     * @brief constructor with arguments
     * @param s state vector
     * @param f is in free space
     * @param n name
     * @param d node d
     */
    Node(std::vector<float>& s, bool f, int n, int d);
    /**
     * @brief setter for state
     * @param s state vector
     */
    void setState(const std::vector<float>& s);
    /**
     * @brief setter for name
     * @param n name
     */
    void setName(const int n);
    /**
     * @brief setter for isFree
     * @param f isFree value
     */
    void setIsFree(const bool f);
    /**
     * @brief set dimension
     * @param dimension
     */
    void setDimension(const int d);
    /**
     * @brief getter for state
     * @return state values
     */
    std::vector<float>& getState();
    /**
     * @brief getter for name
     * @return name
     */
    int getName();
    /**
     * @brief getter for isFree
     * @return isFree
     */
    bool getIsFree();
    /**
     * @brief getter for dimension
     * @return dimension of node
     */
    int getDimension();
};
