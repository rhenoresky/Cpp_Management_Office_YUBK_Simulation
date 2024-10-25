#include <iostream>
#include <string>
#include <random>
#include <vector>

using namespace std;

class HelperService
{
public:
	int inputNum(string message, int max)
	{
		int choosen;
		do
		{
			cout << message;
			printf(" (1-%d) : ", max);
			cin >> choosen;
			if (choosen < 1 || choosen > max)
			{
				cout << "Pilihan tidak valid! silahkan pilih kembali" << endl;
			}
			cout << endl;
		} while (choosen < 1 || choosen > max);
		return choosen;
	}

	string generateRandomId()
	{
		const string CHARACTERS = "abcdefghijklmNOPQRSTUPWXYZ0123456789&@%#$";
		random_device rd;
		mt19937 generator(rd());

		uniform_int_distribution<> distribution(
				0, CHARACTERS.size() - 1);

		string randomId;
		for (int i = 0; i < 10; ++i)
		{
			randomId += CHARACTERS[distribution(generator)];
		}

		return randomId;
	}

	int loopingMenus(string message, vector<string> selectedMenus)
	{
		cout << endl;
		cout << message << endl;
		int i = 0;
		for (string menu : selectedMenus)
		{
			cout << ++i << ". " << menu << endl;
		}
		return inputNum("Pilih", selectedMenus.size());
	}

	string selectRole()
	{
		vector<string> roles = {"HR", "CO", "TRAINER", "STUDENT", "STUDENT CANDIDATE"};
		int selectedRole = loopingMenus("Tentukan role", roles);

		switch (selectedRole)
		{
		case 1:
			return "HR";
			break;
		case 2:
			return "CO";
			break;
		case 3:
			return "TRAINER";
			break;
		case 4:
			return "STUDENT";
			break;
		case 5:
			return "STUDENT CANDIDATE";
			break;
		default:
			return "!VALID";
			break;
		}
	}

	tm createStructTmTimeNow()
	{
		time_t now = time(0);
		tm structTm = *localtime(&now);
		return structTm;
	}
};