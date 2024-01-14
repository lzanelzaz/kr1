#include <iostream>
#include "BSTree.h"

using namespace std;

/* Вариант 8
* Алгоритмы основных операций АТД (вставки, удаления и поиска) реализуются в
* рекурсивной форме.
* Создание и операции обратного итератора.
* Схема операции обхода: Lt → Rt → t.
* Дополнительная операция: поиск для заданного ключа предыдущего по значению
* ключа в дереве.
*/

int main() {
	setlocale(LC_ALL, "Russian");
	BSTree<int, int> tree = BSTree<int, int>();
	auto it = tree.rend();
	int n;
	while (true) {
		cout << endl << "Меню. Выберите действие:" << endl << endl;
		cout << "1. Вставка" << endl;
		cout << "2. Удаление" << endl;
		cout << "3. Размер дерева" << endl;
		cout << "4. Очистка" << endl;
		cout << "5. Проверка на пустоту" << endl;
		cout << "6. Обход: Lt -> Rt -> t" << endl;
		cout << "7. Дополнительная операция: поиск для заданного ключа предыдущего по значению ключа в дереве" << endl;
		cout << "8. Печать" << endl;
		cout << "9. Поиск по ключу" << endl;
		cout << "10. Обнулить итератор" << endl;
		cout << "11. Показать содержание итератора" << endl;
		cout << "12. Перевести итератор на следующий элемент" << endl;
		cout << "13. Присвоить итератору новое значение" << endl;
		cout << endl;
		cin >> n;
		cout << endl;
		try {
			switch (n) {
			case 1: {
				int key;
				int value;
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
				int key;
				cin >> key;
				cout << tree.find(key) << endl;
				break;
			}
			case 10: {
				it = tree.rbegin();
				break;
			}
			case 11: {
				cout << *it << endl;
				break;
			}
			case 12: {
				++it;
				break;
			}
			case 13: {
				cin >> *it;
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
