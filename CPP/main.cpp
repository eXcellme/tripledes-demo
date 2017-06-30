

#include <iostream>
#include <string>
#include <vector>

#include "Base64.h"
#include "Des.h"







int main() {
	Des des;
	
	std::string str = des.encrypt("cM3871p76OTwBU7bf6Nyxxxx","1234567890abcdefg");

	std::cout << Base64::encode(str) << std::endl;

	std::cout << des.decrypt("123456781234567812345678", Base64::decode("decrpyted_text")) << std::endl;


	return 0;
}