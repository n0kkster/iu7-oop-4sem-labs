#include "set.h"

#include <iostream>
#include <ranges>
#include <vector>

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

    std::vector<int> vec{ 1, 2, 3, 4, 4, 3, 2, 1 };

    Set<int> vs(vec);
    std::cout << "7. Конструктор от контейнера: ";
    std::cout << vs << std::endl;

    Set<int> vr(std::ranges::subrange(vec.begin() + 1, vec.end() - 1));
    std::cout << "8. Конструктор от диапазона: ";
    std::cout << vr << std::endl;

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
    std::cout << "\tМножество до присваивания: ";
    std::cout << "\t" << is1 << std::endl;

    is1.assign(is2);

    std::cout << "\tassign: ";
    std::cout << "\t" << is1 << std::endl;

    is1 = is2;

    std::cout << "\toperator =: ";
    std::cout << "\t" << is1 << std::endl;

    // ================================================

    std::cout << "2. Присваивание rvalue" << std::endl;

    is1.clear();

    std::cout << "\tМножество до присваивания: ";
    std::cout << "\t" << is1 << std::endl;

    is1.assign(std::move(is2));

    std::cout << "\tassign: ";
    std::cout << "\t" << is1 << std::endl;

    is2 = { 3, 2, 1, 0, -1, -2, -3 };

    is1 = std::move(is2);

    std::cout << "\toperator =: ";
    std::cout << "\t" << is1 << std::endl;

    // ================================================

    std::cout << "3. Присваивание списка инициализации" << std::endl;
    is1.clear();

    std::cout << "\tМножество до присваивания: ";
    std::cout << "\t" << is1 << std::endl;

    is1.assign<int>({ 1, 2, 3, 4, 5, 6 });

    std::cout << "\tassign: ";
    std::cout << "\t" << is1 << std::endl;

    is1 = { 5, 4, 3, 2, 1 };

    std::cout << "\toperator =: ";
    std::cout << "\t" << is1 << std::endl;

    std::cout << "4. Последовательное присваивание:" << std::endl;
    Set<int> is3;

    is1 = is2 = is3 = { 1, 2, 3, 4 };
    std::cout << "\t" << is1 << std::endl << "\t" << is2 << std::endl << "\t" << is3 << std::endl;

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

    std::cout << "3. Последовательное объединение множеств:" << std::endl;
    is3 = { 7, 8, 9, 10, 11, 12 };
    Set<int> is4 = is1 + is2 + is3;
    std::cout << is4 << std::endl;

    std::cout << "=====================================\n";
}

void test_intersection()
{
    std::cout << "=====================================\n";

    Set<int> is1{ 1, 2, 3, 4, 5 };
    Set<int> is2{ 4, 5, 6, 7, 8 };

    std::cout << "1. Пересечение множеств " << is1 << " и " << is2
              << " с созданием нового мн-ва:" << std::endl;

    Set<int> is3 = is1.make_intersection(is2);
    std::cout << "\tmake_intersection: " << is3 << std::endl;

    is3 = is1 & is2;
    std::cout << "\toperator &: " << is3 << std::endl;

    std::cout << "2. Пересечение множеств " << is1 << " и " << is2
              << " с модификацией исходного мн-ва:" << std::endl;

    is3 = is1;
    is3.intersect(is2);
    std::cout << "\tintersect: " << is3 << std::endl;

    is3 = is1;
    is3 &= is2;
    std::cout << "\toperator &=: " << is3 << std::endl;

    std::cout << "3. Последовательное пересечение множеств:" << std::endl;
    is3 = { 7, 8, 9, 10, 11, 12 };
    Set<int> is4 = is1 & is2 & is3;
    std::cout << is4 << std::endl;

    std::cout << "=====================================\n";
}

void test_erase()
{
    std::cout << "=====================================\n";

    Set<int> is({ 1, 2, 3, 4 });
    std::cout << "1. Удаление произвольного элемента из мн-ва " << is << " по значению (3): ";
    is.erase(3);
    std::cout << is << std::endl;

    is.add(3);

    std::cout << "2. Удаление первого элемента из мн-ва " << is << " по значению (1): ";
    is.erase(1);
    std::cout << is << std::endl;

    is.add(5);

    std::cout << "3. Удаление последнего элемента из мн-ва " << is << " по значению (5): ";
    is.erase(5);
    std::cout << is << std::endl;

    std::cout << "4. Удаление всех элементов элемента из мн-ва " << is << " в цикле: ";
    for (auto it = is.cbegin(); it != is.cend();)
        is.erase(it);
    std::cout << is << std::endl;

    std::cout << "=====================================\n";
}

