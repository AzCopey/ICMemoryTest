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

/// A series of tests for the FrameAllocator
///
TEST_CASE("FrameAllocator", "[Allocator]")
{
    /// Confirms that a unique pointer to a fundamental can be allocated from a FrameAllocator.
    ///
    SECTION("UniqueFundamental", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<int>(frameAllocator);
        *allocated = 1;

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a unique pointer to a fundamental with an initial value can be allocated from a FrameAllocator.
    ///
    SECTION("UniqueFundamentalInitialValue", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<int>(frameAllocator, 1);

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a unique pointer to a struct instance can be allocated from a FrameAllocator.
    ///
    SECTION("UniqueStruct", "[FrameAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<ExampleClass>(frameAllocator);
        allocated->m_x = 1;
        allocated->m_y = 2;

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a unique pointer to a struct instance with a constructor can be allocated from a FrameAllocator.
    ///
    SECTION("UniqueStructConstructor", "[FrameAllocator]")
    {
        struct ExampleClass
        {
            ExampleClass(int x, int y) : m_x(x), m_y(y) {}
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<ExampleClass>(frameAllocator, 1, 2);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a unique pointer to a struct instance can be copy constructed from a FrameAllocator.
    ///
    SECTION("UniqueStructCopyConstructor", "[FrameAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        ExampleClass exampleClass;
        exampleClass.m_x = 1;
        exampleClass.m_y = 2;

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUnique<ExampleClass>(frameAllocator, exampleClass);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a unique pointer to an array can be allocated from a FrameAllocator.
    ///
    SECTION("UniqueArray", "[FrameAllocator]")
    {
        const int k_numValues = 10;

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeUniqueArray<int>(frameAllocator, 10);

        for (auto i = 0; i < k_numValues; ++i)
        {
            allocated[i] = i;
        }

        for (auto i = 0; i < k_numValues; ++i)
        {
            REQUIRE(allocated[i] == i);
        }
    }

    /// Confirms that a shared pointer to a fundamental can be allocated from a FrameAllocator.
    ///
    SECTION("SharedFundamental", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<int>(frameAllocator);
        *allocated = 1;

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a shared pointer to a fundamental with an initial value can be allocated from a FrameAllocator.
    ///
    SECTION("SharedFundamentalInitialValue", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<int>(frameAllocator, 1);

        REQUIRE(*allocated == 1);
    }

    /// Confirms that a shared pointer to a struct instance can be allocated from a FrameAllocator.
    ///
    SECTION("SharedStruct", "[FrameAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<ExampleClass>(frameAllocator);
        allocated->m_x = 1;
        allocated->m_y = 2;

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a shared pointer to a struct instance with a constructor can be allocated from a FrameAllocator.
    ///
    SECTION("SharedStructConstructor", "[FrameAllocator]")
    {
        struct ExampleClass
        {
            ExampleClass(int x, int y) : m_x(x), m_y(y) {}
            int m_x, m_y;
        };

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<ExampleClass>(frameAllocator, 1, 2);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that a shared pointer to a struct instance can be copy constructed from a FrameAllocator.
    ///
    SECTION("SharedStructCopyConstructor", "[FrameAllocator]")
    {
        struct ExampleClass
        {
            int m_x, m_y;
        };

        ExampleClass exampleClass;
        exampleClass.m_x = 1;
        exampleClass.m_y = 2;

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto allocated = IC::makeShared<ExampleClass>(frameAllocator, exampleClass);

        REQUIRE(allocated->m_x == 1);
        REQUIRE(allocated->m_y == 2);
    }

    /// Confirms that multiple objects can be allocated from a FrameAllocator.
    ///
    SECTION("MultipleObjects", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto valueA = IC::makeUnique<int>(frameAllocator, 1);
        auto valueB = IC::makeUnique<int>(frameAllocator, 2);
        auto valueC = IC::makeUnique<int>(frameAllocator, 3);

        REQUIRE(*valueA == 1);
        REQUIRE(*valueB == 2);
        REQUIRE(*valueC == 3);
    }

    /// Confirms that deallocating an object allocated from a FrameAllocator does not affect other allocations.
    ///
    SECTION("Deallocation", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto valueA = IC::makeUnique<int>(frameAllocator, 1);
        auto valueB = IC::makeUnique<int>(frameAllocator, 2);
        valueB.reset();
        auto valueC = IC::makeUnique<int>(frameAllocator, 3);
        valueB = IC::makeUnique<int>(frameAllocator, 4);

        REQUIRE(*valueA == 1);
        REQUIRE(*valueB == 4);
        REQUIRE(*valueC == 3);
    }

    /// Confirms that objects of varying size can be allocated from a FrameAllocator.
    ///
    SECTION("VaryingSizedObjects", "[FrameAllocator]")
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
        IC::FrameAllocator frameAllocator(buddyAllocator, 64);

        auto valueA = IC::makeUnique<int>(frameAllocator, 1);

        auto valueB = IC::makeUnique<LargeExampleClass>(frameAllocator);
        memcpy(valueB->buffer, k_exampleBuffer, 10);

        valueA = IC::makeUnique<int>(frameAllocator, 2);

        auto valueC = IC::makeUnique<MediumExampleClass>(frameAllocator);
        valueC->m_x = 5;
        valueC->m_y = 10;
        valueC->m_z = 15;

        valueA = IC::makeUnique<int>(frameAllocator, 3);

        REQUIRE(*valueA == 3);
        REQUIRE(strcmp(k_exampleBuffer, valueB->buffer) == 0);
        REQUIRE(valueC->m_x == 5);
        REQUIRE(valueC->m_y == 10);
        REQUIRE(valueC->m_z == 15);
    }

    /// Confirms that a new page can be successfully created if there is not enough room left in the current page.
    ///
    SECTION("Paging", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto valueA = IC::makeUnique<std::uint64_t>(frameAllocator, 1);
        auto valueB = IC::makeUnique<std::uint64_t>(frameAllocator, 2);
        auto valueC = IC::makeUnique<std::uint64_t>(frameAllocator, 3);
        auto valueD = IC::makeUnique<std::uint64_t>(frameAllocator, 4);
        auto valueE = IC::makeUnique<std::uint64_t>(frameAllocator, 5);

        REQUIRE(*valueA == 1);
        REQUIRE(*valueB == 2);
        REQUIRE(*valueC == 3);
        REQUIRE(*valueD == 4);
        REQUIRE(*valueE == 5);
    }

    /// Confirms that resetting a frame allocator will allow previous memory to be re-used.
    ///
    SECTION("Reset", "[FrameAllocator]")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto value = IC::makeUnique<std::uint64_t>(frameAllocator, 1);
        auto valueARaw = value.get();
        value.reset();

        frameAllocator.reset();

        value = IC::makeUnique<std::uint64_t>(frameAllocator, 2);
        auto valueBRaw = value.get();

        REQUIRE(*value == 2);
        REQUIRE(valueARaw == valueBRaw);
    }
}