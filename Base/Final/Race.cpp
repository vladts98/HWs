#include "Race.h"

Race::Race() {
	this->type = "";
	this->type_number = 0;
	
	this->lenth = 0;
	this->reg_v = 0;
}

Race::~Race() {
	delete[] this->Vehicles;
}

int Race::Create_race(const int type, const float lenth) {
	if (!set_type(type)) {
		return 1;
	}
	if (!set_lenth(lenth)) {
		return 2;
	}

	this->Vehicles = new Vehicle[this->all_v];
	Vehicles[0] = Boots_fast(this->lenth, this->type);
	Vehicles[1] = Broom(this->lenth, this->type);
	Vehicles[2] = Camal(this->lenth, this->type);
	Vehicles[3] = Kent(this->lenth, this->type);
	Vehicles[4] = Eagle(this->lenth, this->type);
	Vehicles[5] = Camal_fast(this->lenth, this->type);
	Vehicles[6] = Magic_carpet(this->lenth, this->type);
	return 0;
}

int Race::get_all_v() {
	return this->all_v;
}

int Race::get_reg_v() {
	return this->reg_v;
}

float Race::get_time(const int i) {
	return this->Vehicles[i].get_time();
}

void Race::print_all_info() {
	std::cout << this->type_name[this->type_number] << " ";
	std::cout << ". –ассто€ние: " << this->lenth << std::endl;
	if (this->reg_v > 0) {
		std::cout << "«арегистрированные транспортные средства: ";
		for (int i = 0, reg_v = 0; reg_v < this->reg_v; ++i) {
			if (this->Vehicles[i].get_status() == true) {
				++reg_v;
				std::cout << this->Vehicles[i].get_name();
				if (reg_v < this->reg_v) {
					std::cout << ", ";
				}
				else {
					std::cout << std::endl;
				}
			}
		}
	}
	for (int i = 0; i < this->get_all_v(); ++i) {
		std::cout << i + 1 << " " << this->Vehicles[i].get_name() << std::endl;
	}
}

std::string Race::get_v_name(const int i) {
	return this->Vehicles[i].get_name();
}

bool Race::get_v_status(const int i) {
	return (Vehicles[i].get_status());
}

int Race::reg(int n) {
	if (n == 0) {
		return 4;					// конец регистрации
	}
	else if (this->all_v < n) {
		return 1;					// “— не существует
	}
	else {
		n = n - 1;
		if (this->Vehicles[n].get_status()) {
			return 2;				// уже зарегестрировали
		}
		else {
			this->Vehicles[n].change_status(this->type);
			if (this->Vehicles[n].get_status()) {
				this->reg_v++;		// зарегестрировали
				return 0;
			}
			else {
				return 3;			// не может зарегестрироватьс€
			}
		}
	}
}

void Race::start() {
	for (int i = 0; i < this->all_v - 1; ++i) {
		if (this->Vehicles[i].get_time() < this->Vehicles[i + 1].get_time()) {
			std::swap(this->Vehicles[i], this->Vehicles[i + 1]);
			i = -1;
		}
	}
}

bool Race::set_type(const int type) {
	switch (type) {
	case 1:
		this->type = "Ground";
		break;
	case 2:
		this->type = "Air";
		break;
	case 3:
		this->type = "Ground & Air";
		break;
	default:
		return false;
	}
	this->type_number = type - 1;
	return true;
}

bool Race::set_lenth(const float lenth) {
	if (lenth <= 0)
		return false;
	this->lenth = lenth;
	return true;
}