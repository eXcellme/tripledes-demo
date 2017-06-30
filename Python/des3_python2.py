# encoding:utf-8

from Crypto.Cipher import DES3
import base64

# 加密模式 ECB , 填充模式 PKCS5Padding
BS = DES3.block_size
pad = lambda s: s + (BS - len(s) % BS) * chr(BS - len(s) % BS)
unpad = lambda s : s[0:-ord(s[-1])]

'''
  DES3加密
  text 待加密字符串
  key 密钥，使用appsecret
''' 
def encrypt(text, key):
    text = pad(text)
    cipher = DES3.new(key,DES3.MODE_ECB)
    m = cipher.encrypt(text)
    m = base64.b64encode(m)
    return m.decode('utf-8')

'''
  DES3解密
  decrypted_text 解密字符串
  key 密钥，使用appsecret
'''
def decrypt(decrypted_text, key):
    text = base64.b64decode(decrypted_text)
    cipher = DES3.new(key, DES3.MODE_ECB)
    s = cipher.decrypt(text)
    s = unpad(s)
    return s.decode('utf-8')


if __name__ == '__main__':
    print encrypt('Hello','1234567887654321')
    print decrypt('qO8nDeYzqTs=','1234567887654321')
    
