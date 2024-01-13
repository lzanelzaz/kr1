#include<iostream>

using namespace std;

template <class KeyType, class DataType>
class BSTree {

private:
	size_t size = 0; // ���������� ��������� � ������

protected:

	class Node { // ���� ������

	public:
		KeyType key; // ����
		DataType value; // ��������
		Node* leftPtr = nullptr, // ��������� �� ������ �������
			* rightPtr = nullptr; // ��������� �� ������� �������

		Node(const KeyType& key, const DataType& value) : key(key), value(value) {}
	};

	Node* head = nullptr; // ������ ������

public:

	BSTree(); // ����������� ������� ������

	~BSTree(); // ����������

	size_t getSize() const; // ����� ������� ������ (���������� �����)

	void clear(); // ������� ������ (�������� ���� �����)

	bool isEmpty() const; // �������� ������ �� �������

	const DataType& find(const KeyType& key) const; // ����� ������ � �������� ������

	void insert(const KeyType& key, const DataType& value); // ��������� � ������ ������ ���� � �������� ������ � �������

	void removeByKey(const KeyType& key); // �������� �� ������ ���� � �������� ������

	void printTree(); // ����� ��������� ������ �� �����

	void Lt_Rt_t(); // ����� ����� � ������ �� ����� Lt  Rt  t, � ����� ������ � ������� ������

	const KeyType& predecessorKey(const KeyType& key); // ����� ��� ��������� ����� ����������� �� �������� ����� � ������

	class rIterator { // �������� ��������
	private:
		const Node* current; // ��������� �� ������� ����
		BSTree* tree; // ��������� �� ������������ ������

	public:
		rIterator(BSTree* tree) { // ������� ��������� ��� ���������� ������
			this->tree = tree;
			if (tree == nullptr) {
				current = nullptr;
			}
			else {
				current = tree->findMaxNode(tree->head); // ������� ���������� ���� ������
			}
		}

		DataType& operator* () { // /������ � ������ �������� ��������
			if (current == nullptr) {
				throw exception("����� �� ������� ������");
			}
			return current->value;
		}

		rIterator& operator ++() { // �������� ���������� ���������
			if (current != nullptr) {
				current = tree->predecessor(current);
			}
			return *this;
		}

		bool operator == (const rIterator& other) { // �������� ���������
			return current == other.current;
		}

		bool operator != (const rIterator& other) { // �������� �����������
			return current != other.current;
		}
	};

	rIterator rbegin() {
		return rIterator(this);
	}

	rIterator rend() {
		return rIterator(nullptr);
	}

private:

	void clear(Node*& node); // ������� ����

	const Node* findNode(const Node* node, const KeyType& key) const { // ���� ���������� ���� � �������� ���� ��� ��� �����
		if (node == nullptr) {
			throw exception("���� �� ����������");
		}
		if (node->key == key) {
			return node;
		}
		else if (key < node->key) {
			return findNode(node->leftPtr, key);
		}
		else {
			return findNode(node->rightPtr, key);
		}
	}

	const Node* findMaxNode(const Node* node) const { // ���� ������������ ���� � �������� ���� ��� ��� �����
		if (node == nullptr) {
			throw exception("���� �� ����������");
		}
		while (node->rightPtr != nullptr) { // ����������� ���� �� ������ ������� ������ ����
			node = node->rightPtr;
		}
		return node;
	}

	const Node* rParent(const Node* node, const Node* nodeByKey) { // ���� �������� ��������� ����
		if (node == nodeByKey) { // 2. ����� ��������, �����������
			return nullptr;
		}
		else if (nodeByKey->key > node->key) {
			const Node* rp = rParent(node->rightPtr, nodeByKey);
			if (rp != nullptr) {
				return rp;  // 3. ����� ��������, �����������
			}
			else {
				return node; // 1. ����� ��������, �����������
			}
		}
		else {
			return rParent(node->leftPtr, nodeByKey);
		}
	}

	const Node* predecessor(const Node* node) { // ���������� �� �������� ����� ���� ��� ��������� ����
		if (node->leftPtr != nullptr) {
			return findMaxNode(node->leftPtr); // ���� ������������ ���� � �������� ���� ��� ��� �����
		}
		else {
			return rParent(head, node); // ���� �������� ��������� ����
		}
	}

	void insert(Node*& node, const KeyType& key, const DataType& value); // ��������� ������ ���� � �������� ������ � ������� � �������� ������� ��������� ������������� ���� ��� ��� �����

	void removeByKey(Node*& node, const KeyType& key); // �������� ��������� ���� ��� ��� ������� � �������� ������

	void printNode(const Node* node, const size_t& level);  // ����� �� ����� ��������� ����

