public class DriveResponse extends Response {

	// DO WE NEED THIS
	private int distance;

	public DriveResponse(int distance) {
		this.distance = distance;
	}

	public void responseString(int startTime, int endTime, Command command,
			int userDistance, String returnString) {

		outputResponse = "startTime = " + startTime + "; endTime = " + endTime
				+ "; command = " + command + " " + userDistance + returnString;

	}

}
