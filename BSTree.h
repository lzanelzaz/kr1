#pragma once

#include<iostream>
#include <stack>

using namespace std;

template <class KeyType, class DataType>
class BSTree {

private:
	size_t _size = 0;

protected:

	class Node {

	public:

		KeyType _key;
		DataType _value;
		Node* _leftPtr = nullptr,
			* _rightPtr = nullptr;

		Node(const KeyType& key, const DataType& value) : _key(key), _value(value) {}
	};

	Node* head = nullptr;

public:

	BSTree();

	~BSTree();

	size_t getSize() const;

	void clear();

	bool isEmpty() const;

	const DataType& find(const KeyType& key) const;

	void insert(const KeyType& key, const DataType& value);

	void removeByKey(const KeyType& key);

	void printTree();

	void Lt_Rt_t();

	const KeyType& predecessorKey(const KeyType& key);

	class rIterator {
	private:
		stack<const Node*> q;

		void initialize(const Node* node) {
			if (node == nullptr) {
				return;
			}
			initialize(node->_leftPtr);
			q.push(node);
			initialize(node->_rightPtr);
		}

	public:

		rIterator(const BSTree& tree) {
			initialize(tree.head);
		}

		bool hasNext() {
			return !q.empty();
		}

		const KeyType& operator* () {
			if (!hasNext()) {
				throw exception("Iterator is out of range");
			}
			return q.top()->_key;
		}

		rIterator& operator ++() {
			if (!hasNext()) {
				throw exception("Iterator is out of range");
			}
			q.pop();
			return *this;
		}

		bool operator == (const rIterator& other) {
			return q == other.q;
		}
	};

	rIterator rbegin() {
		return rIterator(*this);
	}

private:

	void clear(Node*& node);

	const Node* findNode(const Node* node, const KeyType& key) const {
		if (node == nullptr) {
			throw exception("Key does not exist");
		}
		if (node->_key == key) {
			return node;
		}
		else if (key < node->_key) {
			return findNode(node->_leftPtr, key);
		}
		else {
			return findNode(node->_rightPtr, key);
		}
	}

	const Node* findMaxNode(const Node* node) const {
		if (node == nullptr) {
			throw exception("Node does not exist");
		}
		while (node->_rightPtr != nullptr) {
			node = node->_rightPtr;
		}
		return node;
	}

	const Node* rParent(const Node* node, const Node* nodeByKey) {
		if (node == nodeByKey) {
			return nullptr;
		}
		else if (nodeByKey->_key > node->_key) {
			const Node* rp = rParent(node->_rightPtr, nodeByKey);
			if (rp != nullptr) {
				return rp;
			}
			else {
				return node;
			}
		}
		else {
			return rParent(node->_leftPtr, nodeByKey);
		}
	}

	void insert(Node*& node, const KeyType& key, const DataType& value);

	void removeByKey(Node*& node, const KeyType& key);

	void printNode(const Node* node, const size_t& level);

	void Lt_Rt_t(const Node* node);
};

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::clear(Node*& node) {
	if (node == nullptr) {
		return;
	}
	clear(node->_leftPtr);
	clear(node->_rightPtr);
	delete node;
	node = nullptr;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::insert(Node*& node, const KeyType& key, const DataType& value) {
	if (node == nullptr) {
		node = new Node(key, value);
		return;
	}
	if (node->_key == key) {
		throw exception("Key already exists");
	}
	else if (key < node->_key) {
		insert(node->_leftPtr, key, value);
	}
	else {
		insert(node->_rightPtr, key, value);
	}
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::removeByKey(Node*& node, const KeyType& key) {
	if (node == nullptr) {
		return;
	}
	if (node->_key == key) {
		if (node->_leftPtr == nullptr && node->_rightPtr == nullptr) {
			delete node;
			node = nullptr;
		}
		else if (node->_leftPtr == nullptr) {
			Node* temp = node;
			node = node->_rightPtr;
			delete temp;
		}
		else if (node->_rightPtr == nullptr) {
			Node* temp = node;
			node = node->_leftPtr;
			delete temp;
		}
		else {
			const Node* temp = findMaxNode(node->_leftPtr);
			node->_value = temp->_value;
			node->_key = temp->_key;
			removeByKey(node->_leftPtr, temp->_key);
		}
	}
	else if (key < node->_key) {
		removeByKey(node->_leftPtr, key);
	}
	else {
		removeByKey(node->_rightPtr, key);
	}
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::printNode(const Node* node, const size_t& level) {
	if (node == nullptr) {
		return;
	}
	printNode(node->_rightPtr, level + 1);
	for (int i = 0; i < level; i++) {
		cout << "   ";
	}
	cout << node->_key << endl;
	printNode(node->_leftPtr, level + 1);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::Lt_Rt_t(const Node* node) {
	if (node == nullptr) {
		return;
	}
	Lt_Rt_t(node->_leftPtr);
	Lt_Rt_t(node->_rightPtr);
	cout << node->_key << " ";
}

template <class KeyType, class DataType>
BSTree<KeyType, DataType>::BSTree() {}

template <class KeyType, class DataType>
BSTree<KeyType, DataType>::~BSTree() {
	clear();
}

template<class KeyType, class DataType>
size_t BSTree<KeyType, DataType>::getSize() const {
	return _size;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::clear() {
	_size = 0;
	clear(head);
}

template <class KeyType, class DataType>
bool BSTree<KeyType, DataType>::isEmpty() const {
	return head == nullptr;
}

template<class KeyType, class DataType>
const DataType& BSTree<KeyType, DataType>::find(const KeyType& key) const {
	return findNode(head, key)->_value;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::insert(const KeyType& key, const DataType& value) {
	insert(head, key, value);
	_size++;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::removeByKey(const KeyType& key) {
	removeByKey(head, key);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::printTree() {
	printNode(head, 0);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::Lt_Rt_t() {
	Lt_Rt_t(head);
	cout << endl;
}

template<class KeyType, class DataType>
const KeyType& BSTree<KeyType, DataType>::predecessorKey(const KeyType& key) {
	const Node* nodeForKey = findNode(head, key);
	if (nodeForKey->_leftPtr != nullptr) {
		return findMaxNode(nodeForKey->_leftPtr)->_key;
	}
	else {
		return rParent(head, nodeForKey)->_key;
	}
}
