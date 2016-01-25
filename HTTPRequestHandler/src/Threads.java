import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.util.Calendar;
import java.util.Date;

public class Threads extends Thread {

	private Socket clientSocket;
	private String directory;
	private boolean wantRegister;
	private FileTransactionRegister ftr;

	public Threads(Socket clientSocket, String directory, boolean wantRegister,
			FileTransactionRegister ftr) {
		this.clientSocket = clientSocket;
		this.directory = directory;
		this.wantRegister = wantRegister;
		this.ftr = ftr;
	}

	public void run() {

		char[] clientInput = null;

		// gets input and output stream and open readers and writers
		PrintWriter output = null;

		try {
			output = new PrintWriter(clientSocket.getOutputStream(), true);
		} catch (IOException e1) {
			e1.printStackTrace();
		}

		BufferedReader input = null;

		try {
			input = new BufferedReader(new InputStreamReader(
					clientSocket.getInputStream()));
		} catch (IOException e1) {
			e1.printStackTrace();
		}

		// holds current line being head in
		String requestString = "";
		// holds entire line read in
		String inputString = "";
		// holds the line containing the content length
		String contentLength = "";
		// holds the line containing the if modified since
		String ifModifiedSince = "";
		// is this a getConditional request
		boolean getConditional = false;

		// read input from client
		try {
			while ((requestString = input.readLine()) != null
					&& requestString.length() > 0) {
				inputString = inputString + requestString + "\r\n";

				// find out if this request is a GETConditional (and so find the
				// if-modified-since header)
				if (requestString.contains("If-Modified-Since:")) {
					ifModifiedSince = requestString;
					getConditional = true;
				}

				// find out if this request is a POST and find the content
				// length header
				if (inputString.split(" ")[0].contains("POST")
						&& requestString.contains("Content-Length")) {
					// get content length (allows us with input for post later)
					contentLength = requestString;
				}
			}
		} catch (IOException e2) {
			e2.printStackTrace();
		}

		if (inputString.split(" ")[0].contains("POST")) {
			// find the length of size of body being posted
			String[] contentLengthParts = contentLength.split(" ");
			int contentLengthInt = Integer.parseInt(contentLengthParts[1]);

			// create a char array of the content length to hold the body
			clientInput = new char[contentLengthInt];

			// put body from client being posted into array
			try {
				input.read(clientInput);
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}

		String date = "";
		if (getConditional) {
			// find the length of size of body being posted

			// delete the first part of the header to leave the date behind
			date = ifModifiedSince.substring(ifModifiedSince.indexOf(' ') + 1);
		}

		byte[] requestBytes = null;
		String responseString = "";

		// converting request from string to bytes
		try {
			requestBytes = inputString.getBytes("US-ASCII");
		} catch (UnsupportedEncodingException e2) {
			e2.printStackTrace();
		}

		// append the post or date data onto the method request
		// what you want is stored in client input
		byte[] newRequestBytes = null;

		if (inputString.split(" ")[0].contains("POST")) {
			byte[] clientInputBytes = new String(clientInput).getBytes();
			// append the header array and body array
			newRequestBytes = new byte[requestBytes.length
					+ clientInputBytes.length];
			System.arraycopy(requestBytes, 0, newRequestBytes, 0,
					requestBytes.length);
			System.arraycopy(clientInputBytes, 0, newRequestBytes,
					requestBytes.length, clientInputBytes.length);
		} else if (getConditional) {
			byte[] dateBytes = date.getBytes();
			// append the header array and body array
			newRequestBytes = new byte[requestBytes.length + dateBytes.length];
			System.arraycopy(requestBytes, 0, newRequestBytes, 0,
					requestBytes.length);
			System.arraycopy(dateBytes, 0, newRequestBytes,
					requestBytes.length, dateBytes.length);
		} else {
			newRequestBytes = requestBytes;
		}

		// get date and time of sent request
		Calendar currentSent = Calendar.getInstance();
		String dateSent = currentSent.getTime().toString();

		// Create new instance of request handler
		RequestHandler requestHandler = new RequestHandler(directory);
		byte[] response = requestHandler.processRequest(newRequestBytes);
		responseString = new String(response);

		// write to output stream
		output.println(responseString);

		if (wantRegister) {

			// get date and time of sent response
			Calendar currentReceived = Calendar.getInstance();
			String dateReceived = currentReceived.getTime().toString();

			// response and request details
			// indexing into response and request to get details needed
			String requestDetails = getRequestDetails(
					inputString.split(" ")[1].substring(1),
					responseString.split("\n")[0], dateReceived);
			String responseDetails = getResponseDetails(
					inputString.split(" ")[1].substring(1),
					inputString.split("\n")[0], dateSent);

			// create instance of transaction and write transaction
			Transaction transaction = new Transaction(requestDetails, responseDetails);

			//write transactions to register
			ftr.write(transaction.getResponse());
			ftr.write(transaction.getRequest());
		}
		// close connection
		try {
			clientSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}


	public String getRequestDetails(String file, String requestLine,
			String dateSent) {

		// append all parts of the details
		String requestDetails = dateSent + ", >, " + file + ", " + requestLine;

		return requestDetails;
	}

	public String getResponseDetails(String file, String statusLine,
			String dateReceived) {

		// append all parts of the details
		String responseDetails = dateReceived + ", <, " + file + ", "
				+ statusLine;

		return responseDetails;
	}
}