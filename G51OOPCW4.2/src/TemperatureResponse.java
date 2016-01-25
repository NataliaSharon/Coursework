public class TemperatureResponse extends Response {

	public void responseString(int startTime, int endTime, Command command,
			boolean isC, double temp) {

		char scale = 'C';
		if (isC == false) {
			scale = 'F';
		}
		outputResponse = "startTime = " + startTime + "; endTime = " + endTime
				+ "; command = " + command + " " + scale + "; temperature is "
				+ temp;

	}

}
