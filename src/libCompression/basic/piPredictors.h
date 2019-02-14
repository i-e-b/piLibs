#pragma once

#include "../../libMath/piVecTypes.h"

namespace piLibs
{
	namespace piPredictors
	{
		class Size_1_Order_1
		{
		public:
			Size_1_Order_1();
			int encode(int qval);
			int decode(int qval);
		private:
			int mNum;
			int prev;
		};

		class Size_2_Order_1
		{
		public:
			Size_2_Order_1();
			ivec2 encode(ivec2 qval);
			ivec2 decode(ivec2 qval);
		private:
			int mNum;
			ivec2 prev;
		};

		class Size_3_Order_1
		{
		public:
			Size_3_Order_1();
			ivec3 encode(ivec3 qval);
			ivec3 decode(ivec3 qval);
		private:
			int mNum;
			ivec3 prev;
		};

		class Size_3_Order_2
		{
		public:
			Size_3_Order_2();
			ivec3 encode(ivec3 qval);
			ivec3 decode(ivec3 qval);
		private:
			int mNum;
			ivec3 prev;
			ivec3 prev2;
		};
	}
}