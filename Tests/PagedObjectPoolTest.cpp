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
	/// A series of tests for the PagedObjectPool
	///
	TEST_CASE("PagedObjectPool", "[Allocator]")
	{
		/// Confirms that a unique pointer to a fundamental can be allocated from a PagedObjectPool.
		///
		SECTION("UniqueFundamental")
		{
			IC::PagedObjectPool<int> pagedObjectPool;

			auto allocated = pagedObjectPool.Create();
			*allocated = 1;

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a unique pointer to a fundamental with an initial value can be allocated from a PagedObjectPool.
		///
		SECTION("UniqueFundamentalInitialValue")
		{
			IC::PagedObjectPool<int> pagedObjectPool;

			auto allocated = pagedObjectPool.Create(1);

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a unique pointer to a struct instance can be allocated from a PagedObjectPool.
		///
		SECTION("UniqueStruct")
		{
			struct ExampleClass
			{
				int m_x, m_y;
			};

			IC::PagedObjectPool<ExampleClass> pagedObjectPool;

			auto allocated = pagedObjectPool.Create();
			allocated->m_x = 1;
			allocated->m_y = 2;

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a unique pointer to a struct instance with a constructor can be allocated from a PagedObjectPool.
		///
		SECTION("UniqueStructConstructor")
		{
			struct ExampleClass
			{
				ExampleClass(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::PagedObjectPool<ExampleClass> pagedObjectPool;

			auto allocated = pagedObjectPool.Create(1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a unique pointer to a struct instance can be copy constructed from a PagedObjectPool.
		///
		SECTION("UniqueStructCopyConstructor")
		{
			struct ExampleClass
			{
				ExampleClass(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::PagedObjectPool<ExampleClass> pagedObjectPool;

			ExampleClass exampleClass(1, 2);
			auto allocated = pagedObjectPool.Create(exampleClass);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a shared pointer to a fundamental can be allocated from a PagedObjectPool.
		///
		SECTION("SharedFundamental")
		{
			IC::PagedObjectPool<int> pagedObjectPool;

			IC::SharedPtr<int> allocated = pagedObjectPool.Create();
			*allocated = 1;

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a shared pointer to a fundamental with an initial value can be allocated from a PagedObjectPool.
		///
		SECTION("SharedFundamentalInitialValue")
		{
			IC::PagedObjectPool<int> pagedObjectPool;

			IC::SharedPtr<int> allocated = pagedObjectPool.Create(1);

			REQUIRE(*allocated == 1);
		}

		/// Confirms that a shared pointer to a struct instance can be allocated from a PagedObjectPool.
		///
		SECTION("SharedStruct")
		{
			struct ExampleClass
			{
				int m_x, m_y;
			};

			IC::PagedObjectPool<ExampleClass> pagedObjectPool;

			IC::SharedPtr<ExampleClass> allocated = pagedObjectPool.Create();
			allocated->m_x = 1;
			allocated->m_y = 2;

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a shared pointer to a struct instance with a constructor can be allocated from a PagedObjectPool.
		///
		SECTION("SharedStructConstructor")
		{
			struct ExampleClass
			{
				ExampleClass(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::PagedObjectPool<ExampleClass> pagedObjectPool;

			IC::SharedPtr<ExampleClass> allocated = pagedObjectPool.Create(1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a shared pointer to a struct instance can be copy constructed from a PagedObjectPool.
		///
		SECTION("SharedStructCopyConstructor")
		{
			struct ExampleClass
			{
				ExampleClass(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::PagedObjectPool<ExampleClass> pagedObjectPool;

			ExampleClass exampleClass(1, 2);
			IC::SharedPtr<ExampleClass> allocated = pagedObjectPool.Create(exampleClass);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that multiple objects can be allocated from a PagedObjectPool.
		///
		SECTION("MultipleObjects")
		{
			IC::PagedObjectPool<int> pagedObjectPool;

			auto valueA = pagedObjectPool.Create(1);
			auto valueB = pagedObjectPool.Create(2);
			auto valueC = pagedObjectPool.Create(3);

			REQUIRE(*valueA == 1);
			REQUIRE(*valueB == 2);
			REQUIRE(*valueC == 3);
		}

		/// Confirms that deallocating an object allocated from a PagedObjectPool does not affect other allocations.
		///
		SECTION("Deallocation")
		{
			IC::PagedObjectPool<int> pagedObjectPool;

			auto valueA = pagedObjectPool.Create(1);
			auto valueB = pagedObjectPool.Create(2);
			valueB.reset();
			auto valueC = pagedObjectPool.Create(3);
			valueB = pagedObjectPool.Create(4);

			REQUIRE(*valueA == 1);
			REQUIRE(*valueB == 4);
			REQUIRE(*valueC == 3);
		}

		/// Confirms that paging works correctly in the PagedObjectPool.
		///
		SECTION("Paging")
		{
			constexpr std::size_t k_pageSize = 2;

			IC::PagedObjectPool<int> pagedObjectPool(k_pageSize);

			auto valueA = pagedObjectPool.Create(1);
			auto valueB = pagedObjectPool.Create(2);
			auto valueC = pagedObjectPool.Create(3);
			auto valueD = pagedObjectPool.Create(4);
			auto valueE = pagedObjectPool.Create(5);

			REQUIRE(*valueA == 1);
			REQUIRE(*valueB == 2);
			REQUIRE(*valueC == 3);
			REQUIRE(*valueD == 4);
			REQUIRE(*valueE == 5);
		}

		/// Confirms that a PagedObjectPool can be backed by a BuddyAllocator.
		///
		SECTION("BuddyAllocatorBacked")
		{
			constexpr std::size_t k_buddyAllocatorBufferSize = 2048;
			constexpr std::size_t k_pageSize = 8;

			struct ExampleClass
			{
				ExampleClass(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::BuddyAllocator buddyAllocator(k_buddyAllocatorBufferSize);
			IC::PagedObjectPool<ExampleClass> pagedObjectPool(buddyAllocator, k_pageSize);

			auto allocated = pagedObjectPool.Create(1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}

		/// Confirms that a PagedObjectPool can be backed by a LinearAllocator.
		///
		SECTION("LinearAllocatorBacked")
		{
			constexpr std::size_t k_linearAllocatorBufferSize = 4 * 1024;

			struct ExampleClass
			{
				ExampleClass(int x, int y) : m_x(x), m_y(y) {}
				int m_x, m_y;
			};

			IC::LinearAllocator linearAllocator(k_linearAllocatorBufferSize);
			IC::PagedObjectPool<ExampleClass> pagedObjectPool(linearAllocator);

			auto allocated = pagedObjectPool.Create(1, 2);

			REQUIRE(allocated->m_x == 1);
			REQUIRE(allocated->m_y == 2);
		}
	}
}