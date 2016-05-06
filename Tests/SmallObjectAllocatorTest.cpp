// Created by Ian Copland on 2016-05-04
//
// The MIT License(MIT)
// 
// Copyright(c) 2016 Ian Copland
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "../ICMemory/ICMemory.h"

#include <catch.hpp>

namespace ICMemoryTest
{
	namespace
	{
		constexpr std::size_t k_defaultAllocatorSize = 4096;
	}

	/// A series of tests for the SmallObjectAllocator
	///
	TEST_CASE("SmallObjectAllocator", "[Allocator]")
	{
		/// Confirms that a unique pointer to a fundamental can be allocated from a SmallObjectAllocator.
		///
		SECTION("UniqueFundamental")
		{
			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeUnique<int>(smallObjectAllocator);
			*allocated = 1;

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a unique pointer to a fundamental with an initial value can be allocated from a SmallObjectAllocator.
		///
		SECTION("UniqueFundamentalInitialValue")
		{
			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeUnique<int>(smallObjectAllocator, 1);

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a unique pointer to a struct instance can be allocated from a SmallObjectAllocator.
		///
		SECTION("UniqueStruct")
		{
			struct ExampleStruct
			{
				int m_x, m_y;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeUnique<ExampleStruct>(smallObjectAllocator);
			allocated->m_x = 1;
			allocated->m_y = 2;

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a unique pointer to a struct instance with a constructor can be allocated from a SmallObjectAllocator.
		///
		SECTION("UniqueStructConstructor")
		{
			struct ExampleStruct
			{
				ExampleStruct(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeUnique<ExampleStruct>(smallObjectAllocator, 1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a unique pointer to a struct instance can be copy constructed from a SmallObjectAllocator.
		///
		SECTION("UniqueStructCopyConstructor")
		{
			struct ExampleStruct
			{
				ExampleStruct(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			ExampleStruct exampleStruct(1, 2);
			auto allocated = IC::MakeUnique<ExampleStruct>(smallObjectAllocator, exampleStruct);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a shared pointer to a fundamental can be allocated from a SmallObjectAllocator.
		///
		SECTION("SharedFundamental")
		{
			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeShared<int>(smallObjectAllocator);
			*allocated = 1;

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a shared pointer to a fundamental with an initial value can be allocated from a SmallObjectAllocator.
		///
		SECTION("SharedFundamentalInitialValue")
		{
			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeShared<int>(smallObjectAllocator, 1);

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a shared pointer to a struct instance can be allocated from a SmallObjectAllocator.
		///
		SECTION("SharedStruct")
		{
			struct ExampleStruct
			{
				int m_x, m_y;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeShared<ExampleStruct>(smallObjectAllocator);
			allocated->m_x = 1;
			allocated->m_y = 2;

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a shared pointer to a struct instance with a constructor can be allocated from a SmallObjectAllocator.
		///
		SECTION("SharedStructConstructor")
		{
			struct ExampleStruct
			{
				ExampleStruct(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto allocated = IC::MakeShared<ExampleStruct>(smallObjectAllocator, 1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a shared pointer to a struct instance can be copy constructed from a SmallObjectAllocator.
		///
		SECTION("SharedStructCopyConstructor")
		{
			struct ExampleStruct
			{
				ExampleStruct(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			ExampleStruct exampleStruct(1, 2);
			auto allocated = IC::MakeShared<ExampleStruct>(smallObjectAllocator, exampleStruct);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that multiple objects can be allocated from a SmallObjectAllocator.
		///
		SECTION("MultipleObjects")
		{
			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto valueA = IC::MakeUnique<int>(smallObjectAllocator, 1);
			auto valueB = IC::MakeUnique<int>(smallObjectAllocator, 2);
			auto valueC = IC::MakeUnique<int>(smallObjectAllocator, 3);

			REQUIRE(*valueA == 1);
			REQUIRE(*valueB == 2);
			REQUIRE(*valueC == 3);
		}

		/// Confirms that deallocating an object allocated from a SmallObjectAllocator does not affect other allocations.
		///
		SECTION("Deallocation")
		{
			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto valueA = IC::MakeUnique<int>(smallObjectAllocator, 1);
			auto valueB = IC::MakeUnique<int>(smallObjectAllocator, 2);
			valueB.reset();
			auto valueC = IC::MakeUnique<int>(smallObjectAllocator, 3);
			valueB = IC::MakeUnique<int>(smallObjectAllocator, 4);

			REQUIRE(*valueA == 1);
			REQUIRE(*valueB == 4);
			REQUIRE(*valueC == 3);
		}

		/// Confirms that up to 64-byte objects can be allocated from a SmallObjectAllocator.
		///
		SECTION("LargeObjects")
		{
			struct ExampleStruct final
			{
				ExampleStruct(double a, double b, double c, double d, double e, double f, double g, double h) : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f), m_g(g), m_h(h) {}
				double m_a, m_b, m_c, m_d, m_e, m_f, m_g, m_h;
			};

			IC::SmallObjectAllocator smallObjectAllocator(k_defaultAllocatorSize);

			auto value = IC::MakeUnique<ExampleStruct>(smallObjectAllocator, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

			REQUIRE(value->m_a == 0.0);
			REQUIRE(value->m_b == 1.0);
			REQUIRE(value->m_c == 2.0);
			REQUIRE(value->m_d == 3.0);
			REQUIRE(value->m_e == 4.0);
			REQUIRE(value->m_f == 5.0);
			REQUIRE(value->m_g == 6.0);
			REQUIRE(value->m_h == 7.0);
		}

		///// Confirms that paging works correctly in the SmallObjectAllocator.
		/////
		//SECTION("Paging")
		//{
		//	constexpr std::size_t k_pageSize = 128;

		//	struct ExampleStruct final
		//	{
		//		ExampleStruct(double a, double b, double c, double d, double e, double f, double g, double h) : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f), m_g(g), m_h(h) {}
		//		double m_a, m_b, m_c, m_d, m_e, m_f, m_g, m_h;
		//	};

		//	IC::SmallObjectAllocator smallObjectAllocator(k_pageSize);

		//	auto value1 = smallObjectAllocator.Create<ExampleStruct>(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
		//	auto value2 = smallObjectAllocator.Create<ExampleStruct>(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
		//	auto value3 = smallObjectAllocator.Create<ExampleStruct>(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);

		//	REQUIRE((value1->m_a == 0.0 && value2->m_a == 0.0 && value3->m_a == 0.0));
		//	REQUIRE((value1->m_b == 1.0 && value2->m_b == 1.0 && value3->m_b == 1.0));
		//	REQUIRE((value1->m_c == 2.0 && value2->m_c == 2.0 && value3->m_c == 2.0));
		//	REQUIRE((value1->m_d == 3.0 && value2->m_d == 3.0 && value3->m_d == 3.0));
		//	REQUIRE((value1->m_e == 4.0 && value2->m_e == 4.0 && value3->m_e == 4.0));
		//	REQUIRE((value1->m_f == 5.0 && value2->m_f == 5.0 && value3->m_f == 5.0));
		//	REQUIRE((value1->m_g == 6.0 && value2->m_g == 6.0 && value3->m_g == 6.0));
		//	REQUIRE((value1->m_h == 7.0 && value2->m_h == 7.0 && value3->m_h == 7.0));
		//}

		/// Confirms that a SmallObjectAllocator can be backed by a BuddyAllocator.
		///
		SECTION("BuddyAllocatorBacked")
		{
			constexpr std::size_t k_buddyAllocatorBufferSize = 4096;
			constexpr std::size_t k_buddyAllocatorMinBlockSize = 32;
			constexpr std::size_t k_pageSize = 128;

			struct ExampleStruct
			{
				ExampleStruct(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::BuddyAllocator buddyAllocator(k_buddyAllocatorBufferSize, k_buddyAllocatorMinBlockSize);
			IC::SmallObjectAllocator smallObjectAllocator(buddyAllocator, k_pageSize);

			auto allocated = IC::MakeUnique<ExampleStruct>(smallObjectAllocator, 1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}
	}
}