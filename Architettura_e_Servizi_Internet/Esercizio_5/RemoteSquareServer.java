import java.io.*;
import java.net.*;

public class RemoteSquareServer {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Errore! Sintassi corretta è:");
            System.err.println("\tjava RemoteSquareServer porta");
            System.exit(1);
        }
        Integer quadrato;
        String quad_string;
        var port = args[0];

        try{
            var server = new ServerSocket(Integer.parseInt(port));
            while(true){
                var s = server.accept();

            var netIn = new BufferedReader(new InputStreamReader(s.getInputStream(), "UTF-8"));
            var netOut = new BufferedWriter(new OutputStreamWriter(s.getOutputStream(), "UTF-8"));

            var numero = netIn.readLine();
            int numero_int= Integer.parseInt(numero);
            quadrato = numero_int * numero_int;
            quad_string= Integer.toString(quadrato);

            System.out.println("quadrato: " + quad_string);
            netOut.write(quad_string + "\n");
            netOut.flush();

            s.close();}
        } catch (Exception e){
            System.err.println(e.getMessage());
            e.printStackTrace(System.err);
            System.exit(1);
        }
    }
}
