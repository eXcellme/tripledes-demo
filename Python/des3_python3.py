# encoding:utf-8

from Crypto.Cipher import DES3
import base64

# 加密模式 ECB , 填充模式 PKCS5Padding
BS = DES3.block_size
pad = lambda s: s + (BS - len(s) % BS) * chr(BS - len(s) % BS)
unpad = lambda s : s[0:-s[-1]]

'''
  DES3加密
  参数：
    text str 待加密字符串 
    key str 密钥，使用appsecret
  返回：
    str 加密后的字符串
''' 
def encrypt(text, key):
    text = pad(text)
    cipher = DES3.new(key,DES3.MODE_ECB)
    m = cipher.encrypt(text) # m is bytes
    #m = base64.encodestring(m) # 会追加\n
    m = base64.b64encode(m)
    decrypted_text = m.decode('utf-8')
    return decrypted_text

'''
  DES3解密
  参数：
    decrypted_text str 解密字符串
    key str 密钥，使用appsecret
  返回：
    str 解密后的原始字符串
'''
def decrypt(decrypted_text, key):
    decrypted_bytes = bytes(decrypted_text, encoding='utf-8')
    #text = base64.decodestring(decrypted_bytes) #
    text = base64.b64decode(decrypted_bytes) #
    cipher = DES3.new(key, DES3.MODE_ECB)
    s = cipher.decrypt(text)
    s = unpad(s)
    s = s.decode('utf-8') # unpad and decode bytes to str    
    return s


if __name__ == '__main__':
    print(encrypt('Hello','1234567887654321'))
    print(decrypt('qO8nDeYzqTs=','1234567887654321'))
    
