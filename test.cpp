/**
 * \file test.cpp
 * \brief Файл для тестов.
 * Данный файл предназначен для тестирования структур Linked и Stack. Включаем два хедер файла doctest.h и main.h.
 */
#include "doctest.h"
#include "main.h"

/**
 * \brief Тесты для методов append и getHead класса LinkedList.
 *
 *  Данный тестовый сулчай проверяет функциональность методов append и getHead.
 *
 *  Тесты делают следующие проверки:
 */
TEST_CASE("LinkedList append and getHead") {
  LinkedList list;
  CHECK(list.getHead() == nullptr); ///< Проверка, что начальный список пуст.

  list.append(1);
  CHECK(list.getHead()->data == 1); ///< Проверка, что первый элемент добавлен правильно.
  CHECK(list.getHead()->next == nullptr); ///< Проверка, что в списке только один элемент.

  list.append(2);
  CHECK(list.getHead()->next->data == 2); ///< Проверка, что второй элемент добавлен правильно.
  CHECK(list.getHead()->next->next == nullptr); ///< Проверка, что в списке два элемента.
}

/**
 * \brief Тесты для метода remove класса LinkedList.
 *
 *  Данный тестовый случай проверяет функциональность метода remove.
 *
 *  Тесты делают следующие проверки:
 */
TEST_CASE("LinkedList remove") {
  LinkedList list;
  list.append(1);
  list.append(2);
  list.append(3);

  list.remove(2);
  CHECK(list.getHead()->data == 1); ///< Проверка, что элемент 2 удален правильно.
  CHECK(list.getHead()->next->data == 3); ///< Проверка, что список обновлен правильно.
  CHECK(list.getHead()->next->next == nullptr); ///< Проверка, что в списке два элемента.

  list.remove(1);
  CHECK(list.getHead()->data == 3); ///< Проверка, что элемент 1 удален правильно.
  CHECK(list.getHead()->next == nullptr); ///< Проверка, что в списке один элемент.

  list.remove(3);
  CHECK(list.getHead() == nullptr); ///< Проверка, что список пуст.
}

/**
 * \brief Тесты для методов push и pop класса Stack.
 *
 *  Данный тестовый случай проверяет функциональность методов push и pop.
 *
 *  Тесты делают следующие проверки:
 */
TEST_CASE("Stack push and pop") {
  Stack stack;
  CHECK(stack.isEmpty() == true); ///< Проверка, что стек пуст в начале.

  stack.push("First message");
  stack.push("Second message");
  stack.push("Third message");

  CHECK(stack.isEmpty() == false); ///< Проверка, что стек не пуст после добавления элементов.
  CHECK(stack.pop() == "Third message"); ///< Проверка, что элементы извлекаются в правильном порядке.
  CHECK(stack.pop() == "Second message");
  CHECK(stack.pop() == "First message");
  CHECK(stack.isEmpty() == true); ///< Проверка, что стек пуст после извлечения всех элементов.
}

/**
 * \brief Тесты для метода peek класса Stack.
 *
 *  Этот тестовый случай проверяет функциональность метода peek.
 *
 *  Тест делают следующие проверки:
 */
TEST_CASE("Stack peek") {
  Stack stack;
  stack.push("First message");
  stack.push("Second message");

  CHECK(stack.peek() == "Second message"); ///< Проверка, что верхний элемент правильный.
  stack.pop();
  CHECK(stack.peek() == "First message"); ///< Проверка, что верхний элемент обновлен после извлечения.
  stack.pop();
  CHECK(stack.peek() == ""); ///< Проверка, что стек пуст и метод peek возвращает пустую строку.
}
