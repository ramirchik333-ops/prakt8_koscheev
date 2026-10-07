#include <iostream>
#include <cstring>   // для strcmp, strcpy

using namespace std;


// 1. Структура данных

struct Computer {
    char inventoryNumber[20]; 
    int ram;                  
    double price;            
};


// 2. Узел двусвязного списка

struct Node {
    Computer data;   // данные
    Node* next;      // указатель на следующий узел
    Node* prev;      // указатель на предыдущий узел
};

// 3. Класс двусвязного списка

class DoublyLinkedList {
private:
    Node* head; // указатель на первый элемент
    Node* tail; // указатель на последний элемент

public:
    // --- Конструктор: создание пустонр списка ---
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // --- Деструктор: освобождение всей памяти при выходе ---
    ~DoublyLinkedList() {
        clear();
    }


    // --- 1. Добавить элемент в НАЧАЛО списка ---
    void push_front(Computer comp) {
      
        Node* newNode = new Node;
        newNode->data = comp;
        newNode->prev = nullptr;   
        newNode->next = head;      

        if (head != nullptr) {
            head->prev = newNode;  // бывший первый теперь ссылается назад на новый
        }
        else {
            tail = newNode;       
        }

        head = newNode;        
    }

    // --- 2. Добавить элемент в КОНЕЦ списка ---
    void push_back(Computer comp) {
        Node* newNode = new Node;
        newNode->data = comp;
        newNode->next = nullptr;   
        newNode->prev = tail;     

        if (tail != nullptr) {
            tail->next = newNode;  // бывший последний теперь ссылается вперёд на новый
        }
        else {
            head = newNode;    
        }

        tail = newNode;           
    }

    // --- 3. Удалить ПЕРВЫЙ элемент ---
    void pop_front() {
        if (head == nullptr) {
            cout << "список пуст, удалять нечего!" << endl;
            return;
        }

        Node* toDelete = head;     // запоминаем, что будем удалять

        if (head == tail) {
  
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;    
            head->prev = nullptr;  
        }

        delete toDelete;           // освобождаем память
        cout << "первый элемент удалён" << endl;
    }

    // --- 4. Удалить ПОСЛЕДНИЙ элемент ---
    void pop_back() {
        if (tail == nullptr) {
            cout << "список пуст, удалять нечего!" << endl;
            return;
        }

        Node* toDelete = tail;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            tail = tail->prev;     // сдвигаем хвост назад
            tail->next = nullptr; 
        }

