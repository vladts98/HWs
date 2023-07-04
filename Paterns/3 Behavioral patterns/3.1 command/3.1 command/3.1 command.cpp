#include <iostream>
#include <fstream>

class LogCommand {
public:
	virtual ~LogCommand() = default;
	virtual void print(const std::string& message) = 0;
};

class LogCommandFile : public LogCommand {
public:
	void print(const std::string& message, const std::string& path = "log.txt") {
		std::ofstream fout;
		fout.open(path, std::ios::app);
		fout << message << '\n';
		fout.close();
	}
private:
	void print(const std::string& message) override {}
};

class LogCommandConsole : public LogCommand {
public:
	void print(const std::string& message) override {
		std::cout << message << '\n';
	}

};

int main()
{
	LogCommandConsole Lc;
	Lc.print("command");

	LogCommandFile Lf;
	Lf.print("command", "log.txt");
}