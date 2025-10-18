#include "../include/FOUR.h"
#include <iostream>
#include <algorithm>
#include <initializer_list>

using namespace std;


void Four::remove_zeros() {
    if (!data || !arraysize) {
        return;
    }

    size_t first_valid = arraysize;
    while (first_valid > 0 && data[first_valid - 1] == 0) {
        first_valid--;
    }
    
    if (!first_valid) {
        delete[] data;
        arraysize = 1;
        data = new unsigned char[1];
        data[0] = 0;
        return;
    }
    
    if (first_valid > 0) {
        size_t new_size = first_valid;
        unsigned char* new_data = new unsigned char[new_size];
        
        for (size_t i = 0; i < new_size; ++i) {
            new_data[i] = data[i];
        }
            
        delete[] data;
        this->data = new_data;
        this->arraysize = new_size;
    }
}
    
Four::Four() : arraysize(0), data(nullptr) {}

Four::Four(const size_t& arraysize, unsigned char value) {
    if (value > 3) {
        throw logic_error("Число содержит нечетверичные цифры: " + to_string(value));
    }
    this->arraysize = arraysize;
    this->data = new unsigned char[arraysize];
    
    for (size_t i = arraysize; i > 0; --i) {
        this->data[i - 1] = value;
    }
    remove_zeros();
}

Four::Four(const initializer_list<unsigned char>& lst) {
    this->arraysize = lst.size();
    this->data = new unsigned char[arraysize];
    
    size_t index = arraysize;
    for (const auto& value : lst) {
        
        if (value < 0 && value > 3) {        
            delete[] this->data;
            throw logic_error("Число содержит нечетверичные цифры: " + to_string(value));
        }
        this->data[index - 1] = value;
        --index;
    }
    remove_zeros();
}

Four::Four(const string& sourceString) {
    this->arraysize = sourceString.size();
    this->data = new unsigned char[arraysize];
    
    if (this->arraysize == 0) {
        this->arraysize = 1;
        this->data = new unsigned char[1];
        this->data[0] = 0;
        return;
    }

    this->data = new unsigned char[arraysize];
    
    for (size_t i = 0; i < arraysize; ++i) {
        char c = sourceString[i];
        
        if (c < '0' || c > '3') {
            delete[] this->data; 
            throw logic_error(string("Строка содержит нечетверичные цифры: ") + c);
        }
        
        this->data[arraysize - 1 - i] = static_cast<unsigned char>(c - '0');
    }
    remove_zeros();
}

Four::Four(const Four& other) {
    this->arraysize = other.arraysize;
    this->data = new unsigned char[arraysize];
    
    for (size_t i = 0; i < arraysize; ++i) {
        this->data[i] = other.data[i];
    }
}

Four::Four(Four&& other) noexcept {    
    this->arraysize = other.arraysize;
    this->data = other.data;
    
    other.arraysize = 0;
    other.data = nullptr;
}


Four Four::add(const Four& other) {
    size_t max_size = (arraysize > other.arraysize) ? arraysize : other.arraysize;
    size_t result_size = max_size + 1;
    unsigned char* result_data = new unsigned char[result_size]();

    int carry = 0;

    for (size_t i = 0; i < result_size; ++i) {
        unsigned char digit1 = (i < arraysize) ? this->data[i] : 0;
        unsigned char digit2 = (i < other.arraysize) ? other.data[i] : 0;

        int sum_value = digit1 + digit2 + carry;
        carry = sum_value / 4;

        result_data[i] = sum_value % 4;
    }

    Four result;
    result.arraysize = result_size;
    result.data = result_data;
    result.remove_zeros();
    
    return result;
}

bool Four::is_less(const Four& other) const {
    if (arraysize != other.arraysize) {
        return arraysize < other.arraysize;
    }
    
    for (size_t i = arraysize; i > 0; --i) {
        if (data[i - 1] != other.data[i - 1]) {
            return data[i - 1] < other.data[i - 1];
        }
    }
    return false;
}

bool Four::is_more(const Four& other) const {
    return !(is_less(other) || is_equal(other));
}

Four Four::minus(const Four& other) {
    if (this->is_less(other)) {
        throw logic_error("Результат вычитания отрицательный");
    }
    
    if (this->is_equal(other)) {
        return Four(1, 0);
    }
    
    size_t result_size = arraysize;
    unsigned char* result_data = new unsigned char[result_size]();
    
    int borrow = 0;
    
    for (size_t i = 0; i < result_size; ++i) {
        size_t index_other = (i < other.arraysize) ? i : -1;
        
        int digit_this = this->data[i];
        int digit_other = (index_other != -1) ? other.data[index_other] : 0;
        
        int diff = digit_this - digit_other - borrow;
        
        if (diff < 0) {
            diff += 4;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result_data[i] = diff;
    }
    
    Four result;
    result.arraysize = result_size;
    result.data = result_data;
    result.remove_zeros();
    
    return result;
}

bool Four::is_equal(const Four& other) const {
    if (arraysize != other.arraysize) {
        return false;
    }
    for (size_t i = 0; i < arraysize; i++) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
    
}

ostream& Four::print(ostream& outputStream) const {
    for (size_t i = arraysize; i > 0; --i) {
        outputStream << (char)('0' + data[i - 1]);
    }
    return outputStream;
}

Four::~Four() noexcept {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    
    arraysize = 0;
}