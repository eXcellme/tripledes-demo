<?php


class DES
{
    private $key;

    /**
     * DES constructor.
     * @param string $key
     * @param string $iv
     * @throws Exception
     */
    public function __construct(string $cipher, string $key)
    {
        if (!extension_loaded('openssl')) {
            throw  new  \Exception("OpenSSL extension should be required.");
        }
        if (!in_array(strtolower($cipher), openssl_get_cipher_methods())) {
            throw  new  \Exception("Your cipher is not allowed. Pls choose one in openssl_get_cipher_methods().");
        }
        $this->key = $key;
    }

    /**
     * 加密
     * @param string $value
     * @return string
     */
    public function encrypt($value)
    {
        return openssl_encrypt($value, $this->cipher, $this->key);
    }

    /**
     * 解密
     * @param string $value
     * @return string
     */
    public function decrypt($value)
    {
        return openssl_decrypt($value, $this->cipher, $this->key);
    }
}
