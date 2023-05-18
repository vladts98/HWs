#pragma once
#include <iostream>

#ifdef Vehicles_EXPORTS
#define VEHICLESLIBRARY_API __declspec(dllexport)
#else
#define VEHICLESLIBRARY_API __declspec(dllimport)
#endif

class Vehicle {
public:
	VEHICLESLIBRARY_API Vehicle();
	VEHICLESLIBRARY_API float get_time();
	VEHICLESLIBRARY_API std::string get_name();
	VEHICLESLIBRARY_API bool get_status();
	VEHICLESLIBRARY_API void change_status(std::string race_type);
protected:
	bool check_status(std::string race_type);
	float time;
	std::string name;
	int speed;
	bool status;	//в игре или нет
	std::string type;		//тип ТС назменый воздушный и тд
};

class Ground_vehicle : public Vehicle {
public:
	VEHICLESLIBRARY_API Ground_vehicle();
};

class Camal : public Ground_vehicle {
public:
	VEHICLESLIBRARY_API Camal(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;
};

class Camal_fast : public Ground_vehicle {
public:
	VEHICLESLIBRARY_API Camal_fast(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;

};

class Kent : public Ground_vehicle {
public:
	VEHICLESLIBRARY_API Kent(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;
};

class Boots_fast : public Ground_vehicle {
public:
	VEHICLESLIBRARY_API Boots_fast(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;
};

class Air_vehicle : public Vehicle {
public:
	VEHICLESLIBRARY_API Air_vehicle();
};

class Magic_carpet : public Air_vehicle {
public:
	VEHICLESLIBRARY_API Magic_carpet(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;
};

class Eagle : public Air_vehicle {
public:
	VEHICLESLIBRARY_API Eagle(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;
};

class Broom : public Air_vehicle {
public:
	VEHICLESLIBRARY_API Broom(const float lenth, std::string race_type);
private:
	float calc_time(const float lenth, std::string race_type) ;
};
