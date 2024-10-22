import java.io.*;
import java.net.*;

public class Server {

    public static void main(String[] args) throws IOException {
    	// Apro la socket sulla porta 9090
		ServerSocket listener = new ServerSocket(9090);
        try {
	    	System.out.println("Server Running ...");				
			
            while (true) {
				// Accetto le connessioni entranti
                Socket socket = listener.accept();
		        
				// Leggo dalla socket 
				BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		        // Memorizzo nella variabile filename la stringa che arriva sulla socket
				String filename = input.readLine();
				
			    System.out.println(filename);
				
            	// Scrivo sulla socket il messaggio
			    PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                out.println("Hello!"); 
            }
        }
        finally {
            listener.close();
			System.exit(-1);
        }		
    }
}
