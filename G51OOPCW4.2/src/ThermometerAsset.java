public class ThermometerAsset extends Asset {

	public ThermometerAsset(String name) {
		super(name);

	}

	// asset returns response
	public Response getTemp(Command command) {
		int startTime = time();

		double temp = 0;

		try {
			temp = DeviceDriver
					.getTemperature(((GetTemperatureCommand) command).scale);
		} catch (HardwareFailException e) {

		}

		int endTime = time();

		TemperatureResponse response = new TemperatureResponse();
		response.responseString(startTime, endTime, command,
				(((GetTemperatureCommand) command).scale), temp);

		return response;
	}

}