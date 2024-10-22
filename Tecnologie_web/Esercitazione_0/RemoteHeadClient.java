import java.io.*;
import java.net.*;

public class RemoteHeadClient {
    public void main(String[] args){
        if (args.length != 1){
            System.err.println("Usage: java RemoteHeadClient <hostname> <port> <filename>");
            System.exit(1);
        }
        try{
            String hostname = args[0];
            int port =Integer.parseInt(args[1]);
            String filename = args[2];

            Socket socket = new Socket(hostname, port);
            var netIn = new BufferedReader(new InputStreamReader (socket.getInputStream(), "UTF-8"));
            var netOut = new BufferedWriter(new OutputStreamWriter (socket.getOutputStream(), "UTF-8"));
            
            netOut.write(filename);
            netOut.newLine();
            netOut.flush();
        }
    }
}
