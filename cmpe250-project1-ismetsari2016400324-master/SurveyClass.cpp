#include "SurveyClass.h"

SurveyClass::SurveyClass()
{
	members = new LinkedList();

}

SurveyClass::SurveyClass(const SurveyClass & other)
{
	cout << "SurveyClass Copy constructor is called " << endl;
	members = new LinkedList(*(other.members));
}

SurveyClass & SurveyClass::operator=(const SurveyClass & list)
{
	cout << "SurveyClass = operator is called " << endl;
	delete members;
	members = new LinkedList(*(list.members));
	return *this;
}

SurveyClass::SurveyClass(SurveyClass && other)
{
	cout << "SurveyClass Move constructor is called " << endl;
	members = move(other.members);
	other.members = NULL;
}

SurveyClass & SurveyClass::operator=(SurveyClass && list)
{
	cout << "SurveyClass Move = operator is called " << endl;
	delete members;
	members = move(list.members);
	list.members = NULL;
	return *this;
}

SurveyClass::~SurveyClass()
{
	cout << "SurveyClass Destructor is called " << endl;
	delete members;
}
float round2(float var) {

	int value = (int)(var * 100);
	return float(value) / 100;
}
void SurveyClass::handleNewRecord(string _name, float _amount)
{
	Node* temphead = members->head;
	while (temphead != NULL) {
		if (temphead->name == _name) {
			temphead->amount = _amount;
			return;
		}
		temphead = temphead->next;
	}
	members->pushTail(_name, _amount);

}

float SurveyClass::calculateMinimumExpense()
{
	float minvalue = members->head->amount;
	Node* current = members->head;
	while (current != NULL) {
		if (current->amount < minvalue) {
			minvalue = current->amount;
		}
		current = current->next;
	}
	return round2(minvalue);
}

float SurveyClass::calculateMaximumExpense()
{

	float maxvalue = members->head->amount;
	Node* current = members->head;
	while (current != NULL) {
		if (current->amount > maxvalue) {
			maxvalue = current->amount;
		}
		current = current->next;
	}
	return round2(maxvalue);
}

float SurveyClass::calculateAverageExpense()
{
	float totalvalue = 0.0;
	Node* current = members->head;
	while (current != NULL) {
		totalvalue = totalvalue + current->amount;
		current = current->next;
	}
	float averagevalue = totalvalue / members->length;
	return round2(averagevalue);
}