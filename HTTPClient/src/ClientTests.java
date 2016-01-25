import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class ClientTests {
	public Object runTests;
	public G52APRClient client;
	
	// string to search for in case link is broken
	private static final String STATUS_CODE = "404 Not Found";
	

	// SECOND PART OF COURSEWORK
	// all system.out.print should be done here to the console and to no where
	// else
	public ClientTests(G52APRClient client) {

		this.client = client;
	}

	public void runTests(String url) {

		// call method to get
		ArrayList<String> urlArray = GetURLs(url);

		// convert into string array
		String[] allURLs = new String[urlArray.size()];
		allURLs = urlArray.toArray(allURLs);

		// iterate through array to parse each URL
		for (String tempURL : allURLs) {

			String currentURL = tempURL;

			boolean brokenLink = false;
			boolean over6months = false;
			String lastModified = "";
			ArrayList<String> headings = null;

			// get HEAD of link to check for HTTP status code
			String testBroken = client.httpHead(currentURL);

			if (testBroken.contains(STATUS_CODE)) {
				brokenLink = true;
			} else {

				// call method which finds headers to get the last-modified
				// date
				lastModified = FindLastModified(currentURL);

				if (lastModified == "FALSE") {
					over6months = true;
				}

				// call method which finds all the headings within the url body
				headings = getHeadings(currentURL);
			}

			// ALL OUTPUT TO CONSOLE IS HERE
			// print out current URL being processed
			System.out.println(currentURL);

			if (brokenLink == false && over6months == false) {
				// date of last modification
				System.out.println(lastModified);
				
				// print out all headings
				for (String tempHeader : headings) {
					System.out.println(tempHeader);
				}

			} else if (brokenLink) {
				// error message
				System.out.println("This is a broken link.");
			} else if (over6months) {
				// last modified message
				System.out.println("Page last modified over 6 months ago.");
			}
			System.out.println();
		}
	}

	// this method goes through URL body and returns all links in an array

	public ArrayList<String> GetURLs(String url) {

		// get document of URL
		Document getBody = null;
		try {
			getBody = Jsoup.connect(url).get();
		} catch (IOException e) {
			e.printStackTrace();
		}

		// create string to store current links
		String currentURLstring;

		// arraylist
		ArrayList<String> allURLarray = new ArrayList<String>();

		// find all links by finding the a tags
		Elements urls = getBody.select("a");
		// for all links found
		for (Element a : urls) {
			// convert current <a> tag to string
			currentURLstring = a.toString();

			// find the URL within the tag by indexing
			int left = currentURLstring.indexOf("=") + 2;
			int right = currentURLstring.indexOf(">") - 1;
			String subURLstring = currentURLstring.substring(left, right);

			// append all strings into string arraylist if they haven't already
			// been used
			if (allURLarray.contains(subURLstring)) {

			} else {
				allURLarray.add(new String(subURLstring));
			}
		}
		return allURLarray;
	}

	// this method extracts date of last modified from URL headers

	public String FindLastModified(String url) {

		// use HEAD to find headers to find out when last modified
		String header = client.httpHead(url);

		String lastModified = "";
		String returnDate;

		// create array which splits header (makes parsing easier)
		String headerClean = header.replaceAll(" : ", "\n");
		String[] headerArray = headerClean.split("\n");

		// find header which says "Last-Modified"
		for (int i = 0; i < headerArray.length; i++) {
			if (headerArray[i].equals("Last-Modified")) {
				lastModified = headerArray[i + 1];
			}
		}

		// get last modified date in format of "dd month yyyy"
		String[] dateParts = lastModified.split(" ");
		String simple = dateParts[1] + " " + dateParts[2] + " " + dateParts[3];

		// converts lastModified into a simple date format
		Date simpleLastModified = null;
		try {
			simpleLastModified = new SimpleDateFormat("dd MMM yyyy",
					Locale.ENGLISH).parse(simple);
		} catch (ParseException e) {
			e.printStackTrace();
		}

		// get current date - 6 months
		Calendar current = Calendar.getInstance();
		current.add(Calendar.MONTH, -6);
		Date minus6 = current.getTime();

		// compare the dates
		// after = true if was modified within the last 6 months
		Boolean isAfter = simpleLastModified.after(minus6);

		// if modified within last 6 months, then return date
		if (isAfter) {
			returnDate = lastModified;
		} else {
			returnDate = "FALSE";
		}

		return returnDate;
	}

	// this method extracts headings

	public ArrayList<String> getHeadings(String url) {

		// get document of URL
		Document getBody = null;
		try {
			getBody = Jsoup.connect(url).get();
		} catch (IOException e) {
			e.printStackTrace();
		}

		// create string to store current headings
		String currentHeadingString;

		// arraylist
		ArrayList<String> allHeadings = new ArrayList<String>();

		// find all headings by finding the h tags
		Elements headings = getBody.select("h1,h2,h3,h4,h5,h6");
		// for all links found
		for (Element a : headings) {
			// convert current <h> tag to string
			currentHeadingString = a.toString();

			// find the heading within the tag by indexing
			int left = currentHeadingString.indexOf("<h") + 4;
			int right = currentHeadingString.indexOf("</h");
			String subHeadstring = currentHeadingString.substring(left, right);

			// append all strings into string arraylist
			allHeadings.add(new String(subHeadstring));
		}

		return allHeadings;
	}
}
