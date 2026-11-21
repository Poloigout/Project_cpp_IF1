#pragma once
#include <vector>
template <typename T>
class BinaryTree
{
public:
	void setDepth(int _depth);
	void setNode(int level, int position, T value);
	T getNode(int level, int position) const;
	void display() const;

private:
	std::vector<vector<T>> _tree;
	int _depth = 0;
};

template <typename T>
void BinaryTree<T>::setDepth(int depth)
{
	if (depth < 0)
	{
		throw std::invalid_argument("negative depth");
	}

	_depth = depth;
	_tree.resize(_depth + 1);
	for (int i = 0; i <= _depth; ++i)
	{
		_tree[i].resize(i + 1);
	}
}

template <typename T>
void BinaryTree<T>::setNode(int level, int position, T value)
{
	if (level < 0 || level > _depth || position < 0 || position > level)
	{
		throw std::out_of_range("invalid indices");
	}
	_tree[level][position] = value;
}

template <typename T>
T BinaryTree<T>::getNode(int level, int position) const
{
	if (level < 0 || level > _depth || position < 0 || position > level)
	{
		throw std::out_of_range("invalid indices");
	}
	return _tree[level][position];
}

template <typename T>
void BinaryTree<T>::display() const
{
	for (int level = 0; level <= _depth; ++level)
	{
		for (int position = 0; position <= level; ++position)
			std::cout << _tree[level][position] << " ";
		std::cout << std::endl;
	}
}