#include <iostream>
#include <list>
#include <fstream>

class LogMessage {
public:
	LogMessage(const std::string& m) : text{ m } {}
	enum class Type {
		_FatalError,
		_Error,
		_Warning,
		_UnkownError,
	};
	virtual Type type() const = 0;
	virtual const std::string& message() const final {
		return text;
	}
	virtual ~LogMessage() = default;
private:
	std::string text;
};

class FatalError : public LogMessage {
public:
	FatalError(const std::string& m) : LogMessage(m) {};
	Type type() const override {
		return LogMessage::Type::_FatalError;
	}
};

class Warning : public LogMessage {
public:
	Warning(const std::string& m) : LogMessage(m) {}
	Type type() const override {
		return LogMessage::Type::_Warning;
	}
};

class Error : public LogMessage {
public:
	Error(const std::string& m) : LogMessage(m) {}
	Type type() const override {
		return LogMessage::Type::_Error;
	}
};

class UnkownError : public LogMessage {
public:
	UnkownError(const std::string& m) : LogMessage(m) {}
	Type type() const override {
		return LogMessage::Type::_UnkownError;
	}
};


class Handler {
public:
	explicit Handler(std::unique_ptr<Handler> next) : next_(std::move(next)) {
	}
	virtual ~Handler() = default;
	void receive(const LogMessage& msg) {
		if (handle(msg)) { // Если текущий обработчик принял сообщение, то считаем его обработанным
			return;
		}
		if (!next_) { // Если обработчиков больше нет, то оповещаем о том, что сообщение осталось необработанным
			throw std::runtime_error("Error: Message should be handled! " + msg.message() + "\n");
		}
		next_->receive(msg); // Иначе передаём сообщение следующему обработчику
	}
private:
	virtual bool handle(const LogMessage& msg) = 0; // В наследниках реализуем логику по обработке сообщений
	std::unique_ptr<Handler> next_;
};

class FatalErrorHandler : public Handler {
public:
	using Handler::Handler;
private:
	bool handle(const LogMessage& msg) override {
		if (msg.type() != LogMessage::Type::_FatalError) {
			return false;
		}
		throw("FatalError " + msg.message() + "\n");
		return true;
	}
};

class ErrorHandler : public Handler {
public:
	using Handler::Handler;
private:
	bool handle(const LogMessage& msg) override {
		if (msg.type() != LogMessage::Type::_Error) {
			return false;
		}
		std::ofstream fout;
		fout.open("log.txt", std::ios::app);
		fout << "Error " + msg.message() + "\n";
		fout.close();
		return true;
	}
};

class WarningHandler : public Handler {
public:
	using Handler::Handler;
private:
	bool handle(const LogMessage& msg) override {
		if (msg.type() != LogMessage::Type::_Warning) {
			return false;
		}
		std::cout << "Warning " + msg.message() + "\n";
		return true;
	}
};

//class UnkownErrorHandler : public Handler {
//public:
//	using Handler::Handler;
//private:
//	bool handle(const LogMessage& msg) override {
//		throw("FatalError " + msg.message());
//		return true;
//	}
//};

int main()
{
	//auto a_ = WarningHandler(nullptr);
	auto a = std::make_unique<WarningHandler>(nullptr);
	auto b = std::make_unique<ErrorHandler>(std::move(a));
	auto c = std::make_unique<FatalErrorHandler>(std::move(b));

	try {
		c->receive(Warning("warning01"));
		c->receive(Error("error01"));
		c->receive(UnkownError("?????"));
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what();
	}


	try {
		c->receive(FatalError("fatal01"));
	}
	catch (const std::string& e) {
		std::cout << "catched: " << e;
	}
}