#pragma once
#include "std_head.h"

namespace CppTest
{
	class Solution {
	public:
		static int lengthOfLongestSubstring(string s) {
			int ch[256] = { 0 };
			int len = 0;
			int maxlen = 0;
			memset(ch, -1, sizeof(ch));
			for (unsigned int i = 0; i < s.length(); i++)
			{
				char c = s[i];

				if (ch[c] == -1)
				{
					ch[c] = i;
					len++;
					cout << c << " : " << len << endl;
				}
				else
				{
					i = ch[c];
					maxlen = (len > maxlen) ? len : maxlen;
					memset(ch, -1, sizeof(ch));
					len = 0;
				}

			}
			
			maxlen = (len > maxlen) ? len : maxlen;
			return maxlen;
		}
	};
}