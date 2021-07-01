#pragma once

// unordered_map test : ���� unordered_map, unordered_multimap �Ľӿ������� insert ������

#include <unordered_map>

#include "../unordered_map.h"
#include "test.h"
#include "../vector.h"

namespace LT
{
    namespace test
    {
        namespace unordered_map_test
        {

            void unordered_map_test()
            {
                std::cout << "[===============================================================]" << std::endl;
                std::cout << "[-------------- Run container test : unordered_map -------------]" << std::endl;
                std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
                LT::vector<LT::pair<int,int>> v;
                for (int i = 0; i < 5; ++i)
                    v.push_back(LT::pair<int,int>(5 - i, 5 - i));
                LT::unordered_map<int, int> um1;
                LT::unordered_map<int, int> um2(520);
                LT::unordered_map<int, int> um3(520, LT::hash<int>());
                LT::unordered_map<int, int> um4(520, LT::hash<int>(), LT::equal_to<int>());
                LT::unordered_map<int, int> um5(v.begin(), v.end());
                LT::unordered_map<int, int> um6(v.begin(), v.end(), 100);
                LT::unordered_map<int, int> um7(v.begin(), v.end(), 100, LT::hash<int>());
                LT::unordered_map<int, int> um8(v.begin(), v.end(), 100, LT::hash<int>(), LT::equal_to<int>());
                LT::unordered_map<int, int> um9(um5);
                LT::unordered_map<int, int> um10(std::move(um5));
                LT::unordered_map<int, int> um11;
                um11 = um6;
                LT::unordered_map<int, int> um12;
                um12 = std::move(um6);
                LT::unordered_map<int, int> um13{ LT::pair<int,int>(1,1),LT::pair<int,int>(2,3),LT::pair<int,int>(3,3) };
                LT::unordered_map<int, int> um14;
                um14 = { LT::pair<int,int>(1,1),LT::pair<int,int>(2,3),LT::pair<int,int>(3,3) };

                MAP_FUN_AFTER(um1, um1.emplace(1, 1));
                MAP_FUN_AFTER(um1, um1.emplace_hint(um1.begin(), 1, 2));
                MAP_FUN_AFTER(um1, um1.insert(LT::pair<int,int>(2, 2)));
                MAP_FUN_AFTER(um1, um1.insert(um1.end(), LT::pair<int,int>(3, 3)));
                MAP_FUN_AFTER(um1, um1.insert(v.begin(), v.end()));
                MAP_FUN_AFTER(um1, um1.erase(um1.begin()));
                MAP_FUN_AFTER(um1, um1.erase(um1.begin(), um1.find(3)));
                MAP_FUN_AFTER(um1, um1.erase(1));
                std::cout << std::boolalpha;
                FUN_VALUE(um1.empty());
                std::cout << std::noboolalpha;
                FUN_VALUE(um1.size());
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.max_bucket_count());
                FUN_VALUE(um1.bucket(1));
                FUN_VALUE(um1.bucket_size(um1.bucket(5)));
                MAP_FUN_AFTER(um1, um1.clear());
                MAP_FUN_AFTER(um1, um1.swap(um7));
                MAP_VALUE(*um1.begin());
                FUN_VALUE(um1.at(1));
                FUN_VALUE(um1[1]);
                std::cout << std::boolalpha;
                FUN_VALUE(um1.empty());
                std::cout << std::noboolalpha;
                FUN_VALUE(um1.size());
                FUN_VALUE(um1.max_size());
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.max_bucket_count());
                FUN_VALUE(um1.bucket(1));
                FUN_VALUE(um1.bucket_size(um1.bucket(1)));
                MAP_FUN_AFTER(um1, um1.reserve(1000));
                FUN_VALUE(um1.size());
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.bucket_size(1));
                FUN_VALUE(um1.bucket_size(2));
                FUN_VALUE(um1.bucket_size(3));
                MAP_FUN_AFTER(um1, um1.rehash(150));
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.count(1));
                MAP_VALUE(*um1.find(3));
                auto first = *um1.equal_range(3).first;
                auto second = *um1.equal_range(3).second;
                std::cout << " um1.equal_range(3) : from <" << first.first << ", " << first.second
                    << "> to <" << second.first << ", " << second.second << ">" << std::endl;
                FUN_VALUE(um1.load_factor());
                FUN_VALUE(um1.max_load_factor());
                MAP_FUN_AFTER(um1, um1.max_load_factor(1.5f));
                FUN_VALUE(um1.max_load_factor());
                PASSED;
#if PERFORMANCE_TEST_ON
                std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
                std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
                std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
                MAP_EMPLACE_TEST(unordered_map, LEN1 _M, LEN2 _M, LEN3 _M);
#else
                MAP_EMPLACE_TEST(unordered_map, LEN1 _S, LEN2 _S, LEN3 _S);
#endif
                std::cout << std::endl;
                std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
                PASSED;
