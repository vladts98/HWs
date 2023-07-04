#include <iostream>
#include <fstream>
#include <vector>

class Observer {
public:
	virtual void onWarning(const std::string& message) {
		std::cout << message << ' ';
	}
	virtual void onError(const std::string& message) {
		std::ofstream fout;
		fout.open("log.txt", std::ios::app);
		fout << message << '\n';
		fout.close();
	}
	virtual void onFatalError(const std::string& message) {
		this->onError(message);
		this->onWarning(message);
	}
};

class Observed {
public:
	~Observed() {
		for (auto ob : observers) {
			delete ob;
		}
	}
	Observed& push_back(Observer* ob) {
		observers.push_back(ob);
		return *this;
	}
	Observed& pop(Observer* observer) {
		auto it = std::remove(observers.begin(), observers.end(), observer);
		observers.erase(it, observers.end());
		return *this;
	}

	void warning(const std::string& message) const {
		for (auto observer : observers) {
			observer->onWarning("onWarning " + message);
		}
	}
	void error(const std::string& message) const {
		for (auto observer : observers) {
			observer->onError("error " + message);
		}
	}
	void fatalError(const std::string& message) const {
		for (auto observer : observers) {
			observer->onFatalError("fatalError " + message);
		}
	}
private:
	std::vector<Observer*> observers;
};

int main()
{
	Observed O;
	O.push_back(new Observer()).push_back(new Observer()).push_back(new Observer()).fatalError("aaa");
}