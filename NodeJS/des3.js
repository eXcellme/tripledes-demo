var crypto = require('crypto');
var key = '123456781234567812345678'; //加密的秘钥 app secret
var demo_encryped = 'oVmfzWxhH88=';
var demo_decryped = 'Hello';

encrypt = function (str) {
    var cipher = crypto.createCipheriv('des-ede3', key, new Buffer(0));
    var crypted = cipher.update(str, 'utf8', 'base64');  // data[, input_encoding][, output_encoding]
    crypted += cipher.final('base64');
    return crypted;
}

decrypt = function(str) {
	var decipher = crypto.createDecipheriv('des-ede3', key, new Buffer(0));
	var dec = decipher.update(str, 'base64', 'utf8');
	dec += decipher.final('utf8');
	return dec;
}

console.log(encrypt(demo_decryped))
console.log(decrypt(demo_encryped))