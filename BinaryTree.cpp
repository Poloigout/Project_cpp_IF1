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
