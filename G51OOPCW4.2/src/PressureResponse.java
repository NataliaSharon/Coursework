public class PressureResponse extends Response {

	public void responseString(int startTime, int endTime, Command command,
			int pressure) {

		outputResponse = "startTime = " + startTime + "; endTime = " + endTime
				+ "; command = " + command + "; pressure is " + pressure;

	}
}
