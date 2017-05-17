// Tamagotchi-Klon

using namespace std;
#include <iostream>
#include <string>
#include <fstream>

class virtualAnimal {

	private:
		string name;
		int foodPercentage;
		int cleanlinessPercentage;
		int funPercentage;
		int sleepPercentage;
		int healthPercentage;

	public:

		virtualAnimal(string name_in = "noName") {
			name = name_in;
			foodPercentage = 100;
			cleanlinessPercentage = 100;
			funPercentage = 100;
			sleepPercentage = 100;
			healthPercentage = 100;
		}

		virtualAnimal(string name_in, int food_in, int clean_in, int fun_in, int sleep_in, int health_in) {
			name = name_in;
			foodPercentage = food_in;
			cleanlinessPercentage = clean_in;
			funPercentage = fun_in;
			sleepPercentage = sleep_in;
			healthPercentage = health_in;
		}

		void save(string userName) {
			ofstream saveFile;
			saveFile.open("saveFile.txt", ios::trunc);
			saveFile << userName << "\n";
			saveFile << name << "\n";
			saveFile << foodPercentage << "\n";
			saveFile << cleanlinessPercentage << "\n";
			saveFile << funPercentage << "\n";
			saveFile << sleepPercentage << "\n";
			saveFile << healthPercentage << "\n";
			saveFile.close();
		}

		void getAllValues() {
			cout << endl << endl << name << endl;
			cout << "Food: " << foodPercentage << "%" << endl;
			cout << "Cleanliness: " << cleanlinessPercentage << "%" << endl;
			cout << "Fun: " << funPercentage << "%" << endl;
			cout << "Sleep: " << sleepPercentage << "%" << endl;
			cout << "Health: " << healthPercentage << "%" << endl;
		}

		bool checkStats(string userInput_action) {

			if (healthPercentage < 10) {

				if (userInput_action == "MEDICINE") {
					return true;
				}

				cout << endl << "You need to give some medicine to your animal, it's health is too low." << endl;
				return false;
			}

			if (cleanlinessPercentage < 10) {

				if (userInput_action == "CLEAN") {
					return true;
				}

				cout << endl << "You need to clean your pet, it's too dirty." << endl;
				return false;
			}

			if (funPercentage < 10) {

				if (userInput_action == "PLAY") {
					return true;
				}

				cout << endl << "You need to play with your animal, it is bored." << endl;
				return false;
			}

			if (sleepPercentage < 10) {

				if (userInput_action == "SLEEP") {
					return true;
				}

				cout << endl << "You need to let your pet sleep, it's exhausted." << endl;
				return false;
			}

			if (foodPercentage < 10) {

				if (userInput_action == "FEED") {
					return true;
				}

				cout << endl << "You need to feed your pet, it's hungry." << endl;
				return false;
			}

			return true;
		}

		void changeName(string newName) {
			name = newName;
		}

		void feed() {

			if (foodPercentage >= 80) {
				foodPercentage = 100;
			}
			else {
				foodPercentage += 20;
			}

			if (sleepPercentage < 5) {
				sleepPercentage = 0;
			}
			else {
				sleepPercentage -= 5;
			}

			if (cleanlinessPercentage < 10) {
				cleanlinessPercentage = 0;
			}
			else {
				cleanlinessPercentage -= 10;
			}
		}

		void clean() {

			if (cleanlinessPercentage >= 75) {
				cleanlinessPercentage = 100;
			}
			else {
				cleanlinessPercentage += 25;
			}

			if (sleepPercentage < 10) {
				sleepPercentage = 0;
			}
			else {
				sleepPercentage -= 10;
			}

			if (funPercentage < 5) {
				funPercentage = 0;
			}
			else {
				funPercentage -= 5;
			}
		}

		void play() {

			if (funPercentage >= 80) {
				funPercentage = 100;
			}
			else {
				funPercentage += 20;
			}

			if (sleepPercentage < 15) {
				sleepPercentage = 0;
			}
			else {
				sleepPercentage -= 15;
			}

			if (healthPercentage < 10) {
				healthPercentage = 0;
			}
			else {
				healthPercentage -= 10;
			}
		}

		void sleep() {

			if (sleepPercentage >= 70) {
				sleepPercentage = 100;
			}
			else {
				sleepPercentage += 30;
			}

			if (cleanlinessPercentage < 5) {
				cleanlinessPercentage = 0;
			}
			else {
				cleanlinessPercentage -= 5;
			}

			if (foodPercentage < 20) {
				foodPercentage = 0;
			}
			else {
				foodPercentage -= 20;
			}
		}

		void giveMedicine() {

			if (healthPercentage >= 75) {
				healthPercentage = 100;
			}
			else {
				healthPercentage += 25;
			}

			if (funPercentage < 30) {
				funPercentage = 0;
			}
			else {
				funPercentage -= 30;
			}

			if (cleanlinessPercentage < 5) {
				cleanlinessPercentage = 0;
			}
			else {
				cleanlinessPercentage -= 5;
			}
		}

		void changeValuesAbsence() {

			if (foodPercentage < 25) {
				foodPercentage = 0;
			}
			else {
				foodPercentage -= 25;
			}

			if (funPercentage < 50) {
				funPercentage = 0;
			}
			else {
				funPercentage -= 50;
			}

			if (sleepPercentage > 50) {
				sleepPercentage = 100;
			}
			else {
				sleepPercentage += 50;
			}

			if (cleanlinessPercentage < 20) {
				cleanlinessPercentage = 0;
			}
			else {
				cleanlinessPercentage -= 20;
			}

			if (healthPercentage < 10) {
				healthPercentage = 0;
			}
			else {
				healthPercentage -= 10;
			}

		}

};

