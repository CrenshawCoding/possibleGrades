#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <math.h>

using namespace std;


bool bachelor;
bool master;
double gradeCurrent;
int totalCredits;
int currentCredits;
map<double, double> requiredGrades;

bool getYesOrNoResult() {
	string answer;
	cout << "Type 'y' or 'n'\n";
	cin >> answer;
	if(answer.compare("y") == 0) {
		return true;
	} else if(answer.compare("n") == 0) {
		return false;
	} else {
		cout << "Error: invalid input\n";
		getYesOrNoResult();
	}
}

double calculateRequiredAverageForGrade(double gradeToAchieve) {
	return round((gradeToAchieve * totalCredits) - (gradeCurrent * currentCredits)) / (totalCredits - currentCredits);
}

double calculateBestPossibleGrade() {
	return ((gradeCurrent * currentCredits) + (totalCredits - currentCredits)) / totalCredits;
}

double calculateWorstPossibleGrade() {
	return ((gradeCurrent * currentCredits) + ((totalCredits - currentCredits) * 4.0)) / totalCredits;
}


void setTotalCredits() {
	cout << "Are you enrolled in a bachelor program?\n";
	bachelor = getYesOrNoResult();
	if(bachelor) {
		totalCredits = 180;
		return;
	}
	cout << "Are you enrolled in a masters program?\n";
	master = getYesOrNoResult();
	if(master) {
		totalCredits = 120;
		return;
	}
}

void setCurrentCredits() {
	string answer;
	cout << "Do you have more than 0 Credits in your current program?\n";
	if(!getYesOrNoResult()) {
		currentCredits = 0;
		return;
	}
	cout << "How many credits do you currently have? Please enter a whole number between 0 and " << totalCredits << "\n";
	cin >> answer;
	char * p;
	long answerLong = strtol(answer.data(), NULL, 10);
	if(answerLong > 0 && answerLong <= totalCredits) {
		currentCredits = answerLong;
	} else {
		cout << "The number of Credits you entered is not within 0 and " << totalCredits << ", your total possible credits. Please try again\n";
		setCurrentCredits();
	}
}



void setCurrentGrade() {
	string answer;
	if(currentCredits == 0) return;
	cout << "Please enter your current grade.\n";
	cin >> answer;
	double answerDouble = strtod(answer.data(), NULL);
	if(answerDouble >= 0.7 && answerDouble <= 5.0) {
		gradeCurrent = answerDouble;
	} else {
		cout << "The entered grade " << answer << " is not a valid grade. Please try again\n";
		setCurrentGrade();
	}
}

void generateRequiredGradesMap() {
	for(double i = round(calculateBestPossibleGrade()*10)/10; i <= round(calculateWorstPossibleGrade()*10)/10; i += 0.1) {
		requiredGrades[i] = round(calculateRequiredAverageForGrade(i) * 10)/10;
	}
}

void printRequiredGrades() {
	map<double,double>::iterator it;
	cout << "\n\n";
	for(it = requiredGrades.begin(); it != requiredGrades.end(); it++) {
		cout << it->first 
			 << "\t|\t"
			 << it->second 
			 << endl;
	}
}

void getUserData() {
	setTotalCredits();
	setCurrentCredits();
	setCurrentGrade();
}

int main() {
	getUserData();
	generateRequiredGradesMap();
	printRequiredGrades();
	cout << "Press enter to exit";
	string _;
	cin >> _;
}





