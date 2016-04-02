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

/// A series of unit tests for strings allocated from the memory pools.
///
TEST_CASE("String", "[Container]")
{
    /// Confirms that an empty string can be allocated from the Buddy Allocator.
    ///
    SECTION("MakeEmptyBuddyAllocator")
    {
        constexpr char k_testString[] = "test";

        IC::BuddyAllocator allocator(256, 16);

        auto string = IC::makeString(allocator);
        string.append(k_testString);

        REQUIRE(string == k_testString);
    }

    /// Confirms that an empty string can be allocated from the Frame Allocator.
    ///
    SECTION("MakeEmptyFrameAllocator")
    {
        constexpr char k_testString[] = "test";

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto string = IC::makeString(frameAllocator);
        string.append(k_testString);

        REQUIRE(string == k_testString);
    }

    /// Confirms that a string can be allocated from the Buddy Allocator with a C string.
    ///
    SECTION("MakeCStringBuddyAllocator")
    {
        constexpr char k_testString[] = "test";

        IC::BuddyAllocator allocator(256, 16);

        auto string = IC::makeString(allocator, k_testString);

        REQUIRE(string == k_testString);
    }

    /// Confirms that a string can be allocated from the Frame Allocator with a C string.
    ///
    SECTION("MakeCStringFrameAllocator")
    {
        constexpr char k_testString[] = "test";

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto string = IC::makeString(frameAllocator, k_testString);

        REQUIRE(string == k_testString);
    }

    /// Confirms that a string can be allocated from the Buddy Allocator with a buffer.
    ///
    SECTION("MakehBufferBuddyAllocator")
    {
        constexpr char k_testString[] = "test";
        constexpr std::size_t k_bufferSize = 4;

        IC::BuddyAllocator allocator(256, 16);

        auto string = IC::makeString(allocator, k_testString, k_bufferSize);

        REQUIRE(string == k_testString);
    }

    /// Confirms that a string can be allocated from the Frame Allocator with a buffer.
    ///
    SECTION("MakeBufferFrameAllocator")
    {
        constexpr char k_testString[] = "test";
        constexpr std::size_t k_bufferSize = 4;

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto string = IC::makeString(frameAllocator, k_testString, k_bufferSize);

        REQUIRE(string == k_testString);
    }

    /// Confirms that a string can be allocated from the Buddy Allocator using a std::string.
    ///
    SECTION("MakeStdStringBuddyAllocator")
    {
        const std::string testString = "test";

        IC::BuddyAllocator allocator(256, 16);

        auto string = IC::makeString(allocator, testString);

        REQUIRE(string == testString.c_str());
    }

    /// Confirms that a string can be allocated from the Frame Allocator using a std::string.
    ///
    SECTION("MakeStdStringFrameAllocator")
    {
        const std::string testString = "test";

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto string = IC::makeString(frameAllocator, testString);

        REQUIRE(string == testString.c_str());
    }

    /// Confirms that a string can be allocated from the Buddy Allocator with a range.
    ///
    SECTION("MakeRangeBuddyAllocator")
    {
        const std::string testString = "test";

        IC::BuddyAllocator allocator(256, 16);

        auto string = IC::makeString(allocator, testString.begin(), testString.end());

        REQUIRE(string == testString.c_str());
    }

    /// Confirms that a string can be allocated from the Frame Allocator with a range.
    ///
    SECTION("MakeRangeFrameAllocator")
    {
        const std::string testString = "test";

        IC::BuddyAllocator buddyAllocator(512);
        IC::FrameAllocator frameAllocator(buddyAllocator, 32);

        auto string = IC::makeString(frameAllocator, testString.begin(), testString.end());

        REQUIRE(string == testString.c_str());
    }
}