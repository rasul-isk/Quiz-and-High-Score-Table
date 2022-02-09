//Assignment No:	Lab 5
//Student Name:		Rasul Iskandarov
//Student Number:	C00246498
//Date:				02/02/2022

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <conio.h>

using namespace std;

string quizPath = "res/Files/quiz.txt";
string tablePath = "res/Files/HighScoreTable.txt";

class Question {       

private:         
	static const int answersCount = 4;
	string question;  
	string answers[answersCount];  
	string rightAnswer;


public:
	Question() {
		int index = 0;

		question = "";

		while (index < answersCount)
			answers[index++] = "";

		rightAnswer = "";
	};

	void SetQuestion(string question, string answ[4], string rightAnswer) { 
		int index = 0;
		this->question = question;

		while (index < answersCount)
		{
			answers[index] = answ[index];
			index++;
		}

		this->rightAnswer = rightAnswer;
	}

	void Equalize(Question question)
	{
		int index = 0;

		this->question = question.getQuestion();

		while (index < answersCount)
		{
			this->answers[index] = question.getAnswer(index);
			index++;
		}

		this->rightAnswer = question.getRightAnswer();
	}

	void ShuffleQuestions()
	{
		string temp;
		int size = answersCount;
		int random1 = (rand() % (size));
		int random2 = (rand() % (size));

		if (answers[0] == "")
		{
			cout << "No answers." << endl << endl;
			return;
		}

		if (random1 != random2 && random1 < answersCount && random2 < answersCount)
		{
			temp = this->answers[random1];
			this->answers[random1] = this->answers[random2];
			this->answers[random2] = temp;		
		}
	}

	string getQuestion()
	{
		return question;
	}
	string getAnswer(int index)
	{
		return answers[index];
	}
	string getRightAnswer()
	{
		return rightAnswer;
	}	
};


Question quiz[50];
int objectPosition = 0;

string ReadFile(string path) {
	string data = "";
	string line;
	ifstream file;

	file.open(path);

	if (!file)
	{
		cout << "No file found. File was created by program.";
		ofstream newfile(path);
		newfile << "Rasul Iskandarov.First Line will be ignored." << endl;
		newfile.close();
		return data;
	}

	getline(file, line);

	while (file)
	{
		if (getline(file, line))
		{
			if (line != "" && line != "\n")
			{
				data += line;
				data += "\n";
			}
		}
	}

	file.close();

	return data;
}

void ReadQuiz(string data)
{
	int questionCount = 0;
	int sizeAnswer = 0;
	int numberOfEntries = 0;
	std::istringstream stream{ data };
	std::string line;
	
	getline(stream, line);
	questionCount = stoi(line);
	getline(stream, line);

	sizeAnswer = questionCount * 4;
	numberOfEntries = questionCount * 5;

	while (numberOfEntries>0 && line != "\0" && objectPosition < questionCount) {
		string question = "";
		string rightAnswer = "";
		string* answers = new string[4];
		int index = 0;

		while (line == "\n" || line == "") { getline(stream, line); }
		numberOfEntries--;
		question = line;
		getline(stream, line);

		while (line == "\n" || line == "") { getline(stream, line); }
		numberOfEntries--;
		rightAnswer = line;
		answers[index++] = line;
		getline(stream, line);

		while (line == "\n" || line == "") { getline(stream, line); }
		numberOfEntries--;
		answers[index++] = line;
		getline(stream, line);

		while (line == "\n" || line == "") { getline(stream, line); }
		numberOfEntries--;
		answers[index++] = line;
		getline(stream, line);

		while (line == "\n" || line == "") { getline(stream, line); }
		numberOfEntries--;
		answers[index++] = line;
		getline(stream, line);

		if (question != "" && rightAnswer != "" && answers[3] != "")
			quiz[objectPosition++].SetQuestion(question, answers, rightAnswer);
		else
		{
			cout << "Error occured, while initializing data." << endl;
			break;
		}
	}
}

void printQuiz(int size)
{
	cout << "Quiz:" << endl << endl;
	for (int index = 0; index < size; index++)
	{
		cout << quiz[index].getQuestion() << endl;
		cout << quiz[index].getAnswer(0) << endl;
		cout << quiz[index].getAnswer(1) << endl;
		cout << quiz[index].getAnswer(2) << endl;
		cout << quiz[index].getAnswer(3) << endl;
		cout << endl << "Right Answer: " << quiz[index].getRightAnswer() << endl << endl;
	}

	cout << endl << endl;
}

