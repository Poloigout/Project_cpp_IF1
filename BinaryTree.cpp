// BinaryTree.cpp
#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP

#include "BinaryTree.h"

template <typename T>
void BinaryTree<T>::setDepth(int _depth)
{
	if (_depth < 0)
		throw std::invalid_argument("negative depth");

	this->_depth = _depth;
	_tree.resize(_depth + 1);
	for (int i = 0; i <= _depth; ++i)
		_tree[i].resize(i + 1);
	_tree.shrink_to_fit();
}

template <typename T>
void BinaryTree<T>::setNode(int level, int position, T value)
{
	if (level < 0 || level > _depth || position < 0 || position > level)
		throw std::out_of_range("invalid indices");
	_tree[level][position] = value;
}

template <typename T>
T BinaryTree<T>::getNode(int level, int position) const
{
	if (level < 0 || level > _depth || position < 0 || position > level)
		throw std::out_of_range("invalid indices");
	return _tree[level][position];
}

template <typename T>
void BinaryTree<T>::display() const
{
	// 1) list
	for (int level = 0; level <= _depth; ++level)
	{
		for (int position = 0; position <= level; ++position)
			std::cout << _tree[level][position] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// 2) Tree
	const int u = 3;
	const int width = 2 * _depth * u + 8;

	for (int level = 0; level <= _depth; ++level)
	{
		std::string line(width, ' ');
		std::string branches(width, ' ');

		for (int position = 0; position <= level; ++position)
		{
			int x = (2 * position - level + _depth) * u;

			std::ostringstream oss;
			oss << _tree[level][position];
			line.replace(x, oss.str().size(), oss.str());

			if (level < _depth)
			{
				branches[x - 1] = '/';
				branches[x + 1] = '\\';
			}
		}
		std::cout << line << std::endl;
		if (level < _depth)
			std::cout << branches << std::endl;
	}
}

#endif