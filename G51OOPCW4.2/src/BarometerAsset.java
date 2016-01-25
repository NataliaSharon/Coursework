public class BarometerAsset extends Asset {

	public BarometerAsset(String name) {
		super(name);

	}

	// asset returns response
	public Response getPressure(Command command) {

		int pressure = 0;
		int startTime = time();

		try {
			pressure = DeviceDriver.getPressure();
		} catch (HardwareFailException e) {

		}

		int endTime = time();

		PressureResponse response = new PressureResponse();
		response.responseString(startTime, endTime, command, pressure);

		return response;
	}

}