void printHighScoreTable(string people[], int score[], int size)
{
	ofstream file;
	string data = "";
	ReadFile(tablePath);

	file.open(tablePath, std::ofstream::out | std::ofstream::trunc);

	file << "Rasul Iskandarov.First Line will be ignored." << endl;

	file << "High Score Table" << endl << endl;
	
	for (int index = 0; index < size; index++)
	{
		file << "-----------------------------------------" << endl;
		file << "| Name: " << people[index] << endl;
		file << "| Score: " << score[index] << endl;
		file << "-----------------------------------------" << endl;
	}

	file.close();

}


void Exam(int size, string& people, int& score)
{
	int answer;
	people = "";
	score = 0;

	cout << "Quiz Started..." << endl;
	cout << "Enter Right Answer Number for each of questions." << endl;
	cout << "But at first, please enter your name: ";

	getline(cin, people);
	for (int index = 0; index < size; index++)
	{
		cout << "Question #" << index+1 << " " << quiz[index].getQuestion() << endl << endl;

		cout << "1) " << quiz[index].getAnswer(0) << endl;
		cout << "2) " << quiz[index].getAnswer(1) << endl;
		cout << "3) " << quiz[index].getAnswer(2) << endl;
		cout << "4) " << quiz[index].getAnswer(3) << endl << endl;

		cout << "Right Answer: ";

		cin >> answer;
		cin.ignore();
		answer -= 1;

		if (quiz[index].getAnswer(answer) == quiz[index].getRightAnswer())
		{
			cout << endl << "Correct answer! :)" << endl;
			score++;
		}
		else
		{
			cout << endl << "Wrong answer... :(" << endl;
		}

		if (index + 1 != size)
		{
			cout << "Enter anything to move onto next question.";
			cin.get();
			cin.ignore();
		}
		else
		{
			cout << endl << "Exam is finished!" << endl << endl;
			score *= 10;
			cout << "Your score is " << score << " out of " << size * 10 << endl << endl;
		}
	}
}

void sortArrays(string people[], int score[], int size)
{
	bool sorted = false;
	int tempScore = 0;
	string tempPerson = "";

	while (!sorted)
	{
		sorted = true;
		for (int index = 0; index < size - 1; index++)
		{
			if (score[index] < score[index + 1])
			{
				sorted = false;

				tempScore = score[index];
				score[index] = score[index + 1];
				score[index + 1] = tempScore;

				tempPerson = people[index];
				people[index] = people[index + 1];
				people[index + 1] = tempPerson;

				break;
			}
		}
	}
}

void ShuffleEverything(int size)
{
	Question temp;
	int index = 0;
	srand(time(NULL));

	if (quiz[0].getQuestion() == "")
	{
		cout << "Empty quiz." << endl << endl;
		return;
	}

	while (index < size)
	{
		int randomNum = (rand() % (size));

		if (randomNum != index && randomNum < size)
		{
			temp.Equalize(quiz[index]);
			quiz[index].Equalize(quiz[randomNum]);
			quiz[randomNum].Equalize(temp);

			index++;
		}
	}

	for (index = 0; index < size; index++)
	{
		for(int shufCount = 10; shufCount > 0; shufCount--)
			quiz[index].ShuffleQuestions();
	}

}


int main()
{
	bool menu = true;                  
	int repeat = 0;
	int quizSize = 0;
	string data = ReadFile(quizPath);
	string people[50];
	int score[50];
	int indexOfPeople = 0;

	ReadQuiz(data);
	quizSize = objectPosition;


	while (menu)
	{
		if (repeat)
		{
			cout << ReadFile(tablePath);

			cout << "Do you want to try again?" << endl;
			cout << "0) Exit" << endl;
			cout << "1) Try Again" << endl;
			cin >> repeat;
			cin.ignore();
		}
		else
		{
			repeat = 1;
			ShuffleEverything(quizSize);

			people[indexOfPeople] = "";
			score[indexOfPeople] = 0;

			Exam(quizSize, people[indexOfPeople], score[indexOfPeople]);
			sortArrays(people, score, indexOfPeople + 1);
			printHighScoreTable(people, score, indexOfPeople + 1);

			indexOfPeople++;
			continue;
		}
		switch (repeat)
		{
			default:
				menu = false;
				break;
			case 1: 
				ShuffleEverything(quizSize);

				people[indexOfPeople] = "";
				score[indexOfPeople] = 0;

				Exam(quizSize, people[indexOfPeople], score[indexOfPeople]);
				sortArrays(people, score, indexOfPeople + 1);
				printHighScoreTable(people, score, indexOfPeople + 1);

				indexOfPeople++;
				break;
		}
	}
}