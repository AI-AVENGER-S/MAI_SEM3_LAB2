#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/FOUR.h"

using namespace std;

// Вспомогательная функция для получения строкового представления
static string toString(const Four& num) {
    ostringstream oss;
    num.print(oss);
    return oss.str();
}

// Тест 1: Конструкторы
TEST(FourTest, constructors) {
    Four f1; // пустой
    Four f2(3, 2);       // 222₄
    Four f3({1, 2, 3});  // 123₄
    Four f4("321");       // 321₄

    ASSERT_EQ(toString(f2), "222");
    ASSERT_EQ(toString(f3), "123");
    ASSERT_EQ(toString(f4), "321");
}

// Тест 2: Сложение без переноса
TEST(FourTest, simple_add) {
    Four a({1, 2, 0});  // 120₄ = 24₁₀
    Four b({2, 1});     // 21₄ = 9₁₀
    Four c = a.add(b);
    ASSERT_EQ(toString(c), "201"); 
}

// Тест 3: Сложение с переносом
TEST(FourTest, add_with_carry) {
    Four a({3, 3}); // 15₁₀
    Four b({3});    // 3₁₀
    Four c = a.add(b);
    ASSERT_EQ(toString(c), "102"); // 18₁₀
}

// Тест 4: Простое вычитание
TEST(FourTest, simple_minus) {
    Four a({3, 2, 1});
    Four b({1, 3});
    Four c = a.minus(b);
    ASSERT_EQ(toString(c), "302"); // ожидается 302₄
}

// Тест 5: Вычитание с заимствованием
TEST(FourTest, minus_with_borrow) {
    Four a({1, 0, 0});
    Four b({1});
    Four c = a.minus(b);
    ASSERT_EQ(toString(c), "33");
}

// Тест 6: Вычитание равных чисел
TEST(FourTest, minus_equal) {
    Four a({2, 1, 3});
    Four b({2, 1, 3});
    Four c = a.minus(b);
    ASSERT_EQ(toString(c), "0");
}

// Тест 7: Удаление ведущих нулей
TEST(FourTest, remove_leading_zeros) {
    Four a({0, 3, 0, 1});
    Four b({2, 3});
    Four c = a.minus(b);
    ASSERT_EQ(toString(c), "212");
}

// Тест 8: Отрицательный результат
TEST(FourTest, negative_result) {
    Four small({1, 2});
    Four large({3, 2, 1});
    EXPECT_THROW(small.minus(large), logic_error);
}

// Тест 9: Сравнение чисел
TEST(FourTest, comparisons) {
    Four a({1, 2}); // 6₁₀
    Four b({1, 2}); // 6₁₀
    Four c({1, 3}); // 7₁₀
    Four d({3});    // 3₁₀

    ASSERT_TRUE(a.is_equal(b));
    ASSERT_TRUE(c.is_more(a));
    ASSERT_FALSE(a.is_less(d)); 
}

// Тест 10: Большие числа и перенос
TEST(FourTest, large_numbers) {
    Four a({3, 3, 3, 3});
    Four b({1});
    Four c = a.add(b);
    ASSERT_EQ(toString(c), "10000");
}

// Тест 11: Некорректные цифры
TEST(FourTest, invalid_digit) {
    EXPECT_THROW(Four(3, 5), logic_error);
}

// Тест 12: Инициализация через initializer_list
TEST(FourTest, initializer_list) {
    Four f({3, 2, 1});
    ASSERT_EQ(toString(f), "321");
}

// Тест 13: Конструктор со строкой
TEST(FourTest, string_constructor) {
    Four f("2301");
    ASSERT_EQ(toString(f), "2301");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
