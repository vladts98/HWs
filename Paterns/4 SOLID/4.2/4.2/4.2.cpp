#include <fstream>

class Printable
{
public:
	Printable(const std::string& data, const std::string& format) : data_(data), format_(format) {}
	virtual ~Printable() = default;
	virtual std::string print() const = 0;
	std::string format() {
		return format_;
	}
protected:
	std::string format_; //тут можно создать объект enum или как в оригинале или отдельым классом
	std::string data_;
};


class kText : public Printable {
public:
	kText(const std::string& data) : Printable(data, "kText") {}
	std::string print() const override {
		return data_;
	}
};


class kHTML : public Printable {
public:
	kHTML(const std::string& data) : Printable(data, "kHTML") {}
	std::string print() const override {
		return "<html>" + data_ + "<html/>";
	}
};

class kJSON : public Printable {
public:
	kJSON(const std::string& data) : Printable(data, "kJSON") {}
	std::string print() const override {
		return "{ \"data\": \"" + data_ + "\"}";
	}
};

void saveTo(std::ofstream& file, const Printable& printable)
{
	file << printable.print();
}

void save(std::ofstream& file, const Printable& printable) {
	saveTo(file, printable);
}
