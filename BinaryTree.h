#pragma once
#include <vector>
template <typename T>
class BinaryTree {
private:
	std::vector<std::vector<T>> _tree;
	
public:
	int _depth;
	BinaryTree<T>;

	void setDepth(int n) const {
		_depth = n;
		_tree.resize(n);
		for (int i = 1;i < n;i++) {
			_tree[i].resize(1 << i);
		}

	}
	void setNode(int i, int j, T const&val)const {
		_tree[i][j] = val;
	};
	Tconst& getNode(int i, int j) const {
		return _tree[i][j];
	};
	void display()(){};
};