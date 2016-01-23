// Created by Ian Copland on 2016-01-18
//
// The MIT License(MIT)
// 
// Copyright(c) 2015 Ian Copland
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

TEST_CASE("A unique pointer to a primitive can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeUnique<int>(allocator);
    *allocated = 1;

    REQUIRE(*allocated == 1);
}

TEST_CASE("A unique pointer to a primitive with an initial value can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeUnique<int>(allocator, 1);

    REQUIRE(*allocated == 1);
}

TEST_CASE("A unique pointer to a struct instance can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    struct ExampleClass
    {
        int m_x, m_y;
    };

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeUnique<ExampleClass>(allocator);
    allocated->m_x = 1;
    allocated->m_y = 2;

    REQUIRE(allocated->m_x == 1);
    REQUIRE(allocated->m_y == 2);
}

TEST_CASE("A unique pointer to a struct instance with a constructor can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    struct ExampleClass
    {
        ExampleClass(int x, int y) : m_x(x), m_y(y) {}
        int m_x, m_y;
    };

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeUnique<ExampleClass>(allocator, 1, 2);

    REQUIRE(allocated->m_x == 1);
    REQUIRE(allocated->m_y == 2);
}

TEST_CASE("A unique pointer to a struct instance can be copy constructed from a BuddyAllocator.", "[BuddyAllocator]")
{
    struct ExampleClass
    {
        int m_x, m_y;
    };

    ExampleClass exampleClass;
    exampleClass.m_x = 1;
    exampleClass.m_y = 2;

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeUnique<ExampleClass>(allocator, exampleClass);

    REQUIRE(allocated->m_x == 1);
    REQUIRE(allocated->m_y == 2);
}

TEST_CASE("A shared pointer to a primitive can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeShared<int>(allocator);
    *allocated = 1;

    REQUIRE(*allocated == 1);
}

TEST_CASE("A shared pointer to a primitive with an initial value can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeShared<int>(allocator, 1);

    REQUIRE(*allocated == 1);
}

TEST_CASE("A shared pointer to a struct instance can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    struct ExampleClass
    {
        int m_x, m_y;
    };

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeShared<ExampleClass>(allocator);
    allocated->m_x = 1;
    allocated->m_y = 2;

    REQUIRE(allocated->m_x == 1);
    REQUIRE(allocated->m_y == 2);
}

TEST_CASE("A shared pointer to a struct instance with a constructor can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    struct ExampleClass
    {
        ExampleClass(int x, int y) : m_x(x), m_y(y) {}
        int m_x, m_y;
    };

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeShared<ExampleClass>(allocator, 1, 2);

    REQUIRE(allocated->m_x == 1);
    REQUIRE(allocated->m_y == 2);
}

TEST_CASE("A shared pointer to a struct instance can be copy constructed from a BuddyAllocator.", "[BuddyAllocator]")
{
    struct ExampleClass
    {
        int m_x, m_y;
    };

    ExampleClass exampleClass;
    exampleClass.m_x = 1;
    exampleClass.m_y = 2;

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeShared<ExampleClass>(allocator, exampleClass);

    REQUIRE(allocated->m_x == 1);
    REQUIRE(allocated->m_y == 2);
}

TEST_CASE("A unique pointer to an array can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    const int k_numValues = 10;

    IC::BuddyAllocator allocator(256, 16);

    auto allocated = IC::makeUniqueArray<int>(allocator, 10);

    for (auto i = 0; i < k_numValues; ++i)
    {
        allocated[i] = i;
    }

    for (auto i = 0; i < k_numValues; ++i)
    {
        REQUIRE(allocated[i] == i);
    }
}

TEST_CASE("Multiple objects can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    IC::BuddyAllocator allocator(256, 16);

    auto valueA = IC::makeUnique<int>(allocator, 1);
    auto valueB = IC::makeUnique<int>(allocator, 2);
    auto valueC = IC::makeUnique<int>(allocator, 3);

    REQUIRE(*valueA == 1);
    REQUIRE(*valueB == 2);
    REQUIRE(*valueC == 3);
}

TEST_CASE("Deallocating an object allocated from a BuddyAllocator does not affect other allocations.", "[BuddyAllocator]")
{
    IC::BuddyAllocator allocator(256, 16);

    auto valueA = IC::makeUnique<int>(allocator, 1);
    auto valueB = IC::makeUnique<int>(allocator, 2);
    valueB.reset();
    auto valueC = IC::makeUnique<int>(allocator, 3);
    valueB = IC::makeUnique<int>(allocator, 4);

    REQUIRE(*valueA == 1);
    REQUIRE(*valueB == 4);
    REQUIRE(*valueC == 3);
}

TEST_CASE("Large objects can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    const char* k_exampleBuffer = "GVFuEQyRi*wIn#LAVl@5LWTLqKitenElz#EKiSMf#DW!wsa5Ev#xLxs(LH&IZkumGVFuEQyRi*wIn#LAVl@5LWTLqKitenElz#EKiSMf#DW!wsa5Ev#xLxs(LH&IZku\0";

    struct LargeExampleClass
    {
        char buffer[128];
    };

    IC::BuddyAllocator allocator(256, 16);

    auto value = IC::makeUnique<LargeExampleClass>(allocator);
    memcpy(value->buffer, k_exampleBuffer, 128);

    REQUIRE(strcmp(k_exampleBuffer, value->buffer) == 0);
}

TEST_CASE("Objects of varying size can be allocated from a BuddyAllocator.", "[BuddyAllocator]")
{
    const char* k_exampleBuffer = "GVFuEQyRi*wIn#LAVl@5LWTLqKitenElz#EKiSMf#DW!wsa5Ev#xLxs(LH&IZku\0";

    struct LargeExampleClass
    {
        char buffer[64];
    };

    struct MediumExampleClass
    {
        std::int64_t m_x;
        std::int64_t m_y;
        std::int64_t m_z;
    };

    IC::BuddyAllocator allocator(256, 16);

    auto valueA = IC::makeUnique<int>(allocator, 1);

    auto valueB = IC::makeUnique<LargeExampleClass>(allocator);
    memcpy(valueB->buffer, k_exampleBuffer, 128);

    valueA = IC::makeUnique<int>(allocator, 2);

    auto valueC = IC::makeUnique<MediumExampleClass>(allocator);
    valueC->m_x = 5;
    valueC->m_y = 10;
    valueC->m_z = 15;

    valueA = IC::makeUnique<int>(allocator, 3);

    REQUIRE(*valueA == 3);
    REQUIRE(strcmp(k_exampleBuffer, valueB->buffer) == 0);
    REQUIRE(valueC->m_x == 5);
    REQUIRE(valueC->m_y == 10);
    REQUIRE(valueC->m_z == 15);
}