void test_subtract()
{
    std::cout << "=====================================\n";

    Set<int> is1({ 1, 2, 3, 4 });
    Set<int> is2({ 3, 4, 5, 6 });

    std::cout << "1. Вычитание мн-ва " << is2 << " из мн-ва " << is1 << ": \n";
    std::cout << "\tmake_difference: " << is1.make_difference(is2) << std::endl;
    std::cout << "\toperator -: " << is1 - is2 << std::endl;

    is1.subtract(is2);
    std::cout << "\tsubtract: " << is1 << std::endl;
    is1 = { 1, 2, 3, 4 };
    is1 -= is2;
    std::cout << "\toperator -=: " << is1 << std::endl;

    is1 = { 1, 2, 3, 4 };
    is2 = { 5, 6, 7, 8 };
    std::cout << "2. Вычитание мн-ва " << is2 << " из мн-ва " << is1 << ": \n";
    std::cout << "\tmake_difference: " << is1.make_difference(is2) << std::endl;
    std::cout << "\toperator -: " << is1 - is2 << std::endl;

    is1.subtract(is2);
    std::cout << "\tsubtract: " << is1 << std::endl;
    is1 = { 1, 2, 3, 4 };
    is1 -= is2;
    std::cout << "\toperator -=: " << is1 << std::endl;

    is2 = is1;
    std::cout << "3. Вычитание мн-ва " << is2 << " из мн-ва " << is1 << ": \n";
    std::cout << "\tmake_difference: " << is1.make_difference(is2) << std::endl;
    std::cout << "\toperator -: " << is1 - is2 << std::endl;

    is1.subtract(is2);
    std::cout << "\tsubtract: " << is1 << std::endl;
    is1 = { 1, 2, 3, 4 };
    is1 -= is2;
    std::cout << "\toperator -=: " << is1 << std::endl;

    std::cout << "=====================================\n";
}

void test_xor()
{
    std::cout << "=====================================\n";

    Set<int> is1({ 1, 2, 3, 4 });
    Set<int> is2({ 3, 4, 5, 6 });

    std::cout << "1. Симметрическое вычитание мн-ва " << is2 << " из мн-ва " << is1 << ": \n";
    std::cout << "\tmake_symm_difference: " << is1.make_symm_difference(is2) << std::endl;
    std::cout << "\toperator ^: " << (is1 ^ is2) << std::endl;

    is1.symm_subtract(is2);
    std::cout << "\tsymm_subtract: " << is1 << std::endl;
    is1 = { 1, 2, 3, 4 };
    is1 ^= is2;
    std::cout << "\toperator ^=: " << is1 << std::endl;

    is1 = { 1, 2, 3, 4 };
    is2 = { 5, 6, 7, 8 };
    std::cout << "2. Симметрическое вычитание мн-ва " << is2 << " из мн-ва " << is1 << ": \n";
    std::cout << "\tmake_symm_difference: " << is1.make_symm_difference(is2) << std::endl;
    std::cout << "\toperator ^: " << (is1 ^ is2) << std::endl;

    is1.symm_subtract(is2);
    std::cout << "\tsymm_subtract: " << is1 << std::endl;
    is1 = { 1, 2, 3, 4 };
    is1 ^= is2;
    std::cout << "\toperator ^=: " << is1 << std::endl;

    is2 = is1;
    std::cout << "3. Симметрическое вычитание мн-ва " << is2 << " из мн-ва " << is1 << ": \n";
    std::cout << "\tmake_symm_difference: " << is1.make_symm_difference(is2) << std::endl;
    std::cout << "\toperator ^: " << (is1 ^ is2) << std::endl;

    is1.symm_subtract(is2);
    std::cout << "\tsymm_subtract: " << is1 << std::endl;
    is1 = is2;
    is1 ^= is2;
    std::cout << "\toperator ^=: " << is1 << std::endl;

    std::cout << "=====================================\n";
}

