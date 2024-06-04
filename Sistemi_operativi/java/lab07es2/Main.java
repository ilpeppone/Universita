package lab07es2;

import java.io.IOException;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;

public class Main {
    public static void main(String[] args) {
        PipedInputStream pis = new PipedInputStream();
        try{
            PipedOutputStream pos = new PipedOutputStream(pis);

            FromInput fi = new FromInput(pos);
            ToOutput to = new ToOutput(pis);
            fi.start();
            to.start();
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
