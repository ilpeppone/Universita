import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class rpsClient{
    public static void main(String[] args) {
        if(args.length<2 || args.length>3){
            System.err.println("Errore: sintassi corretta: java rpsClient hostname porta <option>");
            System.exit(-1);
        }

        var hostname = args[0];
        var porta = args[1];
        

        try{
            var s = new Socket(hostname,Integer.parseInt(porta));
            var netIn = new BufferedReader(new InputStreamReader(s.getInputStream(),"UTF-8"));
            var netOut = new BufferedWriter(new OutputStreamWriter(s.getOutputStream(),"UTF-8"));
            
            netOut.write(hostname);
            netOut.newLine();
            if(args.length==3){
                var opzione = args[2];
                netOut.write(opzione);
                netOut.newLine();
            }
            netOut.flush();

            String line;

            while((line = netIn.readLine())!= null){
                if (line.isEmpty()) {
                    break;  // Esce dal ciclo se il server invia una riga vuota
                }
                System.out.println(line);
            }

            s.close();
            
        }catch (Exception e) {
            System.err.println(e.getMessage());
        }

    }
}