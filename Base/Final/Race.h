#pragma once
#include "Vehicles.h"

#ifdef Race_EXPORTS
#define RACELIBRARY_API __declspec(dllexport)
#else
#define RACELIBRARY_API __declspec(dllimport)
#endif

class Race {
public:
	RACELIBRARY_API Race();
	RACELIBRARY_API ~Race();
	const std::string type_name[3] = { "Гонка для наземного транспорта", "Гонка для воздушного транспорта", "Гонка для наземного и воздушного траспорта" };
	const int max_type = sizeof(type_name) / sizeof(type_name[0]);

	RACELIBRARY_API int Create_race(const int type, const float lenth);
	RACELIBRARY_API int get_all_v();
	RACELIBRARY_API int get_reg_v();
	RACELIBRARY_API std::string get_v_name(const int i);
	RACELIBRARY_API bool get_v_status(const int i);
	RACELIBRARY_API float get_time(const int i);

	RACELIBRARY_API void print_all_info();

	RACELIBRARY_API int reg(int n);
	RACELIBRARY_API void start();
private:
	bool set_type(const int type);
	bool set_lenth(const float lenth);

	Vehicle* Vehicles = nullptr;
	const int all_v = 7;	//все доступные машины

	std::string type;
	int type_number;
	float lenth;
	int reg_v;				// зарегестрированные машины
};