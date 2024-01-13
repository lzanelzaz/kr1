#include<iostream>

using namespace std;

template <class KeyType, class DataType>
class BSTree {

private:
	size_t size = 0; // Количество элементов в дереве

protected:

	class Node { // Узел дерева

	public:
		KeyType key; // Ключ
		DataType value; // Значение
		Node* leftPtr = nullptr, // Указатель на левого ребенка
			* rightPtr = nullptr; // Указатель на правого ребенка

		Node(const KeyType& key, const DataType& value) : key(key), value(value) {}
	};

	Node* head = nullptr; // Корень дерева

public:

	BSTree(); // конструктор пустого дерева

	~BSTree(); // деструктор

	size_t getSize() const; // опрос размера дерева (количества узлов)

	void clear(); // очистка дерева (удаление всех узлов)

	bool isEmpty() const; // проверка дерева на пустоту

	const DataType& find(const KeyType& key) const; // поиск данных с заданным ключом

	void insert(const KeyType& key, const DataType& value); // включение в дерево нового узла с заданным ключом и данными

	void removeByKey(const KeyType& key); // удаление из дерева узла с заданным ключом

	void printTree(); // вывод структуры дерева на экран

	void Lt_Rt_t(); // обход узлов в дереве по схеме Lt  Rt  t, и вывод ключей в порядке обхода

	const KeyType& predecessorKey(const KeyType& key); // поиск для заданного ключа предыдущего по значению ключа в дереве

	class rIterator { // Обратный итератор
	private:
		const Node* current; // Указатель на текущий узел
		BSTree* tree; // Указатель на родительское дерево

	public:
		rIterator(BSTree* tree) { // Создаем указатель для указанного дерева
			this->tree = tree;
			if (tree == nullptr) {
				current = nullptr;
			}
			else {
				current = tree->findMaxNode(tree->head); // Находим наибольший ключ дерева
			}
		}

		DataType& operator* () { // /доступ к данным текущего элемента
			if (current == nullptr) {
				throw exception("Вышли за пределы дерева");
			}
			return current->value;
		}

		rIterator& operator ++() { // оператор инкремента итератора
			if (current != nullptr) {
				current = tree->predecessor(current);
			}
			return *this;
		}

		bool operator == (const rIterator& other) { // проверка равенства
			return current == other.current;
		}

