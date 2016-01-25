import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Calendar;

public class G52APRServer {
	// Network has a main method which opens a server socket and listens for
	// client connection
	// When client connection is found, it creates a Network Thread which
	// creates and communicates with a request handler

	@SuppressWarnings("resource")
	public static void main(String[] args) {

		// port number and directory (root of file store) passed in as main
		// arguments
		int portNumber = Integer.parseInt(args[0]);
		String directory = String.valueOf(args[1]);

		String read = "";
		String path = "";
		boolean wantRegister = false;

		// read holds -r or R along, path holds address of file to write transaction to
		if (args.length > 3) {
			read = String.valueOf(args[2]);
			path = String.valueOf(args[3]);
			wantRegister = true;
		}

		FileTransactionRegister ftr = new FileTransactionRegister(read, path);

		// Bind server to port
		ServerSocket serverSocket = null;

		try {
			serverSocket = new ServerSocket(portNumber);
		} catch (IOException e) {
			e.printStackTrace();
		}

		// if successful then server accepts connection from client
		while (true) {
			Socket clientSocket = null;
			try {
				clientSocket = serverSocket.accept();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			new Threads(clientSocket, directory, wantRegister, ftr)
					.start();
		}

	}
}
