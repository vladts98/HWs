#include "Vehicles.h"

Vehicle::Vehicle()
{
	this->name = "Транспорт";
	this->speed = 0;
	this->status = false; //в игре или нет
	this->type = "";
	this->time = 0;
}

float Vehicle::get_time()
{
	return this->time;
}

std::string Vehicle::get_name()
{
	return this->name;
}

bool Vehicle::get_status()
{
	return this->status;
}

void Vehicle::change_status(std::string race_type)
{
	if (check_status(race_type)) {
		this->status = true; // в игре
	}
	else {
		this->status = false;
	}
}

bool Vehicle::check_status(std::string race_type) {
	return (race_type.find(this->type) != std::string::npos);
}

Ground_vehicle::Ground_vehicle()
{
	this->type = "Ground";					// 1 - наземное
}

Camal::Camal(const float lenth, std::string race_type)
{
	this->name = "Верблюд";
	this->speed = 10;
	this->time = this->calc_time(lenth, race_type);
}

float Camal::calc_time(const float lenth, std::string race_type) {
	float time = 0;
	if (check_status(race_type)) {
		int time_between_rest = 30;
		const int i_rest_time = 2;
		float rest_time[i_rest_time] = { 5,8 };

		int i_rest = ((static_cast<int>(lenth) - 1) / this->speed) / time_between_rest;
		float full_rest = 0;
		for (int i = 0; i < i_rest; ++i) {
			int count_rest = i_rest_time > i ? i : (i_rest_time - 1);
			full_rest += rest_time[count_rest];
		}
		time = lenth / this->speed + full_rest;
	}
	return time;
}

Camal_fast::Camal_fast(const float lenth, std::string race_type)
{
	this->name = "Верблюд быстроход";
	this->speed = 40;
	this->time = this->calc_time(lenth, race_type);
}

float Camal_fast::calc_time(const float lenth, std::string race_type) {
	float time = 0;
	if (check_status(race_type)) {
		float time_between_rest = 10;
		const int i_rest_time = 3;
		float rest_time[i_rest_time] = { 5,6.5,8 };

		int i_rest = static_cast<int>(((lenth - 1) / this->speed) / time_between_rest);
		float full_rest = 0;
		for (int i = 0; i < i_rest; ++i) {
			int count_rest = i_rest_time > i ? i : (i_rest_time - 1);
			full_rest += rest_time[count_rest];
		}
		time = lenth / this->speed + full_rest;
	}
	return time;
}

Kent::Kent(const float lenth, std::string race_type)
{
	this->name = "Кентавр";
	this->speed = 15;
	this->time = calc_time(lenth, race_type);
}

float Kent::calc_time(const float lenth, std::string race_type) {
	float time = 0;
	if (check_status(race_type)) {
		float time_between_rest = 8;
		const int i_rest_time = 1;
		float rest_time[i_rest_time] = { 2 };

		int i_rest = static_cast<int>(((lenth - 1) / this->speed) / time_between_rest);
		float full_rest = 0;
		for (int i = 0; i < i_rest; ++i) {
			int count_rest = i_rest_time > i ? i : (i_rest_time - 1);
			full_rest += rest_time[count_rest];
		}
		time = lenth / this->speed + full_rest;
	}
	return time;
}

Boots_fast::Boots_fast(const float lenth, std::string race_type)
{
	this->name = "Ботинки быстроходы";
	this->speed = 6;
	this->time = calc_time(lenth, race_type);
}

float Boots_fast::calc_time(const float lenth, std::string race_type) {
	float time = 0;
	if (check_status(race_type)) {
		float time_between_rest = 60;
		const int i_rest_time = 2;
		float rest_time[i_rest_time] = { 10, 5 };

		int i_rest = static_cast<int>(((lenth - 1) / this->speed) / time_between_rest);
		float full_rest = 0;
		for (int i = 0; i < i_rest; ++i) {
			int count_rest = i_rest_time > i ? i : (i_rest_time - 1);
			full_rest += rest_time[count_rest];
		}
		time = lenth / this->speed + full_rest;
	}
	return time;
}

Air_vehicle::Air_vehicle() {
	this->type = "Air";  // 2 - воздушное
}

Magic_carpet::Magic_carpet(const float lenth, std::string race_type) {
	this->name = "Ковёр-самолёт";
	this->speed = 10;
	this->time = calc_time(lenth, race_type);
}

float Magic_carpet::calc_time(const float lenth, std::string race_type) {
	if (!check_status(race_type)) {
		return 0;
	}
	if (lenth < 1000) {
		return (lenth / this->speed);
	}
	else if (lenth < 5000) {
		return  (lenth * (1 - (3.f / 100)) / this->speed);
	}
	else if (lenth < 10000) {
		return (lenth * (1 - 10.f / 100) / this->speed);
	}
	else {
		return (lenth * (1 - 5.f / 100) / this->speed);
	}
}

Eagle::Eagle(const float lenth, std::string race_type) {
	this->name = "Орёл";
	this->speed = 8;
	this->time = calc_time(lenth, race_type);
}

float Eagle::calc_time(const float lenth, std::string race_type) {
	if (check_status(race_type)) {
		return (lenth * (1 - 6.f / 100) / this->speed);
	}
	return 0;
}

Broom::Broom(const float lenth, std::string race_type) {
	this->name = "Метла";
	this->speed = 20;
	this->time = calc_time(lenth, race_type);
}

float Broom::calc_time(const float lenth, std::string race_type) {
	if (check_status(race_type)) {
		int k = static_cast<int>(lenth) / 1000;
		return (lenth * (1 - static_cast<float>(k) / 100) / this->speed);
	}
	return 0;
}