		bool operator != (const rIterator& other) { // проверка неравенства
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

	void clear(Node*& node); // Удаляем узел

	const Node* findNode(const Node* node, const KeyType& key) const { // Ищем рекурсивно ключ в заданном узле или его детях
		if (node == nullptr) {
			throw exception("Ключ не существует");
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

	const Node* findMaxNode(const Node* node) const { // Ищем максимальный ключ в заданном узле или его детях
		if (node == nullptr) {
			throw exception("Узел не существует");
		}
		while (node->rightPtr != nullptr) { // Итерируемся пока не найдем крайний правый узел
			node = node->rightPtr;
		}
		return node;
	}

	const Node* rParent(const Node* node, const Node* nodeByKey) { // Ищем родителя заданного узла
		if (node == nodeByKey) { // 2. Нашли родителя, возращаемся
			return nullptr;
		}
		else if (nodeByKey->key > node->key) {
			const Node* rp = rParent(node->rightPtr, nodeByKey);
			if (rp != nullptr) {
				return rp;  // 3. Нашли родителя, возращаемся
			}
			else {
				return node; // 1. Нашли родителя, возращаемся
			}
		}
		else {
			return rParent(node->leftPtr, nodeByKey);
		}
	}

	const Node* predecessor(const Node* node) { // Предыдущий по значению ключа узел для заданного узла
		if (node->leftPtr != nullptr) {
			return findMaxNode(node->leftPtr); // Ищем максимальный ключ в заданном узле или его детях
		}
		else {
			return rParent(head, node); // Ищем родителя заданного узла
		}
	}

	void insert(Node*& node, const KeyType& key, const DataType& value); // включение нового узла с заданным ключом и данными в качестве ребенка заданного родительского узла или его детей

	void removeByKey(Node*& node, const KeyType& key); // удаление заданного узла или его ребенка с заданным ключом

	void printNode(const Node* node, const size_t& level);  // вывод на экран заданного узла

	void Lt_Rt_t(const Node* node); // обход заданного узла и его детей в дереве по схеме Lt  Rt  t, и вывод ключей в порядке обхода
};

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::clear(Node*& node) { // удаление заданного узла и его детей
	if (node == nullptr) {
		return;
	}
	clear(node->leftPtr);  // Удаляем детей слева
	clear(node->rightPtr); // Удаляем детей справа
	delete node; // Удаляем сам узел
	node = nullptr; // Удаляем ссылку на очищенный узел
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::insert(Node*& node, const KeyType& key, const DataType& value) {// включение нового узла с заданным ключом и данными в качестве ребенка заданного родительского узла или его детей
	if (node == nullptr) { // Когда нашли свободное место для узла
		node = new Node(key, value);
		return;
	}
	if (node->key == key) {
		throw exception("Ключ уже существует");
	}
	else if (key < node->key) {
		insert(node->leftPtr, key, value);
	}
	else {
		insert(node->rightPtr, key, value);
	}
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::removeByKey(Node*& node, const KeyType& key) { // удаление заданного узла или его ребенка с заданным ключом
	if (node == nullptr) {
		throw exception("Ключ не найден");
	}
	if (node->key == key) { // Нашли узел для удаления
		if (node->leftPtr == nullptr && node->rightPtr == nullptr) { // Если нет детей - просто удаляем
			delete node;
			node = nullptr;
		}
		else if (node->leftPtr == nullptr) { // Если нет ребенка слева - копируем на место удаляемого узла правого ребенка
			Node* temp = node;
			node = node->rightPtr;
			delete temp;
		}
		else if (node->rightPtr == nullptr) { // Если нет ребенка справа - копируем на место удаляемого узла левого ребенка
			Node* temp = node;
			node = node->leftPtr;
			delete temp;
		}
		else { // Оба ребенка присутствуют
			const Node* temp = findMaxNode(node->leftPtr); // Находим максимального ребенка удаляемого узла
			node->value = temp->value;
			node->key = temp->key;
			removeByKey(node->leftPtr, temp->key); // Удаляем найденного ребенка
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
void BSTree<KeyType, DataType>::printNode(const Node* node, const size_t& level) { // вывод на экран заданного узла
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
	Lt_Rt_t(node->leftPtr); // Сначала все узлы слева
	Lt_Rt_t(node->rightPtr); // Потом все узлы справа
	cout << node->key << " "; // Выводим текущий узел
}

template <class KeyType, class DataType>
BSTree<KeyType, DataType>::BSTree() {}

template <class KeyType, class DataType>
BSTree<KeyType, DataType>::~BSTree() {
	clear();
}

template<class KeyType, class DataType>
size_t BSTree<KeyType, DataType>::getSize() const {// опрос размера дерева (количества узлов)
	return size;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::clear() { // очистка дерева (удаление всех узлов)
	size = 0;
	clear(head); // Удаляем корневой узел и его детей
}

template <class KeyType, class DataType>
bool BSTree<KeyType, DataType>::isEmpty() const { // проверка дерева на пустоту
	return head == nullptr; // Проверяем наличие хотя бы одного узла (корневого)
}

template<class KeyType, class DataType>
const DataType& BSTree<KeyType, DataType>::find(const KeyType& key) const { // поиск данных с заданным ключом
	return findNode(head, key)->value;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::insert(const KeyType& key, const DataType& value) { // включение в дерево нового узла с заданным ключом и данными
	insert(head, key, value);
	size++;
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::removeByKey(const KeyType& key) { // удаление из дерева узла с заданным ключом
	removeByKey(head, key);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::printTree() { // вывод структуры дерева на экран
	printNode(head, 0);
}

template<class KeyType, class DataType>
void BSTree<KeyType, DataType>::Lt_Rt_t() {  // обход узлов в дереве по схеме Lt  Rt  t, и вывод ключей в порядке обхода
	Lt_Rt_t(head);
	cout << endl;
}

template<class KeyType, class DataType>
const KeyType& BSTree<KeyType, DataType>::predecessorKey(const KeyType& key) { // поиск для заданного ключа предыдущего по значению ключа в дереве
	const Node* nodeForKey = findNode(head, key); // Находим узел по ключу
	const Node* foundNode = predecessor(nodeForKey); // Находим предшественника для найденного узла
	if (foundNode == nullptr) {
		throw exception("Меньший ключ не существует");
	}
	return foundNode->key;
}
