#include "figure_error.h"

figure_error::figure_error(const char* msg) : std::domain_error(msg) {
}