void test_comparison()
{
    std::cout << "=====================================\n";

    Set<int> is1{ 1, 2, 3, 4, 5, 6, 7 };
    Set<int> is2{ 2, 3, 4, 5 };
    Set<int> is3(is1);
    Set<int> is4{ 5, 6, 7, 8 };
    Set<int> is5{};

    std::cout << is1 << " < " << is2 << " : " << (is1 < is2) << std::endl;
    std::cout << is1 << " > " << is2 << " : " << (is1 > is2) << std::endl;
    std::cout << is1 << " <= " << is3 << " : " << (is1 <= is2) << std::endl;
    std::cout << is1 << " >= " << is3 << " : " << (is1 <= is3) << std::endl;
    std::cout << is1 << " < " << is4 << " : " << (is1 < is4) << std::endl;
    std::cout << is1 << " > " << is4 << " : " << (is1 > is4) << std::endl;
    std::cout << is1 << " == " << is3 << " : " << (is1 == is3) << std::endl;
    std::cout << is1 << " == " << is2 << " : " << (is1 == is2) << std::endl;
    std::cout << is1 << " != " << is2 << " : " << (is1 != is2) << std::endl;
    std::cout << is1 << " != " << is3 << " : " << (is1 != is3) << std::endl;

    std::cout << is1 << " сравнимо с " << is2 << " : " << is1.comparable(is2) << std::endl;
    std::cout << is1 << " сравнимо с " << is4 << " : " << is1.comparable(is4) << std::endl;

    std::cout << is5 << " < " << is1 << " : " << (is5 < is1) << std::endl;
    std::cout << is5 << " < " << is4 << " : " << (is5 < is4) << std::endl;
    std::cout << is5 << " сравнимо с " << is1 << " : " << is5.comparable(is1) << std::endl;
    std::cout << is1 << " сравнимо с " << is5 << " : " << is1.comparable(is5) << std::endl;

    std::cout << "=====================================\n";
}

int main()
{
    static_assert(std::forward_iterator<ConstIterator<int>>,
                  "Iterator does not satisfy std::forward_iterator");

    static_assert(Container<Set<int>>, "Set does not satisfy Container");
    static_assert(Container<std::vector<int>>, "Vector does not satisfy Container");
    static_assert(std::ranges::input_range<Set<int>>, "Set does not satisfy input range");

    // ==================== ТЕСТЫ ==================
    test_cctors();
    test_addition();
    test_assign();
    test_union();
    test_intersection();
    test_erase();
    test_subtract();
    test_xor();

    test_comparison();
    // ==================== ТЕСТЫ ==================

    // Set<int> is1 = { 1, 2, 3, 4, 5 };
    // Set<double> ds1 = { 1.0, 3.4, 5.6, 7.8 };

    // auto res = is1 ^ ds1;
    // auto res2 = ds1 ^ is1;
    // std::cout << is1 << " & " << ds1 << " = " << res << std::endl;
    // std::cout << ds1 << " & " << is1 << " = " << res2 << std::endl;

    // std::vector<int> ivec = { 1, 2, 3, 4, 5 };
    // std::ranges::for_each(ivec, [](const auto &el) { std::cout << el << " "; });
    // std::cout << std::endl;

    // Set<int> isvec(ivec);

    // Set<int> istvec(std::vector<int>{ 1, 2, 3 });

    // Set<int> is1;
    // Set<int> is2 = {1, 2, 3, 4};

    // std::cout << "calling copy lref\n";
    // is1 = is2;

    // std::cout << "calling copy rref\n";
    // is1 = Set<int>{1, 2, 3, 4};

    // std::cout << "calling ilist\n";
    // is1 = {1, 2, 3, 4};

    // std::cout << "calling container lref\n";
    // std::vector<int> vec;
    // vec.push_back(1);
    // is1 = vec;

    // std::cout << "calling container rref\n";
    // is1 = std::vector<int>{1, 2, 3, 4};

    // Set<int> is1 = {1, 2, 3, 4, 5};
    // std::vector<int> iv1 = {5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7};
    // std::cout << is1 + iv1 << std::endl;

    // Set<int> is1 = {};
    // Set<int> is2 = {0, 1, 2, 3, 4, 5, 6, 7};

    // std::cout << is1.subsetOf(is2) << std::endl;

    Set<int> is1 = { 1, 2, 3, 4 };
    std::vector<double> vec = { 1, 1, 1, 2.0, 3, 4 };
    std::cout << (is1 == vec) << std::endl;
    std::cout << (vec <= is1) << std::endl;

    std::cout << "\n";

    return 0;
}

// TODO
// 1. сделать форвард итератор и проверить его статик ассертом +
// 2. разобраться с конструктором ноды (вроде разобрался ?) +
// 6. чето решить с конвертацией типов (например set<int> + set<double> должно быть set<double>) +
// 7. перегруппировать функции в регионах +
// 4. разобраться с конструкторами от rvalue контейнера и диапазона +
// 8. сделать чуть более сложную иерархию наследования эксепшенов +
// 5. сделать оператор присваивания от инит листа, range, container +
// сделать остальные операторы от range и контейнера +
// 3. разобраться со стрелочкой в итераторе +
