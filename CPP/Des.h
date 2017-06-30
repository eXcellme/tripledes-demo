#include <string>
#include <openssl/des.h>
#include <openssl/evp.h>

#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")
class Des {
private:

	static const int CFBMODE = 64;


public:

	static std::string encrypt(std::string tmp_key, std::string in) {
		unsigned char key[24];


		memset(key, 0, sizeof(key));
		memcpy(key, tmp_key.c_str(), sizeof(key));

		DES_key_schedule schedule;
		DES_key_schedule schedule2;
		DES_key_schedule schedule3;
		DES_cblock desKey = { 0 };


		memcpy(desKey, key, 8);
		DES_set_key_unchecked(&desKey, &schedule);
		memcpy(desKey, key + 8, 8);
		DES_set_key_unchecked(&desKey, &schedule2);
		memcpy(desKey, key + 16, 8);
		DES_set_key_unchecked(&desKey, &schedule3);
		int i = 0;
		const size_t paddingLength = (8 - in.length() % 8);

		unsigned char padding[8];
		memset(padding, 8 - (in.length() % 8), 8);

		if (paddingLength)
		{
			in.append((char*)padding, paddingLength);
		}

		size_t dataLength = paddingLength + in.length();
		char tmp_buf[8];
		memset(tmp_buf, 0, 8);
		std::string data;
		//data.reserve(dataLength);
		unsigned char input[8];
		for (size_t i = 0; i < (dataLength / 8); i++)
		{
			/*
			DES_ede3_cfb_encrypt((const unsigned char*)in.c_str() + (i * 8), (unsigned char*)tmp_buf, CFBMODE, 8, &schedule,
				&schedule2, &schedule3, &iv,
				DES_ENCRYPT);
			*/
			//memset(input, 0, 8);
			memcpy(input, in.c_str() + (i * 8), 8);
			
			DES_ecb3_encrypt((const_DES_cblock*)input, (DES_cblock*)tmp_buf,&schedule, &schedule2, &schedule3, DES_ENCRYPT);
			
			data.append(tmp_buf, sizeof(tmp_buf));
		
		
		}

		return data;
	}


	static std::string decrypt(std::string tmp_key, std::string in) {
		//偏移向量
		//24位加密key，3des下秘钥必须为24位
		unsigned char key[24];


		memset(key, 0, sizeof(key));
		memcpy(key, tmp_key.c_str(), sizeof(key));


		DES_key_schedule schedule;
		DES_key_schedule schedule2;
		DES_key_schedule schedule3;
		DES_cblock desKey = { 0 };
		DES_cblock iv = { 0 };
		memcpy(desKey, key, 8);
		DES_set_key_unchecked(&desKey, &schedule);
		memcpy(desKey, key + 8, 8);
		DES_set_key_unchecked(&desKey, &schedule2);
		memcpy(desKey, key + 16, 8);
		DES_set_key_unchecked(&desKey, &schedule3);
		int i = 0;
		std::string padding;
		unsigned char input[8];
		unsigned char tmp_buf[8];
		//memset(tmp_buf, 0, 8);
		for (size_t i = 0; i < (in.length() / 8); i++)
		{
			/*
			DES_ede3_cfb_encrypt((const unsigned char*)in.c_str() + (i * 8), (unsigned char*)tmp_buf, CFBMODE, 8, &schedule,
				&schedule2, &schedule3, &iv,
				DES_DECRYPT);
			*/
			memcpy(input, in.c_str() + (i * 8), 8);
			DES_ecb3_encrypt((const_DES_cblock*)input, (DES_cblock*)tmp_buf,  &schedule,
				&schedule2, &schedule3, DES_DECRYPT);


			
			
			if (i == ((in.length() / 8) - 1) && tmp_buf[7] >= 0x01 && tmp_buf[7] <= 0x08)
			{
				padding.append((char *)tmp_buf, 8 - tmp_buf[7]);
			}
			else
			{
				padding.append((char *)tmp_buf, 8);
			}
		}
		return padding;
	}


};