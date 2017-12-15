//student object constructor
#ifndef STUDENTH
#define STUDENTH
#include <iostream>
class Student
{
	public:
		char* getFirst() { return firstName; }
		char* getLast() { return lastName; }
		int getId() { return id; }
		float getGpa() { return gpa; }
		Student(char* first, char* last, int newId, float newGpa)
		{
			firstName = first;
			lastName = last;
			id = newId;
			gpa = newGpa;
		}
		~Student()
		{
			delete firstName;
			delete lastName;
		}
	private:
		char* firstName;
		char* lastName;
		int id;
		float gpa;
};
#endif