        delete toDelete;
        cout << "последний элемент удалён" << endl;
    }

    // --- 5. Вывод списка ОТ НАЧАЛА К КОНЦУ ---
    void display_forward() {
        if (head == nullptr) {
            cout << "список пуст" << endl;
            return;
        }

        cout << endl << "список (начало -> конец)" << endl;
        Node* current = head;
        int i = 1;
        while (current != nullptr) {
            cout << i << "инв номер: " << current->data.inventoryNumber << " | RAM: " << current->data.ram << " ГБ" << " | цена: " << current->data.price << " руб." << endl;
            current = current->next;
            i++;
        }
    }

    // --- 6. Вывод списка ОТ КОНЦА К НАЧАЛУ ---
    void display_backward() {
        if (tail == nullptr) {
            cout << "список пуст" << endl;
            return;
        }

        cout << endl<<"список (конец -> начало)" << endl;
        Node* current = tail;
        int i = 1;
        while (current != nullptr) {
            cout << i << "инв номер: " << current->data.inventoryNumber << " | RAM: " << current->data.ram << " ГБ" << " | цена: " << current->data.price << " руб." << endl;
            current = current->prev;
            i++;
        }
    }

    // --- 7. Поиск по инвентарному номеру ---
    void searchByNumber() {
        if (head == nullptr) {
            cout << "список пуст" << endl;
            return;
        }

        char key[20];
        cout << "введите инвентарный номер для поиска: ";
        cin >> key;

        Node* current = head;
        while (current != nullptr) {
            if (strcmp(current->data.inventoryNumber, key) == 0) {
                cout << "найден компьютер:" << endl;
                cout << "инв номер: " << current->data.inventoryNumber << " | RAM: " << current->data.ram << " ГБ" << " | цена: " << current->data.price << " руб." << endl;
                return;
            }
            current = current->next;
        }

        cout << "компьютер с таким номером не найден" << endl;
    }

    // --- 8. Удаление элемента из середины по инвентарному номеру ---
    void removeByNumber() {
        if (head == nullptr) {
            cout << "список пуст" << endl;
            return;
        }

        char key[20];
        cout << "введите инвентарный номер для удаления: ";
        cin >> key;

        Node* current = head;
        while (current != nullptr) {
            if (strcmp(current->data.inventoryNumber, key) == 0) {
                

                // Если это единственный элемент
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                // Если это первый элемент
                else if (current == head) {
                    head = current->next;
                    head->prev = nullptr;
                }
                // Если это последний элемент
                else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                }
                // Если это элемент в СЕРЕДИНЕ
                else {
                    current->prev->next = current->next;  // предыдущий теперь указывает на следующий
                    current->next->prev = current->prev;  // следующий теперь указывает на предыдущий
                }

                delete current;
                cout << "компьютер удалён" << endl;
                return;
            }
            current = current->next;
        }

        cout << "компьютер с таким номером не найден" << endl;
    }

    // --- 9. Полная очистка списка ---
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;       // освобождаем каждый узел
        }
        head = nullptr;
        tail = nullptr;
    }

 

    // --- Найти компьютер с максимальным объёмом RAM ---
    void findMaxRAM() {
        if (head == nullptr) {
            cout << "список пуст" << endl;
            return;
        }

        Node* maxNode = head;      
        Node* current = head->next;

        // Проходим по списку и ищем больший RAM
        while (current != nullptr) {
            if (current->data.ram > maxNode->data.ram) {
                maxNode = current;
            }
            current = current->next;
        }

        cout << "компьютер с максимальным RAM:" << endl;
        cout << "инв номер: " << maxNode->data.inventoryNumber << " | RAM: " << maxNode->data.ram << " ГБ" << " | цена: " << maxNode->data.price << " руб" << endl;
    }

    // --- Удалить все компьютеры дешевле заданной стоимости ---
    void removeCheaperThan() {
        if (head == nullptr) {
            cout << "список пуст" << endl;
            return;
        }

        double limit;
        cout << "введите порог стоимости: ";
        cin >> limit;

        int count = 0;
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;
            if (current->data.price < limit) {
              
                if (current == head && current == tail) {
                    head = nullptr;
                    tail = nullptr;
                }
                else if (current == head) {
                    head = current->next;
                    head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                count++;
            }

            current = nextNode; 
        }

        cout << "удалено компьютеров: " << count << endl;
    }

    // --- Поменять местами ПЕРВЫЙ и ПОСЛЕДНИЙ узлы (без обмена данными!) ---
    void swapFirstAndLast() {
      
        if (head == nullptr || head == tail) {
            cout << "в списке меньше 2 элементов, менять нечего" << endl;
            return;
        }

        Node* first = head;
        Node* last = tail;

        if (first->next == last) {
            first->next = nullptr;
            first->prev = last;
            last->next = first;
            last->prev = nullptr;
            head = last;
            tail = first;
            cout << "первый и последний узлы поменяны местами" << endl;
            return;
        }


        Node* second = first->next;         // второй элемент
        Node* beforeLast = last->prev;      // предпоследний элемент

       
        last->prev = nullptr;
        last->next = second;
        second->prev = last;


        first->next = nullptr;
        first->prev = beforeLast;
        beforeLast->next = first;


        head = last;
        tail = first;

        cout << "первый и последний узлы поменяны местами" << endl;
    }
};

// Вспомогательная функция: ввод данных компьютера

Computer inputComputer() {
    Computer comp;
    cout << "  инвентарный номер: ";
    cin >> comp.inventoryNumber;
    cout << "  объём RAM (ГБ): ";
    cin >> comp.ram;
    cout << "  цена (руб): ";
    cin >> comp.price;
    return comp;
}


int main() {
    setlocale(LC_ALL, "Russian");

    DoublyLinkedList list;
    int choice;

    do {
        cout << endl <<"========== меню ==========" << endl;
        cout << " 1. добавить в начало" << endl;
        cout << " 2. добавить в конец" << endl;
        cout << " 3. удалить первый" << endl;
        cout << " 4. удалить последний" << endl;
        cout << " 5. вывести список" << endl;
        cout << " 6. вывести в обратном порядке" << endl;
        cout << " 7. найти компьютер по номеру" << endl;
        cout << " 8. удалить компьютер по номеру" << endl;
        cout << " 9. найти макс RAM" << endl;
        cout << "10. удалить дешевле N" << endl;
        cout << "11. поменять первый и последний" << endl;
        cout << "12. очистить список" << endl;
        cout << " 0. выход" << endl;
        cout << "выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "введите данные компьютера:" << endl;
            list.push_front(inputComputer());
            cout << "добавлено в начало" << endl;
            break;
        }
        case 2: {
            cout << "введите данные компьютера:" << endl;
            list.push_back(inputComputer());
            cout << "добавлено в конец" << endl;
            break;
        }
        case 3:
            list.pop_front();
            break;
        case 4:
            list.pop_back();
            break;
        case 5:
            list.display_forward();
            break;
        case 6:
            list.display_backward();
            break;
        case 7:
            list.searchByNumber();
            break;
        case 8:
            list.removeByNumber();
            break;
        case 9:
            list.findMaxRAM();
            break;
        case 10:
            list.removeCheaperThan();
            break;
        case 11:
            list.swapFirstAndLast();
            break;
        case 12:
            list.clear();
            cout << "список очищен" << endl;
            break;
        case 0:
            cout << "выход из программы" << endl;
            break;
        default:
            cout << "неверный выбор" << endl;
        }
    } while (choice != 0);

    return 0;
    // Деструктор ~DoublyLinkedList() вызовет clear() и освободит всю память
}