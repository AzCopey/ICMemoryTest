// Created by Ian Copland on 2016-01-31
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
        constexpr std::size_t k_defaultBufferSize = 4 * 1024;
    }

    /// A series of tests for the LinearAllocator
    ///
    TEST_CASE("LinearAllocator", "[Allocator]")
    {
        /// Confirms that a unique pointer to a fundamental can be allocated from a LinearAllocator.
        ///
        SECTION("UniqueFundamental")
        {
            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeUnique<int>(linearAllocator);
            *allocated = 1;

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a unique pointer to a fundamental with an initial value can be allocated from a LinearAllocator.
        ///
        SECTION("UniqueFundamentalInitialValue")
        {
            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeUnique<int>(linearAllocator, 1);

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a unique pointer to a struct instance can be allocated from a LinearAllocator.
        ///
        SECTION("UniqueStruct")
        {
            struct ExampleClass
            {
                int m_x, m_y;
            };

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeUnique<ExampleClass>(linearAllocator);
            allocated->m_x = 1;
            allocated->m_y = 2;

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a unique pointer to a struct instance with a constructor can be allocated from a LinearAllocator.
        ///
        SECTION("UniqueStructConstructor")
        {
            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeUnique<ExampleClass>(linearAllocator, 1, 2);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a unique pointer to a struct instance can be copy constructed from a LinearAllocator.
        ///
        SECTION("UniqueStructCopyConstructor")
        {
            struct ExampleClass
            {
                int m_x, m_y;
            };

            ExampleClass exampleClass;
            exampleClass.m_x = 1;
            exampleClass.m_y = 2;

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeUnique<ExampleClass>(linearAllocator, exampleClass);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a unique pointer to an array can be allocated from a LinearAllocator.
        ///
        SECTION("UniqueArray")
        {
            const int k_numValues = 10;

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeUniqueArray<int>(linearAllocator, 10);

            for (auto i = 0; i < k_numValues; ++i)
            {
                allocated[i] = i;
            }

            for (auto i = 0; i < k_numValues; ++i)
            {
                REQUIRE(allocated[i] == i);
            }
        }

        /// Confirms that a shared pointer to a fundamental can be allocated from a LinearAllocator.
        ///
        SECTION("SharedFundamental")
        {
            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeShared<int>(linearAllocator);
            *allocated = 1;

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a shared pointer to a fundamental with an initial value can be allocated from a LinearAllocator.
        ///
        SECTION("SharedFundamentalInitialValue")
        {
            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeShared<int>(linearAllocator, 1);

            REQUIRE(*allocated == 1);
        }

        /// Confirms that a shared pointer to a struct instance can be allocated from a LinearAllocator.
        ///
        SECTION("SharedStruct")
        {
            struct ExampleClass
            {
                int m_x, m_y;
            };

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeShared<ExampleClass>(linearAllocator);
            allocated->m_x = 1;
            allocated->m_y = 2;

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a shared pointer to a struct instance with a constructor can be allocated from a LinearAllocator.
        ///
        SECTION("SharedStructConstructor")
        {
            struct ExampleClass
            {
                ExampleClass(int x, int y) : m_x(x), m_y(y) {}
                int m_x, m_y;
            };

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeShared<ExampleClass>(linearAllocator, 1, 2);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that a shared pointer to a struct instance can be copy constructed from a LinearAllocator.
        ///
        SECTION("SharedStructCopyConstructor")
        {
            struct ExampleClass
            {
                int m_x, m_y;
            };

            ExampleClass exampleClass;
            exampleClass.m_x = 1;
            exampleClass.m_y = 2;

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto allocated = IC::MakeShared<ExampleClass>(linearAllocator, exampleClass);

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }

        /// Confirms that multiple objects can be allocated from a LinearAllocator.
        ///
        SECTION("MultipleObjects")
        {
            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto valueA = IC::MakeUnique<int>(linearAllocator, 1);
            auto valueB = IC::MakeUnique<int>(linearAllocator, 2);
            auto valueC = IC::MakeUnique<int>(linearAllocator, 3);

            REQUIRE(*valueA == 1);
            REQUIRE(*valueB == 2);
            REQUIRE(*valueC == 3);
        }

        /// Confirms that deallocating an object allocated from a LinearAllocator does not affect other allocations.
        ///
        SECTION("Deallocation")
        {
            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto valueA = IC::MakeUnique<int>(linearAllocator, 1);
            auto valueB = IC::MakeUnique<int>(linearAllocator, 2);
            valueB.reset();
            auto valueC = IC::MakeUnique<int>(linearAllocator, 3);
            valueB = IC::MakeUnique<int>(linearAllocator, 4);

            REQUIRE(*valueA == 1);
            REQUIRE(*valueB == 4);
            REQUIRE(*valueC == 3);
        }

        /// Confirms that objects of varying size can be allocated from a LinearAllocator.
        ///
        SECTION("VaryingSizedObjects")
        {
            const char* k_exampleBuffer = "123456789\0";

            struct LargeExampleClass
            {
                char buffer[10];
            };

            struct MediumExampleClass
            {
                std::int64_t m_x;
                std::int64_t m_y;
                std::int64_t m_z;
            };

            IC::LinearAllocator linearAllocator(k_defaultBufferSize);

            auto valueA = IC::MakeUnique<int>(linearAllocator, 1);

            auto valueB = IC::MakeUnique<LargeExampleClass>(linearAllocator);
            memcpy(valueB->buffer, k_exampleBuffer, 10);

            valueA = IC::MakeUnique<int>(linearAllocator, 2);

            auto valueC = IC::MakeUnique<MediumExampleClass>(linearAllocator);
            valueC->m_x = 5;
            valueC->m_y = 10;
            valueC->m_z = 15;

            valueA = IC::MakeUnique<int>(linearAllocator, 3);

            REQUIRE(*valueA == 3);
            REQUIRE(strcmp(k_exampleBuffer, valueB->buffer) == 0);
            REQUIRE(valueC->m_x == 5);
            REQUIRE(valueC->m_y == 10);
            REQUIRE(valueC->m_z == 15);
        }

        /// Confirms that resetting a Linear Allocator can be backed by a Buddy Allocator.
        ///
        SECTION("BuddyAllocatorBacked")
        {
            constexpr std::size_t k_buddyAllocatorBufferSize = 2048;
            constexpr std::size_t k_buddyAllocatorMinBlockSize = 32;
            constexpr std::size_t k_linearAllocatorBufferSize = 32;

            struct ExampleClass
            {
                int m_x, m_y;
            };

            IC::BuddyAllocator buddyAllocator(k_buddyAllocatorBufferSize, k_buddyAllocatorMinBlockSize);
            IC::LinearAllocator linearAllocator(buddyAllocator, k_linearAllocatorBufferSize);

            auto allocated = IC::MakeShared<ExampleClass>(linearAllocator);
            allocated->m_x = 1;
            allocated->m_y = 2;

            REQUIRE(allocated->m_x == 1);
            REQUIRE(allocated->m_y == 2);
        }
    }
}