/*
 * Author Raveen Karnik
 * Date: 12-15-17
 * This program allows user to add and remove students from a linked list of students
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "Node.h"
#include "Student.h"
using namespace std;

//recursively go through to find the student who would come before the new one being added
Node* recursiveAdd(Node* node, int id)
{
	if (node == NULL) return NULL;
	if(node->getNext() != NULL && node->getNext()->getStudent()->getId() < id)
	{
		return recursiveAdd(node->getNext(), id);
	}
	else
	{
		return node;
	}
}

//add student function
void addStudent(Node* &head)
{
	//define variables for the new student
	char* firstName = new char[80];
	char* lastName = new char[80];
	int id;
	float gpa;

	//prompt user for all information on student
	cout << "Enter student's first name." << endl;
	cin >> firstName;
	cout << "Enter student's last name." << endl;
	cin >> lastName;
	cout << "Enter student's ID Number." << endl;
	cin >> id;
	cout << "Enter student's GPA." << endl;
	cin >> gpa;

	//create new node and student with the given variables
	Student* student = new Student(firstName, lastName, id, gpa);
	Node* node = new Node(student);

	//add node to linked list
	if(head == NULL)
	{
		head = node;
		node->setNext(NULL);
	}
	else if(head->getStudent()->getId() > id)
	{
		node->setNext(head);
		head = node;
	}
	else
	{
		Node* before = recursiveAdd(head, id);
		node->setNext(before->getNext());
		before->setNext(node);
	}
}

//go through all students and print their information
void printStudent(Node* node)
{
	if(node == NULL) return;
	cout << node->getStudent()->getFirst() << " " << node->getStudent()->getLast() << ": ";
	cout << node->getStudent()->getId() << ", " << setprecision(2) << fixed << node->getStudent()->getGpa() << endl;
	if(node->getNext() != NULL)
	{
		printStudent(node->getNext());
	}
}

//delete student function; boolean so user can know if the student was deleted
bool deleteStudent(Node* prevNode, Node* node, int id, Node* &head)
{
	if (node == NULL) return false;
	if(id < node->getStudent()->getId())
	{
		return false;
	}
	else if(id == node->getStudent()->getId())
	{
		if(prevNode != NULL) prevNode->setNext(node->getNext());
		if(node == head) head = node->getNext();
		delete node;
		return true;
	}
	else
	{
		if(node->getNext() == NULL)
		{
			return true;
		}
		else
		{
			return deleteStudent(node, node->getNext(), id, head);
		}
	}
}

//average gpa function; averages the gpa of all students and returns the result
void averageGpa(Node* node, float totalGpa, int number)
{
	if(node == NULL) return;
	totalGpa += node->getStudent()->getGpa();
	number++;
	if(node->getNext() != NULL)
	{
		averageGpa(node->getNext(), totalGpa, number);
	}
	else
	{
		float average = totalGpa/number;
		cout << "The average GPA of all students is " << setprecision(2) << fixed << average << ".";
		cout << endl << endl;
	}
}

//main code block
int main()
{
	//define variables to be used
	Node* head = NULL;
	char input[8];

	//general loop to stay true until the user signals to quit
	bool keepGoing = true;
	while(keepGoing)
	{
		//prompt user to add, print, or delete student(s), calling the corresponding function
		cout << "\"ADD\", \"PRINT\", or \"DELETE\" student(s)?" << endl;
		cout << "Type \"AVERAGE\" to average the students' GPAs or \"QUIT\" to exit." << endl;
		cin >> input;

		//if the user wants to add a student, add that student and print that they have been added
		if(strcmp(input, "ADD") == 0 || strcmp(input, "add") == 0)
		{
			addStudent(head);
			cout << "Student Added." << endl << endl;
		}
		
		//if the user wants to prints students, print them all and notify when complete
		else if(strcmp(input, "PRINT") == 0 || strcmp(input, "print") == 0)
		{
			printStudent(head);
			cout << "All Students Printed." << endl << endl;
		} 
		
		//if the user wants to delete a student, attempt to delete that student
		else if(strcmp(input, "DELETE") == 0 || strcmp(input, "delete") == 0)
		{
			cout << "What is the ID of the student you'd like to delete?" << endl;
			int idNumber;
			cin >> idNumber;
			//depending on what deleteStudent returns, notify the user of what happened
			if(deleteStudent(NULL, head, idNumber, head))
			{
				cout << "Selected Student Deleted." << endl << endl;
			} else
			{
				cout << "Given Student was not Found." << endl << endl;
			}
		}
		
		//if the user wants to quit, set the boolean to false, closing the while loop
		else if(strcmp(input, "QUIT") == 0 || strcmp(input, "quit") == 0)
		{
			keepGoing = false;
		}

		//if the user wants to average the GPAs, do so
		else if(!strcmp(input, "AVERAGE") || !strcmp(input, "average"))
		{
			averageGpa(head, 0, 0);
		}
		
		//indicate confusion with any other input
		else
		{
			cout << "Sorry, I couldn't understand that." << endl << endl;
		}
	}
	return 0;
}
