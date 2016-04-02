// Created by Ian Copland on 2016-04-02
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
#include <vector>

/// A series of unit tests for vectors allocated from the memory pools.
///
TEST_CASE("Vector", "[Container]")
{
    /// Confirms that an empty vector can be allocated from the Buddy Allocator.
    ///
    SECTION("MakeEmptyBuddyAllocator")
    {
        IC::BuddyAllocator allocator(256, 16);

        auto vec = IC::makeVector<int>(allocator);

        vec.push_back(5);
        vec.push_back(6);

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 6);
    }

    /// Confirms that an empty vector can be allocated from the Frame Allocator.
    ///
    SECTION("MakeEmptyFrameAllocator")
    {
        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto vec = IC::makeVector<int>(frameAllocator);

        vec.push_back(5);
        vec.push_back(6);

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 6);
    }

    /// Confirms that a vector can be allocated from the Buddy Allocator with a range.
    ///
    SECTION("MakeRangeBuddyAllocator")
    {
        const std::vector<int> toCopy = { 5, 6 };

        IC::BuddyAllocator allocator(256, 16);

        auto vec = IC::makeVector<int>(allocator, toCopy.begin(), toCopy.end());

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 6);
    }

    /// Confirms that a vector can be allocated from the Frame Allocator with a range.
    ///
    SECTION("MakeRangeFrameAllocator")
    {
        const std::vector<int> toCopy = { 5, 6 };

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto vec = IC::makeVector<int>(frameAllocator, toCopy.begin(), toCopy.end());

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 6);
    }

    /// Confirms that a vector can be allocated from the Buddy Allocator using a std::vector.
    ///
    SECTION("MakeStdVectorBuddyAllocator")
    {
        const std::vector<int> toCopy = { 5, 6 };

        IC::BuddyAllocator allocator(256, 16);

        auto vec = IC::makeVector<int>(allocator, toCopy);

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 6);
    }

    /// Confirms that a vector can be allocated from the Frame Allocator using a std::vector.
    ///
    SECTION("MakeStdVectorFrameAllocator")
    {
        const std::vector<int> toCopy = { 5, 6 };

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto vec = IC::makeVector<int>(frameAllocator, toCopy);

        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 5);
        REQUIRE(vec[1] == 6);
    }
}