import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class rpsServer {
    public static void main(String[] args) {
        if(args.length!=1){
            System.err.println("Errore: java rpsServer porta");
            System.exit(-1);
        }

        var porta = args[0];

        try{
            var server = new ServerSocket(Integer.parseInt(porta));
            while(true){
                Socket clientSocket = server.accept();

                var netIn = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                var netOut = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

                String opzione = netIn.readLine();

                ProcessBuilder processBuilder;
                if(opzione!=null && !opzione.isEmpty()){
                    processBuilder = new ProcessBuilder("ps",opzione);
                } else {
                    processBuilder = new ProcessBuilder("ps");
                }
                Process process= processBuilder.start();
                try{
                    BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    String line;
                    while((line=br.readLine())!=null){
                        netOut.write(line);
                        netOut.newLine();
                    }
                    netOut.flush();
                    process.waitFor();
                    clientSocket.close();
                }catch (Exception e){
                    System.err.println("Errore connessione col client" + e.getMessage());
                }
            }
            
        } catch (Exception e){
            System.err.println("Errore server" + e.getMessage());
        }

    }
}
