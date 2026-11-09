#include "BinaryTree.h"
#include<vector>
template <typename T>
void BinaryTree<T>::setDepth(int _depth)
{
	 if (depth < 0)
	 {
		 throw std::invalid_argument("negative depth");
	 }

	 this->_depth = _depth;
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
	else {
		_tree[level][position] = value;
	}
}
template <typename T>
T BinaryTree<T>::getNode(int level, int position)const
{
	if (level < 0 || level > _depth || position < 0 || position > level)
	{
		throw std::out_of_range("invalid indices");
	}
	else
	{
		return _tree[level][position]:
	}
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