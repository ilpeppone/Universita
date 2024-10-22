
import java.net.*;
import java.io.*;

public class RemoteHeadServer{

    public static void main(String[] args){
        if (args.length != 1){
            System.err.println("Usage: java RemoreHeadServer port");
            System.exit(1);
        } try {
            var ss = new ServerSocket(Integer.parseInt(args[0]));
            while (true){
            var ns = ss.accept();

            //Servizio 
            var netIn = new BufferedReader(new InputStreamReader (ns.getInputStream(), "UTF-8"));
            var netOut = new BufferedWriter(new OutputStreamWriter (ns.getOutputStream(), "UTF-8"));

            //Ricezione file
            var filename = netIn.readLine();
    
            //Apertura file
            BufferedReader fileIn;
            try{
                var file = new BufferedReader(new FileReader(filename));
                var i = 1;
                String line;
                while (((line = file.readLine()) != null) && i++ <=5){
                    netOut.write(line);
                    netOut.newLine();
                }
                netOut.flush();
            } catch (FileNotFoundException e){
                //niente da fare
            }
            ns.close();
            //Servizio - a qui
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
            e.printStackTrace(System.err);
            System.exit(1);
        }
    }
}