
public class Transaction {

	private String responseDetails;
	private String requestDetails;
	
	
	public Transaction(String requestDetails, String responseDetails) {
		this.responseDetails = responseDetails;
		this.requestDetails = requestDetails;
	}


	public String getResponse(){
		return responseDetails;
	}
	
	public String getRequest(){
		return requestDetails;
	}
}