	void Lt_Rt_t(const Node* node); // ����� ��������� ���� � ��� ����� � ������ �� ����� Lt  Rt  t, � ����� ������ � ������� ������
};

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::clear(Node*& node) { // �������� ��������� ���� � ��� �����
	if (node == nullptr) {
		return;
	}
	clear(node->leftPtr);  // ������� ����� �����
	clear(node->rightPtr); // ������� ����� ������
	delete node; // ������� ��� ����
	node = nullptr; // ������� ������ �� ��������� ����
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::insert(Node*& node, const KeyType& key, const DataType& value) {// ��������� ������ ���� � �������� ������ � ������� � �������� ������� ��������� ������������� ���� ��� ��� �����
	if (node == nullptr) { // ����� ����� ��������� ����� ��� ����
		node = new Node(key, value);
		return;
	}
	if (node->key == key) {
		throw exception("���� ��� ����������");
	}
	else if (key < node->key) {
		insert(node->leftPtr, key, value);
	}
	else {
		insert(node->rightPtr, key, value);
	}
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::removeByKey(Node*& node, const KeyType& key) { // �������� ��������� ���� ��� ��� ������� � �������� ������
	if (node == nullptr) {
		throw exception("���� �� ������");
	}
	if (node->key == key) { // ����� ���� ��� ��������
		if (node->leftPtr == nullptr && node->rightPtr == nullptr) { // ���� ��� ����� - ������ �������
			delete node;
			node = nullptr;
		}
		else if (node->leftPtr == nullptr) { // ���� ��� ������� ����� - �������� �� ����� ���������� ���� ������� �������
			Node* temp = node;
			node = node->rightPtr;
			delete temp;
		}
		else if (node->rightPtr == nullptr) { // ���� ��� ������� ������ - �������� �� ����� ���������� ���� ������ �������
			Node* temp = node;
			node = node->leftPtr;
			delete temp;
		}
		else { // ��� ������� ������������
			const Node* temp = findMaxNode(node->leftPtr); // ������� ������������� ������� ���������� ����
			node->value = temp->value;
			node->key = temp->key;
			removeByKey(node->leftPtr, temp->key); // ������� ���������� �������
		}
	}
	else if (key < node->key) {
		removeByKey(node->leftPtr, key);
	}
	else {
		removeByKey(node->rightPtr, key);
	}
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::printNode(const Node* node, const size_t& level) { // ����� �� ����� ��������� ����
	if (node == nullptr) {
		return;
	}
	printNode(node->rightPtr, level + 1);
	for (int i = 0; i < level; i++) {
		cout << "   ";
	}
	cout << node->key << endl;
	printNode(node->leftPtr, level + 1);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::Lt_Rt_t(const Node* node) {
	if (node == nullptr) {
		return;
	}
	Lt_Rt_t(node->leftPtr); // ������� ��� ���� �����
	Lt_Rt_t(node->rightPtr); // ����� ��� ���� ������
	cout << node->key << " "; // ������� ������� ����
}

template <class KeyType, class DataType>
BSTree<KeyType, DataType>::BSTree() {}

template <class KeyType, class DataType>
BSTree<KeyType, DataType>::~BSTree() {
	clear();
}

template<class KeyType, class DataType>
size_t BSTree<KeyType, DataType>::getSize() const {// ����� ������� ������ (���������� �����)
	return size;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::clear() { // ������� ������ (�������� ���� �����)
	size = 0;
	clear(head); // ������� �������� ���� � ��� �����
}

template <class KeyType, class DataType>
bool BSTree<KeyType, DataType>::isEmpty() const { // �������� ������ �� �������
	return head == nullptr; // ��������� ������� ���� �� ������ ���� (���������)
}

template<class KeyType, class DataType>
const DataType& BSTree<KeyType, DataType>::find(const KeyType& key) const { // ����� ������ � �������� ������
	return findNode(head, key)->value;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::insert(const KeyType& key, const DataType& value) { // ��������� � ������ ������ ���� � �������� ������ � �������
	insert(head, key, value);
	size++;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::removeByKey(const KeyType& key) { // �������� �� ������ ���� � �������� ������
	removeByKey(head, key);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::printTree() { // ����� ��������� ������ �� �����
	printNode(head, 0);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::Lt_Rt_t() {  // ����� ����� � ������ �� ����� Lt  Rt  t, � ����� ������ � ������� ������
	Lt_Rt_t(head);
	cout << endl;
}

template<class KeyType, class DataType>
const KeyType& BSTree<KeyType, DataType>::predecessorKey(const KeyType& key) { // ����� ��� ��������� ����� ����������� �� �������� ����� � ������
	const Node* nodeForKey = findNode(head, key); // ������� ���� �� �����
	const Node* foundNode = predecessor(nodeForKey); // ������� ��������������� ��� ���������� ����
	if (foundNode == nullptr) {
		throw exception("������� ���� �� ����������");
	}
	return foundNode->key;
}
