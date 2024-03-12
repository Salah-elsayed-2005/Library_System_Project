#ifndef str_h
#define str_h
#include <istream>
namespace OurString {
	class str {
	private:
		char* ptr;

		/*
			the two "const"s was add to insure that "len_local" won't change or modify anything.
			this function calculates the length of a string from the type of "pointer to array of char"
			this function is only used internally, not allowed to be called. thats why it is private.
		*/
		int len_local(const char* String) const;

	public:

		/*
			default constractor
		*/
		str();

		/*
			When you add "const" to the constractor it is called a "Conversion Constructors", this type of constructor allows us to create an object using one value of another type.
			"const" was added in the constractor to give us the ability to use the assignment operator "="
			this constractor is used do (str x = "hi")
		*/
		str(const char* String);

		/*
			When you add "const" to the constractor it is called a "Conversion Constructors", this tpye of constructor allows us to create an object using one value of another type.
			"const" was added in the constractor to give us the ability to use the assignment operator "="
			this constractor is used do (str x = y), where y an object from class str;
			this is called a copy constractor, it makes a copy of an object and puts it in an object from the same class
			it is better in general to pass a reference to a constractor not a pointer
		*/
		str(const str& obj);

		/*
			this functions calculates the length of a string from the type str
		*/
		int len() const;

		/*
		destractor
		*/
		~str();

		/*
			this operator returns "ptr" when the object gets called by name only.
			we did not put a return type because this is a "conversion operators" and you should not put a return type while dealing with it
		*/
		operator const char* () const;

		/*
			Copy Assignment Operator 
			this is used to make (x = y) where x and y are defined before. and x and y are objects from class str
		*/
		void operator = (const str& obj);

		void operator = (const char* String);

		str operator + (const str& obj) const;

		void operator += (const str& obj);

		bool operator == (const str& obj) const;


		/*
			when you add the word "friend" before a function, the compiler understands that this function is not a method of the current class.
			the operators of ">>" and "<<" take two inputs.
			"friend" keyword is used to say that this function has access to the private and protected data members of this class
			"istream" is the return type of this opperator.
			why can't I make the operators of ">>" and "<<" local operators, we have to make them friend operators.
		*/
		friend std::istream& operator>>(std::istream& is, str& obj);
	};
}

#endif