#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "array.h"


#define RED      "\033[91m"
#define GREEN    "\033[92m"
#define RESET    "\033[0m"


// These are the correct values we should get after each test
size_t           ok1_1        = 1; 
size_t           ok1_2        = 3; 
vector<string>   ok2          = { "elem1", "elem2", "elem3" };  
vector<string>   ok4          = { "elem1", "hello", "elem3" };
vector<int>      ok5          = { 0, 10, 20, 30, 40 };
#ifdef HAS_INITIALIZER
Array<double>    tabd         = { 1.0, 2.0, 3.0, 4.0, 5.0 };
vector<double>   ok6          = { 1.0, 2.0, 3.0, 4.0, 5.0 };
#endif


/** 
 * Redefinition of << to display a vector with the same format 
   as the Array operator<< output.
 **/
template <typename T>
std::ostream & operator<<(ostream & os, vector<T> & vect ) {
    os << "[";
    size_t len = vect.size();
    for( size_t position=0; position<len; ++position ) {
        os << vect[position];
        if ( position < len-1 ) os << ", ";
    }
    return os << "]";
}

/**
 * Utility to check on the Array contents (actual) with the 
 * reference (good). Performs an element-wise comparison,
 * prints out a green * for each correct element, a red x 
 * otherwise.
 * Assume actual and good have same size.
 * return: true if all elements are equal, false otherwise. 
 **/
template <typename T>
bool check_array(Array<T> & actual, vector<T> & good)  {
bool ok(true);
      cout << "\tcheckarray: ";
        for (size_t i=0; i<good.size(); i++) {
          if (good[i] != actual[i]) {
            cout << RED << "x";
                cout << "(" << good[i] << "!=" << actual[i] <<")";
                ok = false;
          }
          else
                cout << GREEN << "*";
        }
        cout << RESET << endl;
        return ok;
}

/**
 * main
 **/
int main( int argc, char * argv[] ) {
    std::string color;

    // == Test 1 ==
    size_t actual_size;
    cout << "--> Test base constructor " << endl;
    // An array with default type : test default template parameters      
    Array<> tabdef;
    actual_size = tabdef.size();
    actual_size == ok1_1 ? color = GREEN : color = RED; 
    cout << "\ttabdef.size() should be " << ok1_1 << ": is " << color << tabdef.size() << RESET << endl;

    // An array of strings : test constructor with type and size specified
    Array<string> tabstr(ok1_2);
    actual_size = tabstr.size();
    actual_size == ok1_2 ? color = GREEN : color = RED; 
    cout << "\ttabstr.size() should be " << ok1_2 << ": is " << color << tabstr.size() << RESET << endl;

    // == Test 2 ==
    // Array access : test operator[]
    cout << "--> Test access : operator[] " << endl;
    for (size_t i=0; i<3; i++)
          tabstr[i] = ok2[i];
    // now check values are correctly extracted with operator[] 
    // result
    for (size_t i=0; i<3; i++) {
          auto actual_val = tabstr[i];
          actual_val == ok2[i] ? color = GREEN : color = RED; 
          cout << "\ttabstr[" << i << "] should be " << ok2[i] << " : is " << color << actual_val << RESET << endl;
     }

    // Array display : test operator<<
    cout << "--> Test Array display : operator<< " << endl;
    // result
    cout << "\ttabstr should be [elem1, elem2, elem3], is : " << tabstr << endl; 
 
    // == Test 4 ==
    // A copy of first array : test operator=
    cout << "--> Test array assignment : operator= " << endl;
    Array<string> copy;
    copy = tabstr;
    copy[1] = "hello";
    // result
    check_array( copy, ok4 ) ? color = GREEN : color = RED;
    cout << "\tcopy should be " << ok4  << ": is " <<  color << copy << RESET << endl;

    // == Test 5 == 
    // Array illegal access
    cout << "--> Test illegal access with operator[] " << endl;
    cout << "\texception expected for access to tabint[5], tabint stays unchanged." << endl;
    Array<int> tabint( 5 );

    // Array illegal access 
    // Will avoid segfault ONLY IF you handle this case by
    // throwing std::out_of_range exception
    size_t position { 0 };
    try {
        while( true ) {
            tabint[ position ] = position * 10;
                position++;
        }
    } catch( out_of_range & e ) {
        cout << "\t" << GREEN << e.what() << RESET << endl;
    }
    // result
    check_array( tabint, ok5 ) ? color = GREEN : color = RED;
    cout << "\ttabint should be " << ok5 << " is : " << color << tabint << RESET << endl; 

    // Array construction with initialization list
    // Will compile ONLY IF you have defined a constructor accepting a list-initializer
#ifdef HAS_INITIALIZER
    cout << "--> Test constructor with initializer list" << endl;
    check_array( tabd, ok6 ) ? color = GREEN : color = RED;
    cout << "\ttabd should be " << ok6 << " is : " << color << tabd << RESET << endl;
#endif

    return 0;
}