#endif
                std::cout << "[-------------- End container test : unordered_map -------------]" << std::endl;
            }

            void unordered_multimap_test()
            {
                std::cout << "[===============================================================]" << std::endl;
                std::cout << "[----------- Run container test : unordered_multimap -----------]" << std::endl;
                std::cout << "[-------------------------- API test ---------------------------]" << std::endl;
                LT::vector<LT::pair<int,int>> v;
                for (int i = 0; i < 5; ++i)
                    v.push_back(LT::pair<int,int>(5 - i, 5 - i));
                LT::unordered_multimap<int, int> um1;
                LT::unordered_multimap<int, int> um2(520);
                LT::unordered_multimap<int, int> um3(520, LT::hash<int>());
                LT::unordered_multimap<int, int> um4(520, LT::hash<int>(), LT::equal_to<int>());
                LT::unordered_multimap<int, int> um5(v.begin(), v.end());
                LT::unordered_multimap<int, int> um6(v.begin(), v.end(), 100);
                LT::unordered_multimap<int, int> um7(v.begin(), v.end(), 100, LT::hash<int>());
                LT::unordered_multimap<int, int> um8(v.begin(), v.end(), 100, LT::hash<int>(), LT::equal_to<int>());
                LT::unordered_multimap<int, int> um9(um5);
                LT::unordered_multimap<int, int> um10(std::move(um5));
                LT::unordered_multimap<int, int> um11;
                um11 = um6;
                LT::unordered_multimap<int, int> um12;
                um12 = std::move(um6);
                LT::unordered_multimap<int, int> um13{ LT::pair<int,int>(1,1),LT::pair<int,int>(2,3),LT::pair<int,int>(3,3) };
                LT::unordered_multimap<int, int> um14;
                um14 = { LT::pair<int,int>(1,1),LT::pair<int,int>(2,3),LT::pair<int,int>(3,3) };

                MAP_FUN_AFTER(um1, um1.emplace(1, 1));
                MAP_FUN_AFTER(um1, um1.emplace_hint(um1.begin(), 1, 2));
                MAP_FUN_AFTER(um1, um1.insert(LT::pair<int,int>(2, 2)));
                MAP_FUN_AFTER(um1, um1.insert(um1.end(), LT::pair<int,int>(3, 3)));
                MAP_FUN_AFTER(um1, um1.insert(v.begin(), v.end()));
                MAP_FUN_AFTER(um1, um1.erase(um1.begin()));
                MAP_FUN_AFTER(um1, um1.erase(um1.begin(), um1.find(3)));
                MAP_FUN_AFTER(um1, um1.erase(1));
                std::cout << std::boolalpha;
                FUN_VALUE(um1.empty());
                std::cout << std::noboolalpha;
                FUN_VALUE(um1.size());
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.max_bucket_count());
                FUN_VALUE(um1.bucket(1));
                FUN_VALUE(um1.bucket_size(um1.bucket(5)));
                MAP_FUN_AFTER(um1, um1.clear());
                MAP_FUN_AFTER(um1, um1.swap(um7));
                MAP_VALUE(*um1.begin());
                std::cout << std::boolalpha;
                FUN_VALUE(um1.empty());
                std::cout << std::noboolalpha;
                FUN_VALUE(um1.size());
                FUN_VALUE(um1.max_size());
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.max_bucket_count());
                FUN_VALUE(um1.bucket(1));
                FUN_VALUE(um1.bucket_size(um1.bucket(1)));
                MAP_FUN_AFTER(um1, um1.reserve(1000));
                FUN_VALUE(um1.size());
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.bucket_size(1));
                FUN_VALUE(um1.bucket_size(2));
                FUN_VALUE(um1.bucket_size(3));
                MAP_FUN_AFTER(um1, um1.rehash(150));
                FUN_VALUE(um1.bucket_count());
                FUN_VALUE(um1.count(1));
                MAP_VALUE(*um1.find(3));
                auto first = *um1.equal_range(3).first;
                auto second = *um1.equal_range(3).second;
                std::cout << " um1.equal_range(3) : from <" << first.first << ", " << first.second
                    << "> to <" << second.first << ", " << second.second << ">" << std::endl;
                FUN_VALUE(um1.load_factor());
                FUN_VALUE(um1.max_load_factor());
                MAP_FUN_AFTER(um1, um1.max_load_factor(1.5f));
                FUN_VALUE(um1.max_load_factor());
                PASSED;
#if PERFORMANCE_TEST_ON
                std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
                std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
                std::cout << "|       emplace       |";
#if LARGER_TEST_DATA_ON
                MAP_EMPLACE_TEST(unordered_multimap, LEN1 _M, LEN2 _M, LEN3 _M);
#else
                MAP_EMPLACE_TEST(unordered_multimap, LEN1 _S, LEN2 _S, LEN3 _S);
#endif
                std::cout << std::endl;
                std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
                PASSED;
#endif
                std::cout << "[----------- End container test : unordered_multimap -----------]" << std::endl;
            }

        } // namespace unordered_map_test
    } // namespace test
} // namespace LT
