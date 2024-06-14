/**
 * \file main.cpp
 * \brief Основной файл программы, реализующий сервер на базе сокетов и использующий односвязный список и стек.
 */

#include "main.h"

/**
 * \brief Конструктор узла односвязного списка.
 * \param data Сокет клиента.
 */
Node::Node(SOCKET data) : data(data), next(nullptr) {}

/**
 * \brief Конструктор узла стека.
 * \param data Строка данных.
 */
StackNode::StackNode(std::string data) : data(data), next(nullptr) {}

/**
 * \brief Конструктор односвязного списка.
 */
LinkedList::LinkedList() : head(nullptr) {}

/**
 * \brief Добавление узла в конец односвязного списка.
 * \param data Сокет клиента.
 *
 *  Создает новый узел с указанным сокетом и добавляет его в конец списка. Если список пуст,
 *  новый узел становится его головой. В противном случае узел добавляется после последнего элемнта списка.
 */
void LinkedList::append(SOCKET data) {
  Node *newNode = new Node(data);
  if (!head) {
    head = newNode;
  } else {
    Node *temp = head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

/**
 * \brief Отображение содержимого односвязного списка.
 *
 *  Выводит данные всех узлов списка на консоль в формате: data1 -> data2 -> ... -> NULL.
 */
void LinkedList::display() {
  Node *temp = head;
  while (temp) {
    std::cout << temp->data << " -> ";
    temp = temp->next;
  }
  std::cout << "NULL" << std::endl;
}

/**
 * \brief Получение головы односвязного списка.
 * \return Указатель на голову списка.
 *
 *  Возвращает указатель на первый узел списка.
 */
Node *LinkedList::getHead() {
  return head;
}

/**
 * \brief Удаление узла из односвязного списка по значению сокета.
 * \param data Сокет клиента.
 *
 *  Удаляет первый узел с указанным сокетом из списка. Если узел с указанным сокетом не найден,
 *  список остается без изменений.
 */
//Заимствование --------------------------------------------------
void LinkedList::remove(SOCKET data) {
  if (!head)
    return;

  if (head->data == data) {
    Node *temp = head;
    head = head->next;
    delete temp;
    return;
  }

  Node *current = head;
  while (current->next && current->next->data != data) {
    current = current->next;
  }

  if (current->next) {
    Node *temp = current->next;
    current->next = current->next->next;
    delete temp;
  }
}
//Заимствование -------------------------------------------------
/**
 * \brief Деструктор односвязного списка. Удаляет все узлы.
 *
 *  Проходит по всему списку и удаляет каждый узел, освобождая занятую память.
 */
LinkedList::~LinkedList() {
  Node *temp;
  while (head) {
    temp = head;
    head = head->next;
    delete temp;
  }
}

/**
 * \brief Конструктор стека.
 */
Stack::Stack() : top(nullptr) {}

/**
 * \brief Добавление элемента на вершину стека.
 * \param data Строка данных.
 *
 *  Создает новый узел с указанной строкой данных и добавляет его на вершину стека.
 */
void Stack::push(std::string data) {
  StackNode *newNode = new StackNode(data);
  newNode->next = top;
  top = newNode;
}

/**
 * \brief Удаление и получение элемента с вершины стека.
 * \return Строка данных.
 *
 *  Удаляет верхний узел стека и возвращает хранимую в нем строку данных.
 *  Если стек пуст, вовзращает пустую строку и выводит сообщение об ошибке.
 */
std::string Stack::pop() {
  if (!top) {
    std::cerr << "Stack underflow" << std::endl;
    return "";
  }
  StackNode *temp = top;
  std::string popped = top->data;
  top = top->next;
  delete temp;
  return popped;
}

/**
 * \brief Получение элемента с вершины стека без его удаления.
 * \return Строка данных.
 *
 *  Возвращает строку данных верхнего узла стека без его удаления.
 *  Если стек пуст, возвращает пустую строку и выводит сообщение об ошибке.
 */
std::string Stack::peek() {
  if (!top) {
    std::cerr << "Stack is empty" << std::endl;
    return "";
  }
  return top->data;
}

/**
 * \brief Проверка, пуст ли стек.
 * \return true, если стек пуст, иначе false.
 *
 *  Возвращает true, если стек пуст, иначе false.
 */
bool Stack::isEmpty() {
  return top == nullptr;
}

/**
 * \brief Деструктор стека. Удаляет все узлы.
 *
 *  Проходит по всему стеку и удаляет каждый узел, освобождая занятую память.
 */
Stack::~Stack() {
  StackNode *temp;
  while (top) {
    temp = top;
    top = top->next;
    delete temp;
  }
}

/**
 * \brief Глобальная переменная, представляющая сокет для прослушивания.
 */
SOCKET Listen;

/**
 * \brief Глобальная переменная, представляющая список подключенных клиентов.
 */
LinkedList connectionsList;

/**
 * \brief Глобальная переменная, представляющая количество клиентов.
 */
int ClientCount = 0;

/**
 * \brief Отправка сообщения клиенту.
 * \param ID Идентификатор клиента.
 *
 *   Отправляет сообщение клиенту с указанным идентификатором через соответствующий сокет.
 *   Получает сообщение от клиента и пересылает его всем подключенным клиентам.
 */
void SendMessageToClient(int ID) {
  char *buffer = new char[1024];

  for (;; Sleep(75)) {
    memset(buffer, 0, sizeof(buffer));

    Node *temp = connectionsList.getHead();
    SOCKET clientSocket = INVALID_SOCKET;
    for (int i = 0; i < ID && temp; i++) {
      temp = temp->next;
    }
    if (temp) {
      clientSocket = temp->data;
    }

    if (clientSocket != INVALID_SOCKET && recv(clientSocket, buffer, 1024, NULL)) {
      std::cout << buffer;
      std::cout << "\n";

      Node *current = connectionsList.getHead();
      while (current) {
        send(current->data, buffer, strlen(buffer), NULL);
        current = current->next;
      }
    }
  }

  delete[] buffer;
}

/**
 * \brief Основная функция программы. Инициализирует сервер, принимает подключения клиентов и создает потоки для обработки сообщений.
 *
 *  Инициализирует сервер, принимает подключения клиентов и создает потоки для обработки сообщений.
 *  Также демонстрирует использование односвязного списка и стека.
 *
 * \return Код завершения программы.
 */
int main() {
  setlocale(LC_ALL, "english");

  WSAData data;
  WORD version = MAKEWORD(2, 2);
  int result = WSAStartup(version, &data);

  if (result != 0) {
    return 0;
  }
  struct addrinfo hints;
  struct addrinfo *finally;

  //Заимствованный код ---------------------------------------------------------
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  getaddrinfo(NULL, "7770", &hints, &finally);
  Listen = socket(finally->ai_family, finally->ai_socktype, finally->ai_protocol);
  bind(Listen, finally->ai_addr, finally->ai_addrlen);
  listen(Listen, SOMAXCONN);

  freeaddrinfo(finally);
  std::cout << "Start server";

  char m_connect[] = "Connect...;;;5";

  for (;; Sleep(75)) {
    SOCKET Connect = accept(Listen, NULL, NULL);
    if (Connect != INVALID_SOCKET) {
      std::cout << "Client connect...\n";
      connectionsList.append(Connect);
      send(Connect, m_connect, strlen(m_connect), NULL);
      ClientCount++;

      CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) SendMessageToClient, (LPVOID) (ClientCount - 1), NULL, NULL);
    }
  }//Заимствованный код-----------------------------------------------------------------

  LinkedList list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.display();

  Stack stack;
  stack.push("First message");
  stack.push("Second message");
  stack.push("Third message");
  std::cout << "Top element is " << stack.peek() << std::endl;
  std::cout << "Stack elements: ";
  while (!stack.isEmpty()) {
    std::cout << stack.pop() << " ";
  }
  std::cout << std::endl;

  return 0;
}
