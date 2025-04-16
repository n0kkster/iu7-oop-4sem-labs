#include "set.h"

#include <iostream>

void test_cctors()
{
    std::cout << "=====================================\n";

    // 1. Вызов дефолтного конструктора
    Set<int> is1;
    is1.add(1);
    is1.add(2);
    is1.add(3);
    is1.add(4);
    is1.add(5);
    std::cout << "1. Дефолтный конструктор: ";
    std::cout << is1 << std::endl;

    // 2. Вызов конструктора от массива
    int *arr = new int[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    Set<int> is2(10, arr);
    std::cout << "2. Конструктор от массива: ";
    std::cout << is2 << std::endl;

    // 3. Вызов конструктора от списка инициализации
    Set<int> is3({ 1, 2, 3, 4, 5, 6, 7 });
    std::cout << "3. Конструктор от списка инициализации: ";
    std::cout << is3 << std::endl;

    // 4. Вызов конструктора копирования
    Set<int> is4(is3);
    std::cout << "4. Конструктор копирования: ";
    std::cout << is4 << std::endl;

    // 5. Вызов конструктора переноса
    Set<int> is5(std::move(Set<int>({ 1, 2, 3, 4 }))); //  как создать правую ссылку?
    std::cout << "5. Конструктор переноса: ";
    std::cout << is5 << std::endl;

    // 5. Вызов конструктора от итераторов
    Set<int> is6(is2.cbegin(), is2.cend());
    std::cout << "6. Конструктор от итераторов: ";
    std::cout << is6 << std::endl;

    delete[] arr;

    std::cout << "=====================================\n";
}

void test_addition()
{
    std::cout << "=====================================\n";

    Set<int> is;
    int x = 2;
    int *arr = new int[3]{ 5, 2, 10 };

    is.add(1);
    is.add(x);

    std::cout << "Множество после добавления: ";
    std::cout << is << std::endl;

    is.clear();

    std::cout << "Множество после очистки: ";
    std::cout << is << std::endl;

    is.add(1);
    is.add(x);

    std::cout << "Множество после добавления: ";
    std::cout << is << std::endl;

    delete[] arr;

    std::cout << "=====================================\n";
}

void test_assign()
{
    std::cout << "=====================================\n";

    Set<int> is1;
    Set<int> is2({ 1, 2, 3, 4, 5, 6 });

    std::cout << "1. Присваивание другого списка" << std::endl;
    std::cout << "Множество до присваивания: ";
    std::cout << is1 << std::endl;

    is1.assign(is2);

    std::cout << "Множество после присваивания: ";
    std::cout << is1 << std::endl;

    is1 = is2;

    std::cout << "Множество после присваивания: ";
    std::cout << is1 << std::endl;

    // ================================================

    std::cout << "2. Присваивание rvalue" << std::endl;
    is1.clear();

    std::cout << "Множество до присваивания: ";
    std::cout << is1 << std::endl;

    is1.assign(std::move(is2));

    std::cout << "Множество после присваивания: ";
    std::cout << is1 << std::endl;

    is2 = { 3, 2, 1, 0, -1, -2, -3 };

    is1 = std::move(is2);

    std::cout << "Множество после присваивания: ";
    std::cout << is1 << std::endl;

    // ================================================

    std::cout << "3. Присваивание списка инициализации" << std::endl;
    is1.clear();

    std::cout << "Множество до присваивания: ";
    std::cout << is1 << std::endl;

    is1.assign({ 1, 2, 3, 4, 5, 6 });

    std::cout << "Множество после присваивания: ";
    std::cout << is1 << std::endl;

    is1 = { 5, 4, 3, 2, 1 };

    std::cout << "Множество после присваивания: ";
    std::cout << is1 << std::endl;

    std::cout << "=====================================\n";
}

void test_union()
{
    std::cout << "=====================================\n";

    Set<int> is1{ 1, 2, 3, 4, 5 };
    Set<int> is2{ 4, 5, 6, 7, 8 };

    std::cout << "1. Объединение множеств " << is1 << " и " << is2
              << " с созданием нового мн-ва:" << std::endl;

    Set<int> is3 = is1.make_union(is2);
    std::cout << "\tmake_union: " << is3 << std::endl;

    is3 = is1 + is2;
    std::cout << "\toperator +: " << is3 << std::endl;

    is3 = is1 + is2;
    std::cout << "\toperator |: " << is3 << std::endl;

    std::cout << "2. Объединение множеств " << is1 << " и " << is2
              << " с модификацией исходного мн-ва:" << std::endl;

    is3 = is1;
    is3.unite(is2);
    std::cout << "\tunite: " << is3 << std::endl;

    is3 = is1;
    is3 += is2;
    std::cout << "\toperator +=: " << is3 << std::endl;

    is3 = is1;
    is3 |= is2;
    std::cout << "\toperator |=: " << is3 << std::endl;

    std::cout << "=====================================\n";
}

int main()
{
    // ==================== ТЕСТЫ ==================
    test_cctors();
    test_addition();
    test_assign();
    test_union();
    // ==================== ТЕСТЫ ==================

    return 0;
}
