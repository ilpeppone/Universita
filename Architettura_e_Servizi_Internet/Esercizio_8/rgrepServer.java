import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class rgrepServer {
    public static void main(String[] args) {
        if(args.length!=1){
            System.err.println("Uso: java rgrepServer porta");
            System.exit(-1);
        }

        var porta = args[0];
        try{
            var server = new ServerSocket(Integer.parseInt(porta));
            while(true){
                try( Socket clientSocket = server.accept()){

                    var netIn = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    var netOut = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));

                    String stringa = netIn.readLine();
                    String nome_file = netIn.readLine();
                    
                    ProcessBuilder pb = new ProcessBuilder("find", ".", "-name",nome_file+".*");
                    Process process = pb.start();
                    BufferedReader processOutput = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    String filePath = processOutput.readLine();
                    processOutput.close();

                    if (filePath==null || filePath.isEmpty()){
                        netOut.write("file non trovato!\n");
                        netOut.flush();
                        break;
                    }

                    if (filePath.startsWith("./")) {
                        filePath = filePath.substring(2);
                    }

                    System.out.println("file trovato!\n"+ filePath);
                    //funziona solo se specifico l'estensione del file 
                    ProcessBuilder pb2 = new ProcessBuilder("grep",stringa,filePath);
                    Process process2 = pb2.start();

                    BufferedReader grep_output=new BufferedReader(new InputStreamReader(process2.getInputStream()));
                    String line ;
                    Boolean found = false;
                    while((line=grep_output.readLine())!=null){
                        netOut.write(line);
                        netOut.newLine();
                        netOut.flush();
                        found=true;
                    }
                    if (!found){
                        netOut.write("Nessuna corrispondenza trovata\n");
                        netOut.flush();
                    }
                    grep_output.close();
                    process2.waitFor();
                    
                } catch (Exception e){
                    System.err.println("Errore socket client" + e.getMessage());
                }
            }
            server.close();
        } catch (Exception e){
            System.err.println("Errore socket server" + e.getMessage());
        }
    }
}
