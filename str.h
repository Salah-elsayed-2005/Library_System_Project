#ifndef str_h
#define str_h
/*
	Documentation

 	str x; will declare an object of class str called x
  	str x = "hi"; will work as expected.
  	str x = y; will initialize an object of class str and will copy y in x, y has to be an object of class str
   	x = y; will copy y in x, and y must be of class str
	x == y; will return a true or false, the returned value will be ture iff x and y are two identical strings
	x.len(); will return the length of the string.
 
 	writing "x" will return the value of object x, that means "cout << x" will work as expected.

	I did not implement "cin >> x" yet because it got a couple of problems.
*/




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
			When you add "const" to the constractor it is called a "Conversion Constructors", this tpye of constructor allows us to create an object using one value of another type.
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
			this is used to make (x = y) where x and y are defined before. and x and y are objects from class str
		*/
		void operator = (str obj);

		bool operator == (str obj);
	};
}

#endif
