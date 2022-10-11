import java.util.Map;

import util.RSA;

public class Main_RSA {
    public static void main(String args[]){
        try {
            Map<String, String> map= RSA.generateKeyPair();
            String pub=map.get("publicKey");
            String pri=map.get("privateKey");
            
            String data="testcontent";
            System.out.println("原始数据：");
            System.out.println(data);
            String en_result=RSA.encrypt(data,pub);
            System.out.println("加密后：");
            System.out.println(en_result);
            String de_result=RSA.decrypt(en_result, pri);
            System.out.println("解密后：");
            System.out.println(de_result);
            } 
            catch (Exception e) {
                e.printStackTrace();
            }
    }
}
