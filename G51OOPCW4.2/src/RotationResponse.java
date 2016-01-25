public class RotationResponse extends Response {

	public void responseString(int startTime, int endTime, Command command,
			Rotation rotateType, String returnString) {

		outputResponse = "startTime = " + startTime + "; endTime = " + endTime
				+ "; command = " + command + " " + rotateType + returnString;

	}

}
