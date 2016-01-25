import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

import javax.activation.MimetypesFileTypeMap;

import org.apache.http.HttpStatus;
import org.apache.http.HttpVersion;

public class FileServer implements IServe {

	public static final String DATE_FORMAT = "EEE MMM dd kk:ss:SS zzz yyyy";
	public static final String STATUS_LINE_200 = HttpVersion.HTTP_1_0.toString()
			+ " " + HttpStatus.SC_OK + " " + "OK";
	public static final String STATUS_LINE_201 = HttpVersion.HTTP_1_0.toString()
			+ " " + HttpStatus.SC_CREATED + " " + "Created\r\n";
	public static final String STATUS_LINE_304 = HttpVersion.HTTP_1_0.toString()
			+ " " + HttpStatus.SC_NOT_MODIFIED + " " + "Not Modified\r\n";
	public static final String FILE_STRING = "File ";
	public static final String RN = "\r\n";

	public byte[] httpGet(String requestURI) throws HTTPFileNotFoundException,
			HTTPRuntimeException, HTTPPermissionDeniedException {
		// return bytes
		byte[] returnGet = null;

		// get file
		File file = new File(requestURI);

		// throw exceptions
		if (!file.exists()) {
			throw new HTTPFileNotFoundException(FILE_STRING + requestURI
					+ " not found");
		} else if (!file.canExecute()) {
			throw new HTTPFileNotFoundException(FILE_STRING + requestURI
					+ " cannot be executed");
		} else if (!file.canRead()) {
			throw new HTTPFileNotFoundException(FILE_STRING + requestURI
					+ " cannot be read");
		}

		// create a path out of the request uri string
		Path pathURL = Paths.get(requestURI);

		// call header method (remember you always need to return the headers
		// with the body)
		byte[] headers = httpHEAD(requestURI);

		byte[] body = null;
		try {
			body = Files.readAllBytes(pathURL);
		} catch (IOException e) {
			e.printStackTrace();
		}

		// append the header array and body array
		returnGet = new byte[headers.length + body.length];
		System.arraycopy(headers, 0, returnGet, 0, headers.length);
		System.arraycopy(body, 0, returnGet, headers.length, body.length);

		// return the body as a response
		return returnGet;
	}

	public byte[] httpGETconditional(String requestURI, Date ifModifiedSince)
			throws HTTPFileNotFoundException, HTTPRuntimeException,
			HTTPPermissionDeniedException {

		// ifModifiedSince is the date the file was last READ
		// ifModified is the date the file was last MODIFIED
		// we only want to load the body if it was modified more recently than
		// it was read

		// get file
		File file = new File(requestURI);

		// find last modified date of file
		Date lastModified = new Date(file.lastModified());

		// compare the dates
		// isAfter = true if was modified between now and the date last read
		Boolean isAfter = lastModified.after(ifModifiedSince);

		// response string
		String responseString;
		// response bytes
		byte[] returnGetConditional;

		if (isAfter) {
			// call the get method to attain body and header
			returnGetConditional = httpGet(requestURI);
		} else {
			// if isAfter = false then the body to be returned must 304 status
			// line
			responseString = STATUS_LINE_304;
			// convert response to bytes
			returnGetConditional = responseString.getBytes();
		}

		return returnGetConditional;
	}

	public byte[] httpHEAD(String requestURI) throws HTTPFileNotFoundException,
			HTTPRuntimeException, HTTPPermissionDeniedException {
		// this method creates the headers for the file

		// convert response into bytes to return
		byte[] returnHead;

		// get file
		File file = new File(requestURI);

		// throw exceptions
		if (!file.exists()) {
			throw new HTTPFileNotFoundException(FILE_STRING + requestURI
					+ " not found");
		} else if (!file.canExecute()) {
			throw new HTTPFileNotFoundException(FILE_STRING + requestURI
					+ " cannot be executed");
		} else if (!file.canRead()) {
			throw new HTTPFileNotFoundException(FILE_STRING + requestURI
					+ " cannot be read");
		}

		// get current date
		Calendar current = Calendar.getInstance();
		String currentString = current.getTime().toString();

		// and find last modified date of file
		Date lastModified = new Date(file.lastModified());
		SimpleDateFormat formatter = new SimpleDateFormat(DATE_FORMAT);
		String lastModifiedString = formatter.format(lastModified);

		// find content length
		long contentLength = file.length();
		String contentLengthString = Long.toString(contentLength);

		// find content type
		String contentType = new MimetypesFileTypeMap().getContentType(file);

		// set the status line
		String headers = STATUS_LINE_200 + RN + "Date: " + currentString
				+ RN + "Last-Modified: " + lastModifiedString + RN
				+ "Content-Length: " + contentLengthString + RN
				+ "Content-Type: " + contentType + RN + RN;

		// change response to bytes
		returnHead = headers.getBytes();

		return returnHead;
	}

	public byte[] httpPOST(String requestURI, byte[] postData)
			throws HTTPFileNotFoundException, HTTPRuntimeException,
			HTTPPermissionDeniedException {

		// convert response into bytes to return
		byte[] returnPost = null;

		// get file (or create new file if does not exist)
		File file = new File(requestURI);

		// if file exists then check permissions
		if (file.exists()) {
			// throw exceptions
			if (!file.canExecute()) {
				throw new HTTPFileNotFoundException(FILE_STRING + requestURI
						+ " cannot be executed");
			} else if (!file.canRead()) {
				throw new HTTPFileNotFoundException(FILE_STRING + requestURI
						+ " cannot be read");
			} else if (!file.canWrite()) {
				throw new HTTPFileNotFoundException(FILE_STRING + requestURI
						+ " cannot be written to");
			}
		} else {
			// if file does not exist, create new file
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		// convert data (in bytes, read in from RQ) into string
		String data = new String(postData);

		if (!file.exists()) {
			// append the data onto the file
			FileWriter fileWriter = null;
			try {
				fileWriter = new FileWriter(file, true);
				BufferedWriter bufferWritter = new BufferedWriter(fileWriter);
				bufferWritter.write(data);
				bufferWritter.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		// use get method to get body, which will also call the head method
		returnPost = httpGet(requestURI);

		// edit the response to change the status code from 200 to 201 if the
		// file was created
		String returnPostString = new String(returnPost);
		if (!file.exists()) {

			// find the first line of the body (this wil be the status line)
			String firstLine = returnPostString.substring(0,
					returnPostString.indexOf("\n"));

			// alter the first line to match the 201 status line
			firstLine = STATUS_LINE_201;

			// delete the original status line off the body
			returnPostString = returnPostString.substring(returnPostString
					.indexOf('\n') + 1);

			// append the new status line to the body
			returnPostString = firstLine + returnPostString;

			// convert back into bytes
			try {
				returnPost = returnPostString.toString().getBytes("US-ASCII");
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}

		}

		return returnPost;
	}

}
