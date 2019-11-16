#pragma once
#include<chrono>
using namespace std;
namespace Paradox {

		class Time {
		public : 
		static const int SECONDS  = 10000000.0; 
			
		static auto getTime() -> long {
			chrono::system_clock::time_point tp = chrono::system_clock::now();
			//std::cout << chrono::system_clock::period::num << " / " << chrono::system_clock::period::den << std::endl;
			return tp.time_since_epoch().count();
			}

		};
} 