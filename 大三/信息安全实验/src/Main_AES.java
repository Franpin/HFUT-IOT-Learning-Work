import util.AES;
public class Main_AES {
    public static void main(String args[]){
        AES.encryptFile("aaaaaaaaaaaaaaaa", "3.mp4", "4.mp4");
        AES.decryptFile("aaaaaaaaaaaaaaaa", "4.mp4", "3.mp4");
    }
}
