import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;
import java.security.spec.InvalidKeySpecException;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESedeKeySpec;
import sun.misc.BASE64Decoder;
import sun.misc.BASE64Encoder;


public class TripleDES {

  public static void main(String[] args) {
    String text = "Hello";
    String key = "123456781234567812345678";
    String c = encrypt(text,key);
    System.out.println(c);
    System.out.println(decrypt(c,key));

  }

  public static String encrypt(String text, String key){
    try {
      DESedeKeySpec spec = new DESedeKeySpec(key.getBytes());
      SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("desede");

      Key destKey = keyFactory.generateSecret(spec);

      Cipher cipher = Cipher.getInstance("desede" + "/ECB/PKCS5Padding");
      cipher.init(Cipher.ENCRYPT_MODE, destKey);

      byte[] textBs = text.getBytes("UTF-8");

      byte[] cipherText = cipher.doFinal(textBs);

      BASE64Encoder b64encoder = new BASE64Encoder();
      return b64encoder.encode(cipherText);
    } catch (InvalidKeyException e) {
      e.printStackTrace();
    } catch (NoSuchAlgorithmException e) {
      e.printStackTrace();
    } catch (InvalidKeySpecException e) {
      e.printStackTrace();
    } catch (NoSuchPaddingException e) {
      e.printStackTrace();
    } catch (BadPaddingException e) {
      e.printStackTrace();
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    } catch (IllegalBlockSizeException e) {
      e.printStackTrace();
    }

    return null;
  }
  public static String decrypt(String decryptedText, String key){

    try {

      BASE64Decoder b64decoder = new BASE64Decoder();
      byte[] textBs = b64decoder.decodeBuffer(decryptedText);
      DESedeKeySpec spec = new DESedeKeySpec(key.getBytes());
      SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("desede");

      Key destKey = keyFactory.generateSecret(spec);

      Cipher cipher = Cipher.getInstance("desede" + "/ECB/PKCS5Padding");
      cipher.init(Cipher.DECRYPT_MODE, destKey);

      byte[] cipherText = cipher.doFinal(textBs);

      return new String(cipherText,"UTF-8");

    } catch (InvalidKeyException e) {
      e.printStackTrace();
    } catch (NoSuchAlgorithmException e) {
      e.printStackTrace();
    } catch (InvalidKeySpecException e) {
      e.printStackTrace();
    } catch (NoSuchPaddingException e) {
      e.printStackTrace();
    } catch (BadPaddingException e) {
      e.printStackTrace();
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    } catch (IllegalBlockSizeException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    }

    return null;
  }
}
