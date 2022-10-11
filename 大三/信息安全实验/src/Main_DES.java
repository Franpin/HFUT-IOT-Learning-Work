import util.DES;
public class Main_DES{
    public static void main(String args[]){

        DES.encryptFile("aaaaaaaa", "1.mp4", 
                        "2.mp4");
        DES.decryptFile("aaaaaaaa", "2.mp4", "1.mp4");
    }

}