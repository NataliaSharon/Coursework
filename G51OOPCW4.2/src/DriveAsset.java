public class DriveAsset extends Asset {

	public DriveAsset(String name) {
		super(name);
	}

	// asset returns response
	public Response getMove(Command command) {

		int distance = 0;
		int startTime = time();
		boolean error = false;
		String returnString = null;

		try {
			distance = DeviceDriver.makeMove(((MakeMoveCommand) command)
					.getDistance());
		} catch (HardwareFailException e) {
			error = true;
			returnString = (" error is: " + e.getMessage());
		}

		int endTime = time();

		DriveResponse response = new DriveResponse(distance);

		if (error == false) {
			returnString = ("; distance is " + distance);
		} else {
			startTime = 0;
			endTime = 0;
		}

		response.responseString(startTime, endTime, command,
				((MakeMoveCommand) command).getDistance(), returnString);

		return response;
	}

}
