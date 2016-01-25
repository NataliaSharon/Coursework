import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class RequestHandler implements IRequestHandler {

	// variable holding amount of parts in request from protocol 0.9
	public static final int PROTOCOL09 = 2;
	public static final String BAD_REQUEST = "HTTP/1.0 400 Bad Request\r\n\r\n";
	public static final String INVALID_PROTOCOL = "HTTP/1.0 400 Invalid Protocol\r\n\r\n";
	public static final String DATE_FORMAT = "EEE MMM dd kk:ss:SS zzz yyyy";
	public static final String STRING_404 = "HTTP/1.0 404 Not Found";
	public static final String STRING_500 = "HTTP/1.0 500 Internal Server error";
	public static final String STRING_403 = "HTTP/1.0 403 Forbidden error";

	private String directory;

	public RequestHandler(String directory) {
		this.directory = directory;
	}

	public byte[] processRequest(byte[] requestBytes) {

		byte[] response;
		// convert bytes to String
		String requestString = new String(requestBytes);

		// split string to test which type of protocol it is
		String[] splitString = requestString.split(" ");

		// find out if this is a getConditional
		String dateString;
		boolean getConditional = false;
		Date date = null;

		// if it contains "If-Modified-Since" then it's intended for
		// getConditional
		if (requestString.contains("If-Modified-Since")) {
			// date is the last thing appended onto the headers
			String[] temp = requestString.split("\r\n");
			dateString = temp[temp.length - 1];

			// turn string date into date object
			try {
				date = new SimpleDateFormat(DATE_FORMAT).parse(dateString);
			} catch (ParseException e) {
				e.printStackTrace();
			}
			getConditional = true;

		}

		// appending the path of the file to the root directory
		String totalDirectory = directory + splitString[1];

		// http method will be the first part of the request
		String method = splitString[0];
		char[] methodChar = method.toCharArray();

		// call method to test request
		boolean tspecialOrCt1 = tspecials(methodChar);

		// find out if there are more than 2 parts to the request (for protocols
		// 1.0 and 1.1)
		if (tspecialOrCt1) {
			response = invalidProtocol();
		} else if (splitString.length > PROTOCOL09) {
			// find out if correct protocol is being used
			String protocol = splitString[2];

			if (protocol.contains("HTTP")) {
				// switch to call appropriate method
				// response is returned

				switch (method) {
				// case for GET
				case "GET":
					if (getConditional) {
						response = processGetConditional(totalDirectory, date);
					} else {
						response = processGET(totalDirectory);
					}
					break;
				// case for HEAD
				case "HEAD":
					response = processHEAD(totalDirectory);
					break;
				// case for POST
				case "POST":
					// split the request to find the clients data to post
					String[] splitRequestString = requestString.split("\n");
					String postData = splitRequestString[splitRequestString.length - 1];
					response = processPOST(totalDirectory, postData);
					break;
				default:
					response = processBadRequest();
				}
			} else {
				response = processBadRequest();
			}
			// if there are 2 parts to the request then this is protocol 0.9
		} else if (splitString.length == PROTOCOL09) {
			// if to call appropriate method
			// response is returned
			if (method.contains("GET")) {
				response = processGET(totalDirectory);

			} else {
				response = processBadRequest();
			}

		} else {
			response = processBadRequest();
		}
		
		return response;
	}

	public byte[] processGET(String totalDirectory) {
		// create an instance of Serve
		FileServer fileSever = new FileServer();

		// call appropriate method in Serve
		byte[] response = null;

		try {
			response = fileSever.httpGet(totalDirectory);
		} catch (HTTPFileNotFoundException e) {
			return STRING_404.getBytes();
		} catch (HTTPRuntimeException e) {
			return STRING_500.getBytes();
		} catch (HTTPPermissionDeniedException e) {
			return STRING_403.getBytes();
		}

		return response;
	}

	public byte[] processGetConditional(String totalDirectory, Date date) {
		// create an instance of Serve
		FileServer fileSever = new FileServer();

		// call appropriate method in Serve
		byte[] response = null;

		try {
			response = fileSever.httpGETconditional(totalDirectory, date);
		} catch (HTTPFileNotFoundException e) {
			return STRING_404.getBytes();
		} catch (HTTPRuntimeException e) {
			return STRING_500.getBytes();
		} catch (HTTPPermissionDeniedException e) {
			return STRING_403.getBytes();
		}

		return response;
	}

	public byte[] processHEAD(String totalDirectory) {
		// create an instance of Serve
		FileServer fileSever = new FileServer();

		// call appropriate method in Serve
		byte[] response = null;

		try {
			response = fileSever.httpHEAD(totalDirectory);
		} catch (HTTPFileNotFoundException e) {
			return STRING_404.getBytes();
		} catch (HTTPRuntimeException e) {
			return STRING_500.getBytes();
		} catch (HTTPPermissionDeniedException e) {
			return STRING_403.getBytes();
		}
		return response;
	}

	public byte[] processPOST(String totalDirectory, String postData) {
		// create an instance of Serve
		FileServer fileSever = new FileServer();
		byte[] postBytes = null;
		try {
			postBytes = postData.getBytes("US-ASCII");
		} catch (UnsupportedEncodingException e1) {
			e1.printStackTrace();
		}

		// call appropriate method in Serve
		byte[] response = null;

		try {
			response = fileSever.httpPOST(totalDirectory, postBytes);
		} catch (HTTPFileNotFoundException e) {
			return STRING_404.getBytes();
		} catch (HTTPRuntimeException e) {
			return STRING_500.getBytes();
		} catch (HTTPPermissionDeniedException e) {
			return STRING_403.getBytes();
		}
		return response;
	}

	public byte[] processBadRequest() {
		byte[] responseBytes = null;
		try {
			responseBytes = BAD_REQUEST.getBytes("US-ASCII");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return responseBytes;
	}

	public byte[] invalidProtocol() {
		byte[] responseBytes = null;
		try {
			responseBytes = INVALID_PROTOCOL.getBytes("US-ASCII");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		return responseBytes;
	}

	// each value in tpsecials array is iterated and the http method is
	// checked to see whether it contains the value
	public boolean tspecials(char[] methodChar) {
		// array of the tspecial values which cannot be contained in the HTTP
		// method
		char[] tspecials = { '(', ')', '<', '>', '@', '.', ';', ':', '"', '/',
				'[', ']', '?', '=', '{', '}', ' ', '	' };
		Boolean tspecialOrCt1 = false;

		for (int j = 0; j < methodChar.length; j++) {

			// checking to ensure value is not a CTL value
			if ((int) methodChar[j] <= 31 || (int) methodChar[j] == 127) {
				tspecialOrCt1 = true;
			}

			for (int i = 0; i < tspecials.length; i++) {
				if (methodChar[j] == tspecials[i]) {
					tspecialOrCt1 = true;
				}
			}

		}
		return tspecialOrCt1;
	}

}
