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

/// A series of tests for the LinearAllocator
///
TEST_CASE("LinearAllocator", "[Allocator]")
{
    /// Confirms that a unique pointer to a fundamental can be allocated from a LinearAllocator.
    ///
    SECTION("UniqueFundamental", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<int>(LinearAllocator);
        *allocated = 1;

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a unique pointer to a fundamental with an initial value can be allocated from a LinearAllocator.
    ///
    SECTION("UniqueFundamentalInitialValue", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<int>(LinearAllocator, 1);

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a unique pointer to a struct instance can be allocated from a LinearAllocator.
    ///
    SECTION("UniqueStruct", "[LinearAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<ExampleClass>(LinearAllocator);
        allocated->m_x = 1;
        allocated->m_y = 2;

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a unique pointer to a struct instance with a constructor can be allocated from a LinearAllocator.
    ///
    SECTION("UniqueStructConstructor", "[LinearAllocator]")
    {
        struct ExampleClass
        {
            ExampleClass(int x, int y) : m_x(x), m_y(y) {}
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<ExampleClass>(LinearAllocator, 1, 2);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a unique pointer to a struct instance can be copy constructed from a LinearAllocator.
    ///
    SECTION("UniqueStructCopyConstructor", "[LinearAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        ExampleClass exampleClass;
        exampleClass.m_x = 1;
        exampleClass.m_y = 2;

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<ExampleClass>(LinearAllocator, exampleClass);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a unique pointer to an array can be allocated from a LinearAllocator.
    ///
    SECTION("UniqueArray", "[LinearAllocator]")
    {
        const int k_numValues = 10;

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUniqueArray<int>(LinearAllocator, 10);

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
    SECTION("SharedFundamental", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<int>(LinearAllocator);
        *allocated = 1;

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a shared pointer to a fundamental with an initial value can be allocated from a LinearAllocator.
    ///
    SECTION("SharedFundamentalInitialValue", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<int>(LinearAllocator, 1);

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a shared pointer to a struct instance can be allocated from a LinearAllocator.
    ///
    SECTION("SharedStruct", "[LinearAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<ExampleClass>(LinearAllocator);
        allocated->m_x = 1;
        allocated->m_y = 2;

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a shared pointer to a struct instance with a constructor can be allocated from a LinearAllocator.
    ///
    SECTION("SharedStructConstructor", "[LinearAllocator]")
    {
        struct ExampleClass
        {
            ExampleClass(int x, int y) : m_x(x), m_y(y) {}
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<ExampleClass>(LinearAllocator, 1, 2);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a shared pointer to a struct instance can be copy constructed from a LinearAllocator.
    ///
    SECTION("SharedStructCopyConstructor", "[LinearAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        ExampleClass exampleClass;
        exampleClass.m_x = 1;
        exampleClass.m_y = 2;

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<ExampleClass>(LinearAllocator, exampleClass);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that multiple objects can be allocated from a LinearAllocator.
    ///
    SECTION("MultipleObjects", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto valueA = IC::makeUnique<int>(LinearAllocator, 1);
        auto valueB = IC::makeUnique<int>(LinearAllocator, 2);
        auto valueC = IC::makeUnique<int>(LinearAllocator, 3);

        REQUIRE(*valueA == 1);
        REQUIRE(*valueB == 2);
        REQUIRE(*valueC == 3);
    }

    /// Confirms that deallocating an object allocated from a LinearAllocator does not affect other allocations.
    ///
    SECTION("Deallocation", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto valueA = IC::makeUnique<int>(LinearAllocator, 1);
        auto valueB = IC::makeUnique<int>(LinearAllocator, 2);
        valueB.reset();
        auto valueC = IC::makeUnique<int>(LinearAllocator, 3);
        valueB = IC::makeUnique<int>(LinearAllocator, 4);

        REQUIRE(*valueA == 1);
        REQUIRE(*valueB == 4);
        REQUIRE(*valueC == 3);
    }

    /// Confirms that objects of varying size can be allocated from a LinearAllocator.
    ///
    SECTION("VaryingSizedObjects", "[LinearAllocator]")
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

        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 64);

        auto valueA = IC::makeUnique<int>(LinearAllocator, 1);

        auto valueB = IC::makeUnique<LargeExampleClass>(LinearAllocator);
        memcpy(valueB->buffer, k_exampleBuffer, 10);

        valueA = IC::makeUnique<int>(LinearAllocator, 2);

        auto valueC = IC::makeUnique<MediumExampleClass>(LinearAllocator);
        valueC->m_x = 5;
        valueC->m_y = 10;
        valueC->m_z = 15;

        valueA = IC::makeUnique<int>(LinearAllocator, 3);

        REQUIRE(*valueA == 3);
        REQUIRE(strcmp(k_exampleBuffer, valueB->buffer) == 0);
        REQUIRE(valueC->m_x == 5);
        REQUIRE(valueC->m_y == 10);
        REQUIRE(valueC->m_z == 15);
    }

    /// Confirms that a new page can be successfully created if there is not enough room left in the current page.
    ///
    SECTION("Paging", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 32);

        auto valueA = IC::makeUnique<std::uint64_t>(LinearAllocator, 1);
        auto valueB = IC::makeUnique<std::uint64_t>(LinearAllocator, 2);
        auto valueC = IC::makeUnique<std::uint64_t>(LinearAllocator, 3);
        auto valueD = IC::makeUnique<std::uint64_t>(LinearAllocator, 4);
        auto valueE = IC::makeUnique<std::uint64_t>(LinearAllocator, 5);

        REQUIRE(*valueA == 1);
        REQUIRE(*valueB == 2);
        REQUIRE(*valueC == 3);
        REQUIRE(*valueD == 4);
        REQUIRE(*valueE == 5);
    }

    /// Confirms that resetting a Linear Allocator will allow previous memory to be re-used.
    ///
    SECTION("Reset", "[LinearAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::LinearAllocator LinearAllocator(buddyAllocator, 32);

        auto value = IC::makeUnique<std::uint64_t>(LinearAllocator, 1);
        auto valueARaw = value.get();
        value.reset();

        LinearAllocator.reset();

        value = IC::makeUnique<std::uint64_t>(LinearAllocator, 2);
        auto valueBRaw = value.get();

        REQUIRE(*value == 2);
        REQUIRE(valueARaw == valueBRaw);
    }
}