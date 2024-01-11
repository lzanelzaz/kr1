#include <iostream>
#include "BSTree.h"

using namespace std;

/* Алгоритмы основных операций АТД (вставки, удаления и поиска) реализуются в
* рекурсивной форме.
* Создание и операции обратного итератора.
* Схема операции обхода: Lt → Rt → t.
* Дополнительная операция: поиск для заданного ключа предыдущего по значению
* ключа в дереве.
*/

int main() {
	setlocale(LC_ALL, "Russian");

	BSTree<int, string> tree = BSTree<int, string>();

	int n;
	while (1) {
		cout << endl << "Меню. Выберите действие:" << endl << endl;
		cout << "1. Вставка" << endl;
		cout << "2. Удаление" << endl;
		cout << "3. Размер дерева" << endl;
		cout << "4. Очистка" << endl;
		cout << "5. Проверка на пустоту" << endl;
		cout << "6. Обход: Lt -> Rt -> t" << endl;
		cout << "7. Дополнительная операция: поиск для заданного ключа предыдущего по значению ключа в дереве" << endl;
		cout << "8. Печать" << endl;
		cout << "9. Сгенерировать дерево" << endl;
		cout << "10. Поиск по ключу" << endl;
		cout << "11. Проитерироваться с помощью обратного итератора" << endl;
		cout << "12. Сравнить обратные итераторы" << endl;
		cout << endl;
		cin >> n;
		cout << endl;
		try {
			switch (n) {
			case 1: {
				int key;
				string value;
				cin >> key >> value;
				tree.insert(key, value);
				break;
			}
			case 2: {
				int key;
				cin >> key;
				tree.removeByKey(key);
				break;
			}
			case 3: {
				cout << tree.getSize() << endl;
				break;
			}
			case 4: {
				tree.clear();
				break;
			}
			case 5: {
				cout << tree.isEmpty() << endl;
				break;
			}
			case 6: {
				cout << endl;
				tree.Lt_Rt_t();
				break;
			}
			case 7: {
				int key;
				cin >> key;
				cout << tree.predecessorKey(key);
				break;
			}
			case 8: {
				cout << endl;
				tree.printTree();
				break;
			}
			case 9: {
				tree.clear();
				tree.insert(10, "a");
				tree.insert(5, "b");
				tree.insert(2, "c");
				tree.insert(8, "d");
				tree.insert(15, "e");
				tree.insert(9, "f");
				tree.insert(11, "g");
				break;
			}
			case 10: {
				int key;
				cin >> key;
				cout << tree.find(key) << endl;
				break;
			}
			case 11: {
				auto it = tree.rbegin();
				while (it.hasNext()) {
					cout << *it << " ";
					++it;
				}
				cout << endl;
				break;
			}
			case 12: {
				BSTree<int, string>::rIterator it1 = tree.rbegin();
				BSTree<int, string>::rIterator it2 = tree.rbegin();
				cout << *it1 << " == " << *it2<<" ? -> " << (it1 == it2) << endl;
				++it2;
				cout << *it1 << " == " << *it2 << " ? -> " << (it1 == it2) << endl;
				break;
			}
			default: {
				cout << "Попробуйте еще раз" << endl;
				break;
			}
			}
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
}
