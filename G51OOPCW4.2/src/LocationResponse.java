public class LocationResponse extends Response {

	public void responseString(int startTime, int endTime, Command command,
			int x, int y, Direction direction) {

		outputResponse = "startTime = " + startTime + "; endTime = " + endTime
				+ "; command = " + command + "; location is [" + x + ", " + y
				+ "] " + direction;

	}

}