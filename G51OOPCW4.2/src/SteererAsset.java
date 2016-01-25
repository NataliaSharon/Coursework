public class SteererAsset extends Asset {

	public SteererAsset(String name) {
		super(name);

	}

	// asset returns response
	public Response getRotation(Command command) {

		int startTime = time();
		Direction newDirection = null;
		boolean error = false;
		String returnString = null;

		try {
			newDirection = DeviceDriver.makeTurn(((RotateCommand) command)
					.getRotation());
		} catch (HardwareFailException e) {
			error = true;
			returnString = (" error is: " + e.getMessage());
		}

		int endTime = time();

		RotationResponse response = new RotationResponse();

		if (error == false) {
			returnString = ("; direction is " + newDirection);
		} else {
			startTime = 0;
			endTime = 0;
		}

		response.responseString(startTime, endTime, command,
				((RotateCommand) command).getRotation(), returnString);

		return response;
	}
}