int main() {

	string userInput;
	string animalName;
	string userName;
	string userInput_action;
	virtualAnimal userAnimal;
	bool loadedGame = false;

	cout << "Hello, nice to meet you!" << endl;
	cout << "Do you want to load a saved game? Yes/No" << endl;
	cin >> userInput;

	if (userInput == "Yes") {

		string helpString_food;
		string helpString_clean;
		string helpString_fun;
		string helpString_sleep;
		string helpString_health;

		ifstream savedFile("saveFile.txt");

		if (savedFile.is_open() == true) {

			getline(savedFile, userName);
			getline(savedFile, animalName);
			getline(savedFile, helpString_food);
			getline(savedFile, helpString_clean);
			getline(savedFile, helpString_fun);
			getline(savedFile, helpString_sleep);
			getline(savedFile, helpString_health);
			savedFile.close();

			virtualAnimal userAnimal(animalName, std::stoi(helpString_food), std::stoi(helpString_clean), std::stoi(helpString_fun), std::stoi(helpString_sleep), std::stoi(helpString_health));
			cout << endl << "Welcome back " << userName << "!" << endl;
			cout << animalName << "'s stats changed while you were gone." << endl;
			cout << endl << "New stats: " << endl;
			userAnimal.changeValuesAbsence();
			userAnimal.getAllValues();
			loadedGame = true;

		}

		else {
			cout << "Loading failed. Please close the application and try again." << endl;
			cout << "Please press any key and enter to close the programm." << endl;
			cin >> userInput;
			return 0;
		}
	}

	if (loadedGame == false) {

		do {
			cout << endl << "Do you want to take care of your own little animal? Yes/No" << endl;
			cin >> userInput;

			if (userInput != "No" && userInput != "Yes") {
				cout << "I'm sorry, I didn't understand that. Please make sure you don't have any typos in your answer." << endl;
			}

		} while (userInput != "No" && userInput != "Yes");

		if (userInput == "No" || userInput == "no") {
			cout << endl << "Okay then, have a nice day!" << endl;
			cout << "Please press any key and enter to close the programm." << endl;
			cin >> userInput;
			return 0;
		}

		else {
			cout << endl << "What is your name, human?" << endl;
			cin >> userName;
			cout << endl << "Nice to meet you " << userName << "!" << endl;

			cout << "How do you want to call your little animal pal?" << endl;
			cin >> animalName;

			userAnimal.changeName(animalName);
			cout << endl << "----------------------" << endl << endl;
			cout << "Hi " << userName << ", nice to meet you! I'm " << animalName << ", your new animal best friend." << endl;

		}

	}

	do {

		cout << endl << "----------------------" << endl << endl;
		cout << "What do you want to do now, " << userName << "?" << endl;
		cout << "If you want to feed me, say FEED." << endl;
		cout << "If you want to wash me, say CLEAN." << endl;
		cout << "If you want to play with me, say PLAY." << endl;
		cout << "If you want me to sleep, say SLEEP." << endl;
		cout << "If you want to give me some medicine, say MEDICINE." << endl;
		cout << "If you want to see my current stats, say STATS." << endl;
		cout << "And last but not least: If you want to exit, say EXIT." << endl << endl;
		cin >> userInput_action;

		if (userInput_action == "FEED") {

			if (userAnimal.checkStats(userInput_action) == true) {
				userAnimal.feed();
				cout << endl << "----------------------" << endl << endl;
				cout << animalName << " has just been fed. Food +20, Sleep -5, Cleanliness -10." << endl;
				cout << endl << "New stats: " << endl;
				userAnimal.getAllValues();
			}

		}

		else if (userInput_action == "CLEAN") {

			if (userAnimal.checkStats(userInput_action) == true) {
				userAnimal.clean();
				cout << endl << "----------------------" << endl << endl;
				cout << animalName << " has just been bathed. Cleanliness +25, Sleep -10, Fun -5." << endl;
				cout << endl << "New stats: " << endl;
				userAnimal.getAllValues();
			}

		}

		else if (userInput_action == "PLAY") {

			if (userAnimal.checkStats(userInput_action) == true) {
				userAnimal.play();
				cout << endl << "----------------------" << endl << endl;
				cout << "You just played with " << animalName << ". Fun +20, Sleep -15, Health -10." << endl;
				cout << endl << "New stats: " << endl;
				userAnimal.getAllValues();
			}

		}

		else if (userInput_action == "SLEEP") {

			if (userAnimal.checkStats(userInput_action) == true) {
				userAnimal.sleep();
				cout << endl << "----------------------" << endl << endl;
				cout << animalName << " just took a nap. Sleep +30, Cleanliness -5, Food -20." << endl;
				cout << endl << "New stats: " << endl;
				userAnimal.getAllValues();
			}

		}

		else if (userInput_action == "MEDICINE") {

			if (userAnimal.checkStats(userInput_action) == true) {
				userAnimal.giveMedicine();
				cout << endl << "----------------------" << endl << endl;
				cout << animalName << " just took some medicine. Health +25, Fun -30, Cleanliness -5." << endl;
				cout << endl << "New stats: " << endl;
				userAnimal.getAllValues();
			}

		}

		else if (userInput_action == "STATS") {
			cout << endl << "----------------------" << endl << endl;
			userAnimal.getAllValues();
		}

		else {
			cout << endl << "----------------------" << endl << endl;
			cout << "I'm sorry, I didn't get that, did you make a typo?" << endl;
		}

	} while (userInput_action != "EXIT");

	cout << "Do you want to save before you exit? Yes/No" << endl;
	cin >> userInput;

	if (userInput == "Yes") {
		userAnimal.save(userName);
	}

	return 0;
}