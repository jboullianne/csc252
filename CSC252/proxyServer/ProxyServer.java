import java.io.IOException;
import java.net.ServerSocket;


public class ProxyServer {

	public static void main(String[] args) {
		
		int port = Integer.parseInt(args[0]);
		// int port = 17177; Default Port
		ServerSocket serverSocket = null;
		try {
			serverSocket = new ServerSocket(port);
			System.out.println("Proxy Server Started on port: " + port);
			while(true){
				new ProxyRequest(serverSocket.accept()).start();
				System.out.println("New Request Recieved");
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

}
