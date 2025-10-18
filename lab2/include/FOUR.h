#ifndef FOUR_H
#define FOUR_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>

using namespace std;

class Four {
private:
    size_t arraysize;
    unsigned char* data;

    void remove_zeros();

public:
    Four();                                         
    Four(const size_t& arraysize, unsigned char value); 
    Four(const initializer_list<unsigned char>& lst); 
    Four(const string& sourceString);          
    Four(const Four& other);                        
    Four(Four&& other) noexcept;                 
    ~Four() noexcept;                  

    Four add(const Four& other);
    Four minus(const Four& other);

    bool is_less(const Four& other) const;
    bool is_more(const Four& other) const;
    bool is_equal(const Four& other) const;

    ostream& print(std::ostream& os) const;
};

#endif
