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
#include <deque>

namespace ICMemoryTest
{
    namespace
    {
        constexpr std::size_t k_linearAllocatorBufferSize = 4 * 1024;
        constexpr std::size_t k_buddyAllocatorBufferSize = 2048;
        constexpr std::size_t k_buddyAllocatorMinBlockSize = 16;
    }

    /// A series of unit tests for deques allocated from the memory pools.
    ///
    TEST_CASE("Deque", "[Container]")
    {
        /// Confirms that an empty deque can be allocated from the Buddy Allocator.
        ///
        SECTION("MakeEmptyBuddyAllocator")
        {
            IC::BuddyAllocator allocator(k_buddyAllocatorBufferSize, k_buddyAllocatorMinBlockSize);

            auto deque = IC::MakeDeque<int>(allocator);
            deque.push_back(5);
            deque.push_back(6);

            REQUIRE(deque.size() == 2);
            REQUIRE(deque.front() == 5);

            deque.pop_front();
            REQUIRE(deque.front() == 6);
        }

        /// Confirms that an empty deque can be allocated from the Linear Allocator.
        ///
        SECTION("MakeEmptyLinearAllocator")
        {
            IC::LinearAllocator linearAllocator(k_linearAllocatorBufferSize);

            auto deque = IC::MakeDeque<int>(linearAllocator);
            deque.push_back(5);
            deque.push_back(6);

            REQUIRE(deque.size() == 2);
            REQUIRE(deque.front() == 5);

            deque.pop_front();
            REQUIRE(deque.front() == 6);
        }

        /// Confirms that a deque can be allocated from the Buddy Allocator with a range.
        ///
        SECTION("MakeRangeBuddyAllocator")
        {
            const std::deque<int> toCopy = { 5, 6 };

            IC::BuddyAllocator allocator(k_buddyAllocatorBufferSize, k_buddyAllocatorMinBlockSize);

            auto deque = IC::MakeDeque<int>(allocator, toCopy.begin(), toCopy.end());

            REQUIRE(deque.size() == 2);
            REQUIRE(deque.front() == 5);

            deque.pop_front();
            REQUIRE(deque.front() == 6);
        }

        /// Confirms that a deque can be allocated from the Linear Allocator with a range.
        ///
        SECTION("MakeRangeLinearAllocator")
        {
            const std::deque<int> toCopy = { 5, 6 };

            IC::LinearAllocator linearAllocator(k_linearAllocatorBufferSize);

            auto deque = IC::MakeDeque<int>(linearAllocator, toCopy.begin(), toCopy.end());

            REQUIRE(deque.size() == 2);
            REQUIRE(deque.front() == 5);

            deque.pop_front();
            REQUIRE(deque.front() == 6);
        }

        /// Confirms that a deque can be allocated from the Buddy Allocator using a std::deque.
        ///
        SECTION("MakeStdDequeBuddyAllocator")
        {
            const std::deque<int> toCopy = { 5, 6 };

            IC::BuddyAllocator allocator(k_buddyAllocatorBufferSize, k_buddyAllocatorMinBlockSize);

            auto deque = IC::MakeDeque<int>(allocator, toCopy);

            REQUIRE(deque.size() == 2);
            REQUIRE(deque.front() == 5);

            deque.pop_front();
            REQUIRE(deque.front() == 6);
        }

        /// Confirms that a deque can be allocated from the Linear Allocator using a std::deque.
        ///
        SECTION("MakeStdDequeLinearAllocator")
        {
            const std::deque<int> toCopy = { 5, 6 };

            IC::LinearAllocator linearAllocator(k_linearAllocatorBufferSize);

            auto deque = IC::MakeDeque<int>(linearAllocator, toCopy);

            REQUIRE(deque.size() == 2);
            REQUIRE(deque.front() == 5);

            deque.pop_front();
            REQUIRE(deque.front() == 6);
        }
    }
}