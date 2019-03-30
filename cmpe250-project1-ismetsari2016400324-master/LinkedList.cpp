#include "LinkedList.h"
LinkedList::LinkedList() {
	head = NULL;
	tail = NULL;
	length = 0;
}

LinkedList::LinkedList(const LinkedList & list)
{
	cout << "LinkedList Copy constructor is called " << endl;
	head = new Node(*list.head);
	tail = new Node(*list.tail);
	length = list.length;
}
LinkedList & LinkedList::operator=(const LinkedList & list)
{
	cout << "LinkedList Operator assignment is called " << endl;
	delete head;
	delete tail;
	head= new Node(*list.head);
	tail= new Node(*list.tail);
	length = list.length;
	return *this;
}


LinkedList::LinkedList(LinkedList&& list) {
	cout << "LinkedList Move constructor is called " << endl;
	this->head = move(list.head);
	this->tail=move(list.tail);
	this->length = move(list.length);

	list.head=NULL;
	list.tail=NULL;
	list.length = 0;

}
LinkedList & LinkedList::operator=(LinkedList && list)
{
	cout << "LinkedList   Move operetor is called " << endl;
	delete head;
	delete tail;
	this->head = move(list.head);
	this->tail=move(list.tail);
	this->length = move(list.length);

	list.head=NULL;
	list.tail=NULL;
	list.length = 0;


	return *this;
}

LinkedList::~LinkedList() {
	cout << "LinkedList destructor is called " << endl;
	delete head;
	length = 0;
}
void LinkedList::pushTail(string _name, float _amount) {
	Node *newone = new Node(_name, _amount);
	if (head == NULL) {
		head = newone;
		tail = newone;
	}
	else {
		Node *current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newone;
		tail = newone;
	}
	this->length++;


}
void LinkedList::updateNode(string _name, float _amount) {
	Node* current = head;
	while (current->name != _name) {

		current = current->next;
	}
	current->amount = _amount;

}