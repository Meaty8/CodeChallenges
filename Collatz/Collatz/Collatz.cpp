// Collatz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <format>
struct ScopedTimer
{
    ScopedTimer() : startTime_(std::chrono::steady_clock::now()) {}
    ~ScopedTimer()
    {
        std::chrono::duration<double> diff = std::chrono::steady_clock::now() - startTime_;
        std::cout << std::format("\nTime : {} seconds\n", diff.count() );
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> startTime_;
};


//======================================= ATTEMPT 2 . template option ====================
//
//auto Collatz_(auto i)
//{
//    auto isEven = i % 2 == 0;
//	  return isEven ? i / 2 : (3 * i) + 1;
//}
//auto BruteForceInner_()
//{
//	std::pair maxPair = { 0, 0 };
//	for (int i = 1; i < 100; ++i)
//	{
//		auto x = i;
//		auto count = 1;
//		do
//		{
//			x = Collatz_(x);
//			++count;
//		} while (x != 1);
//		if (count > maxPair.first)
//		{
//			maxPair = { count, i };
//		}
//	}
//	return maxPair;
//}
//void BruteForce_()
//{
//	std::cout << "Brute force\n";
//	ScopedTimer t;
//	auto maxPair = BruteForceInner_();
//	std::cout << "count " << maxPair.first << " value " << maxPair.second;
//}
//
//enum class NumType : bool
//{
//	Even = true,
//	Odd = false
//};
//
//template <NumType, auto, auto>
//struct CollatzInner;
//
//template<auto> 
//struct Collatz;
//
//constexpr NumType IsEven_(auto in)
//{
//	return NumType((in % 2) == 0);
//}
//template <auto N, auto COUNT>
//struct CollatzInner<NumType::Even, N, COUNT>
//	: public CollatzInner<IsEven_(N / 2), N / 2, COUNT + 1> {};
//
//template <auto N, auto COUNT>
//struct CollatzInner<NumType::Odd, N, COUNT>
//	: public CollatzInner<IsEven_((N * 3) + 1), (N * 3) + 1, COUNT + 1> {};
//
//template <auto COUNT> 
//struct CollatzInner<NumType::Odd, 1, COUNT >
//{
//	static const auto Count = COUNT;
//};
//
//template<auto N> 
//struct Collatz 
//	: public CollatzInner< IsEven_(N), N, 0>
//{
//	static const auto Input = N;
//};
//
//template <int N>
//constexpr auto Collate_()
//{
//	return std::make_pair(Collatz<N>::Count, Collatz<N>::Input);
//}
//
//
//constexpr auto Max_(auto left, auto right)
//{
//	return (left > right) ? left : right;
//}
//
//template<int LOOP> 
//struct Loop
//{
//	static const auto Biggest = Max_(Collatz<LOOP>::Count, Loop<LOOP - 1>::Biggest);
//};
//
//template<>
//struct Loop<1>
//{
//	static const auto Biggest = 1;
//};
//


//======================================= ATTEMPT 1 . Brute force with consteval option ====================
#define _PRECOMPILE_ON 0

#if _PRECOMPILE_ON == 1
#define CONSTEVAL consteval
#else
#define CONSTEVAL 
#endif

CONSTEVAL auto Collatz_(auto i)
{
	auto isEven = i % 2 == 0;
	return isEven ? i / 2 : (3 * i) + 1;
}
CONSTEVAL auto CollatzInner_(auto i, auto count)
{
	if(i == 1)
		return count;
	return CollatzInner_(Collatz_(i), count + 1);
}

CONSTEVAL auto BruteForceInner_()
{
	std::pair< uint64_t, uint64_t> maxPair = { 0u, 0u };
	for (uint64_t i = 1; i < 1000000; ++i)
	{
		auto count = CollatzInner_(i, 0);
		if (count > maxPair.first)
		{
			maxPair = { count, i };
		}
	}
	return maxPair;
}
void BruteForce_()
{
	std::cout << "Brute force\n";
	ScopedTimer t;
	auto maxPair = BruteForceInner_();
	std::cout << "count " << maxPair.first << " value " << maxPair.second;
}

int main()
{
	ScopedTimer x;
	/*{
		ScopedTimer x;
		auto pair = Collate_<837799>();
		std::cout << std::format("Collatz output {}, {}\n", pair.first, pair.second);
		std::cout << "Loop output " << Loop<100>::Biggest << std::endl;
	}*/
	BruteForce_();
    return 0;
}
