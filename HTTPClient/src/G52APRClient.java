import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.HttpStatus;
import org.apache.http.HttpVersion;
import org.apache.http.NameValuePair;
import org.apache.http.ParseException;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpHead;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class G52APRClient implements IG52APRClient {

	// Constructor to make G52APRClient object.
	public G52APRClient() {
	}

	// getting the body
	public String httpGet(String url) {

		// creating instance of httpClient
		CloseableHttpClient httpclient = HttpClients.createDefault();

		// create an instance of "Get" method
		HttpGet httpGet = new HttpGet(url);
		httpGet.setProtocolVersion(HttpVersion.HTTP_1_0);

		// Tell client to execute method
		CloseableHttpResponse getResponse = null;
		try {
			getResponse = (CloseableHttpResponse) httpclient.execute(httpGet);
		} catch (ClientProtocolException e) {
			e.printStackTrace();
			return e.toString();
		} catch (IOException e) {
			e.printStackTrace();
			return e.toString();
		}

		// Read Response
		String responseBody = "";

		// get the status code
		int statusCode = getResponse.getStatusLine().getStatusCode();
		if (statusCode == HttpStatus.SC_OK) {
			// get body
			HttpEntity body = getResponse.getEntity();

			try {
				// convert body to ASCII
				responseBody = EntityUtils.toString(getResponse.getEntity(),
						"UTF-8");
				// shows that the entity content is fully consumed
				EntityUtils.consume(body);
				getResponse.close();
			} catch (ParseException e) {
				e.printStackTrace();
				return e.toString();
			} catch (IOException e) {
				e.printStackTrace();
				return e.toString();
			}

		} else {
			responseBody = getResponse.getStatusLine().toString();
			try {
				getResponse.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		// return the body
		return responseBody;
	}

	// getting the head
	public String httpHead(String url) {

		// create an instance of httpClient
		CloseableHttpClient httpclient = HttpClients.createDefault();

		// create instance of head request
		HttpHead request = new HttpHead(url);
		request.setProtocolVersion(HttpVersion.HTTP_1_0);

		// Tell client to execute method
		CloseableHttpResponse head = null;
		try {
			head = ((CloseableHttpResponse) httpclient.execute(request));
		} catch (ClientProtocolException e) {
			e.printStackTrace();
			return e.toString();
		} catch (IOException e) {
			e.printStackTrace();
			return e.toString();
		}
		// get the headers
		String stringHeaders = "";

		// get the Status code
		int statusCode = head.getStatusLine().getStatusCode();
		if (statusCode == HttpStatus.SC_OK) {
			// get all headers
			Header[] header = head.getAllHeaders();

			// for loop to place all headers into a string
			for (int i = 0; i < header.length; i++) {
				stringHeaders += header[i].getName() + " : "
						+ header[i].getValue() + "\n";
			}
		} else {
			stringHeaders = head.getStatusLine().toString();
		}

		// close connection
		try {
			head.close();
		} catch (IOException e) {
			e.printStackTrace();
			return e.toString();
		}

		// return the headers as a string
		return stringHeaders;

	}

	public String httpPost(String url, String body) {

		// create an instance of "Post" method (so the URL you want to post to
		HttpPost httpPost = new HttpPost(url);
		httpPost.setProtocolVersion(HttpVersion.HTTP_1_0);

		// creating instance of httpClient
		CloseableHttpClient httpclient = HttpClients.createDefault();

		// get the body passed in and set as an entity
		try {
			httpPost.setEntity(new StringEntity(body));
		} catch (UnsupportedEncodingException e1) {
			e1.printStackTrace();
		}

		// Tell client to execute method
		CloseableHttpResponse postResponse = null;
		try {
			postResponse = ((CloseableHttpResponse) httpclient
					.execute(httpPost));
		} catch (ClientProtocolException e) {
			e.printStackTrace();
			return e.toString();
		} catch (IOException e) {
			e.printStackTrace();
			return e.toString();
		}

		// Read Response
		String response = "";

		// get the status code
		int statusCode = postResponse.getStatusLine().getStatusCode();
		if (statusCode == HttpStatus.SC_OK
				|| statusCode == HttpStatus.SC_CREATED) {
			// get response
			HttpEntity entity = null;
			entity = postResponse.getEntity();
			try {
				response = EntityUtils.toString(entity);
				// shows that the entity content is fully consumed
				EntityUtils.consume(entity);
				postResponse.close();
			} catch (ParseException e) {
				e.printStackTrace();
				return e.toString();
			} catch (IOException e) {
				e.printStackTrace();
				return e.toString();
			}

		} else {
			response = postResponse.getStatusLine().toString();
			try {
				postResponse.close();
			} catch (IOException e) {
				e.printStackTrace();
			}

		}

		return response;
	}

	public String httpPost(String url, ArrayList<NameValuePair> dataArray) {
		// create an instance of "Post" method (so the URL you want to post to
		HttpPost httpPost = new HttpPost(url);
		httpPost.setProtocolVersion(HttpVersion.HTTP_1_0);

		// creating instance of httpClient
		CloseableHttpClient httpclient = HttpClients.createDefault();

		try {
			httpPost.setEntity(new UrlEncodedFormEntity(dataArray));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
			return e.toString();
		}

		// tell client to execute method
		CloseableHttpResponse postResponse = null;
		try {
			postResponse = ((CloseableHttpResponse) httpclient
					.execute(httpPost));
		} catch (ClientProtocolException e) {
			e.printStackTrace();
			return e.toString();
		} catch (IOException e) {
			e.printStackTrace();
			return e.toString();
		}

		String response = "";

		// get the status code
		int statusCode = postResponse.getStatusLine().getStatusCode();
		if (statusCode == HttpStatus.SC_OK) {
			HttpEntity entity = postResponse.getEntity();
			try {
				response = EntityUtils.toString(entity);
				// shows that the entity content is fully consumed
				EntityUtils.consume(entity);
				postResponse.close();
			} catch (ParseException e) {
				e.printStackTrace();
				return e.toString();
			} catch (IOException e) {
				e.printStackTrace();
				return e.toString();
			}

		} else {
			response = postResponse.getStatusLine().toString();
			try {
				postResponse.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		// return response
		return response;
	}

	// getConditional

	public String httpGetConditional(String url, String ifModifiedSince) {

		// creating instance of httpClient
		CloseableHttpClient httpclient = HttpClients.createDefault();

		// create an instance of "Get" method
		HttpGet httpGet = new HttpGet(url);
		httpGet.setProtocolVersion(HttpVersion.HTTP_1_0);

		// add the isModifiedSince header
		httpGet.addHeader("If-Modified-Since", ifModifiedSince);

		// Tell client to execute method
		CloseableHttpResponse getResponse = null;
		try {
			getResponse = (CloseableHttpResponse) httpclient.execute(httpGet);
		} catch (ClientProtocolException e) {
			e.printStackTrace();
			return e.toString();
		} catch (IOException e) {
			e.printStackTrace();
			return e.toString();
		}

		// Read Response
		String responseBody = "";

		// get the status code
		int statusCode = getResponse.getStatusLine().getStatusCode();
		if (statusCode == HttpStatus.SC_OK) {
			// get body
			HttpEntity body = getResponse.getEntity();

			try {
				// convert body to ASCII
				responseBody = EntityUtils.toString(getResponse.getEntity(),
						"UTF-8");
				// shows that the entity content is fully consumed
				EntityUtils.consume(body);
				getResponse.close();
			} catch (ParseException e) {
				e.printStackTrace();
				return e.toString();
			} catch (IOException e) {
				e.printStackTrace();
				return e.toString();
			}

		} else {
			responseBody = getResponse.getStatusLine().toString();
			try {
				getResponse.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		// return the body
		return responseBody;

	}
}
