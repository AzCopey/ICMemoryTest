// Created by Ian Copland on 2016-05-03
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
        constexpr std::size_t k_defaultPoolSize = 8;
    }

    /// A series of tests for ObjectPool
    ///
    TEST_CASE("ObjectPool", "[Allocator]")
    {
        /// Confirms that a unique pointer to a fundamental can be allocated from an ObjectPool.
        ///
        SECTION("UniqueFundamental")
        {
            IC::ObjectPool<int> objectPool(k_defaultPoolSize);

            auto allocated = objectPool.Create();
            *allocated = 1;

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a unique pointer to a fundamental with an initial value can be allocated from an ObjectPool.
        ///
        SECTION("UniqueFundamentalInitialValue")
        {
            IC::ObjectPool<int> objectPool(k_defaultPoolSize);

            auto allocated = objectPool.Create(1);

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a unique pointer to a struct instance can be allocated from an ObjectPool.
        ///
        SECTION("UniqueStruct")
        {
            struct ExampleClass
            {
                int m_x, m_y;
            };

            IC::ObjectPool<ExampleClass> objectPool(k_defaultPoolSize);

            auto allocated = objectPool.Create();
            allocated->m_x = 1;
            allocated->m_y = 2;

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a unique pointer to a struct instance with a constructor can be allocated from an ObjectPool.
        ///
        SECTION("UniqueStructConstructor")
        {
            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::ObjectPool<ExampleClass> objectPool(k_defaultPoolSize);

            auto allocated = objectPool.Create(1, 2);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a unique pointer to a struct instance can be copy constructed from an ObjectPool.
        ///
        SECTION("UniqueStructCopyConstructor")
        {
            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::ObjectPool<ExampleClass> objectPool(k_defaultPoolSize);

            ExampleClass exampleClass(1, 2);
            auto allocated = objectPool.Create(exampleClass);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a shared pointer to a fundamental can be allocated from an ObjectPool.
        ///
        SECTION("SharedFundamental")
        {
            IC::ObjectPool<int> objectPool(k_defaultPoolSize);

            IC::SharedPtr<int> allocated = objectPool.Create();
            *allocated = 1;

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a shared pointer to a fundamental with an initial value can be allocated from an ObjectPool.
        ///
        SECTION("SharedFundamentalInitialValue")
        {
            IC::ObjectPool<int> objectPool(k_defaultPoolSize);

            IC::SharedPtr<int> allocated = objectPool.Create(1);

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a shared pointer to a struct instance can be allocated from an ObjectPool.
        ///
        SECTION("SharedStruct")
        {
            struct ExampleClass
            {
                int m_x, m_y;
            };

            IC::ObjectPool<ExampleClass> objectPool(k_defaultPoolSize);

            IC::SharedPtr<ExampleClass> allocated = objectPool.Create();
            allocated->m_x = 1;
            allocated->m_y = 2;

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a shared pointer to a struct instance with a constructor can be allocated from an ObjectPool.
        ///
        SECTION("SharedStructConstructor")
        {
            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::ObjectPool<ExampleClass> objectPool(k_defaultPoolSize);

            IC::SharedPtr<ExampleClass> allocated = objectPool.Create(1, 2);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a shared pointer to a struct instance can be copy constructed from an ObjectPool.
        ///
        SECTION("SharedStructCopyConstructor")
        {
            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::ObjectPool<ExampleClass> objectPool(k_defaultPoolSize);

            ExampleClass exampleClass(1, 2);
            IC::SharedPtr<ExampleClass> allocated = objectPool.Create(exampleClass);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that multiple objects can be allocated from an ObjectPool.
        ///
        SECTION("MultipleObjects")
        {
            IC::ObjectPool<int> objectPool(k_defaultPoolSize);

            auto valueA = objectPool.Create(1);
            auto valueB = objectPool.Create(2);
            auto valueC = objectPool.Create(3);

            REQUIRE(*valueA == 1);
            REQUIRE(*valueB == 2);
            REQUIRE(*valueC == 3);
        }

        /// Confirms that deallocating an object allocated from an ObjectPool does not affect other allocations.
        ///
        SECTION("Deallocation")
        {
            IC::ObjectPool<int> objectPool(k_defaultPoolSize);

            auto valueA = objectPool.Create(1);
            auto valueB = objectPool.Create(2);
            valueB.reset();
            auto valueC = objectPool.Create(3);
            valueB = objectPool.Create(4);

            REQUIRE(*valueA == 1);
            REQUIRE(*valueB == 4);
            REQUIRE(*valueC == 3);
        }

        /// Confirms that an ObjectPool can be backed by a BuddyAllocator.
        ///
        SECTION("BuddyAllocatorBacked")
        {
            constexpr std::size_t k_buddyAllocatorBufferSize = 2048;

            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::BuddyAllocator buddyAllocator(k_buddyAllocatorBufferSize);
            IC::ObjectPool<ExampleClass> objectPool(buddyAllocator, k_defaultPoolSize);

            auto allocated = objectPool.Create(1, 2);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that an ObjectPool can be backed by a LinearAllocator.
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
            IC::ObjectPool<ExampleClass> objectPool(linearAllocator, k_defaultPoolSize);

            auto allocated = objectPool.Create(1, 2);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }
    }
}