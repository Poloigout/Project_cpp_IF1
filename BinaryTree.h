// BinaryTree.h
#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

template <typename T>
class BinaryTree
{
public:
	void setDepth(int _depth);
	void setNode(int level, int position, T value);
	T getNode(int level, int position) const;
	void display() const;

private:
	std::vector<std::vector<T>> _tree;
	int _depth = 0;
};

#include "BinaryTree.cpp"