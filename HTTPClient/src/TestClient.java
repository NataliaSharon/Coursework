import java.io.IOException;
import java.util.ArrayList;

import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.message.BasicNameValuePair;

public class TestClient {

	public static void main(String[] args) throws ClientProtocolException,
			IOException {
		// remember you want URL to be passed through command prompt
		String url = "http://localhost:4444/index.html";
		String url2 = "http://posttestserver.com/post.php";
		// creates new client
		G52APRClient client = new G52APRClient();

		// GET
		System.out.println(client.httpGet(url));

		// HEAD
		//System.out.println(client.httpHead(url));

		// POST
		String dataBody = "Testing POST method, it worked. ";
		//System.out.println(client.httpPost(url, dataBody));

		// POSTARRAY
		// creating ArrayList
		ArrayList<NameValuePair> dataArray = new ArrayList<NameValuePair>();
		dataArray.add(new BasicNameValuePair("Name", "Natalia"));
		dataArray.add(new BasicNameValuePair("Course", "Computer Science"));
		dataArray.add(new BasicNameValuePair("Age", "19"));
		//System.out.println(client.httpPost(url, dataArray));

		// getConditional*******************************************

		// date which should return the body (last read before it was last
		// modified)
		String date1 = "Sun Nov 16 21:31:815 GMT 2013";

		// date which should return the 304 status line (last read after it was
		// last modified)
		String date2 = "Sun Nov 16 21:31:815 GMT 2015";
		
		//System.out.println(client.httpGetConditional(url, date1));
		
		//System.out.println(client.httpGetConditional(url, date2));

		// RUN TESTS FROM THIS MAIN TO ClientTests (testing for part 2 of
		// coursework)
		//ClientTests ct = new ClientTests(new G52APRClient());
		//ct.runTests("http://cs.nott.ac.uk/~syn/webfiles/index.html");

	}

}