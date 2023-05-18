#include "Test.h"

TEST_CASE("Test list", "Base") {
	auto L = List(); // создаем 
	
	SECTION("Empty") {
		CHECK(L.Empty() == true);
		L.PushFront(2);
		CHECK(L.Empty() == false);
	}
	SECTION("Size") {
		CHECK(L.Size() == 0);
		L.PushBack(2);
		CHECK(L.Size() == 1);
		L.PushBack(2);
		CHECK(L.Size() == 2);
	}
	SECTION("Clear") {
		L.PushBack(2);
		CHECK(L.Size() != 0);
		CHECK(L.Empty() == false);
		L.Clear();
		CHECK(L.Size() == 0);
		CHECK(L.Empty() == true);
	}
}

TEST_CASE("Test list 2", "Add and get") {
	auto L = List(); // создаем 

	SECTION("Back push and pop") {
		L.PushBack(1);
		L.PushBack(3);
		CHECK(L.Size() == 2);
		CHECK(L.PopBack() == 3);
	}
	SECTION("Front push and pop") {
		L.PushFront(1);
		L.PushFront(3);
		CHECK(L.Size() == 2);
		CHECK(L.PopFront() == 3);
	}
	SECTION("Empty PopBack") {
		CHECK_THROWS_AS(L.PopBack(), std::runtime_error);
	}
	SECTION("Empty PopFront") {
		CHECK_THROWS_AS(L.PopFront(), std::runtime_error);
	}
}