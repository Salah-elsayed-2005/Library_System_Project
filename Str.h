#ifndef str_h
#define str_h
#include <istream>

namespace OurString {
    class Str {
    private:
        char* ptr;

        // This function calculates the length of a string from the type of "pointer to array of char"
        // It is used internally and not allowed to be called externally, hence it's private.
        int lenLocal(const char* string) const;

    public:
        // Default constructor
        Str();

        // Conversion constructor allows creation of an object using a value of another type.
        // It is used to enable assignment operation like str x = "hi".
        Str(const char* string);

        // Copy constructor allows creating a copy of an object in the same class.
        // It is generally better to pass a reference to a constructor rather than a pointer.
        Str(const Str& obj);

        // Calculates the length of a string from the type Str.
        int len() const;

        // Destructor
        ~Str();

        // Conversion operator returns "ptr" when the object gets called by name only.
        // No return type is specified because it's a conversion operator.
        operator const char* () const;

        // Copy Assignment Operator used for assignment like x = y where x and y are Str objects.
        void operator= (const Str& obj);

        void operator= (const char* string);

        // Concatenates two Str objects.
        Str operator+ (const Str& obj) const;

        // Appends another Str object to this one.
        void operator+= (const Str& obj);

        // Checks if two Str objects are equal.
        bool operator== (const Str& obj) const;

        // Friend function to allow input operations with >> operator.
        // It has access to private and protected members of this class.
        friend std::istream& operator>>(std::istream& is, Str& obj);

        friend Str operator+ (const char* prefix, const Str& obj);
    };
}

#endif
