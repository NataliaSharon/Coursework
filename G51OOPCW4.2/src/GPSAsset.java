public class GPSAsset extends Asset {

	public GPSAsset(String name) {
		super(name);

	}

	// asset returns response
	public Response getLoc(Command command) {

		Location loc = null;
		int x = 0;
		int y = 0;
		Direction direction;
		
		int startTime = time();

		try {
			loc = DeviceDriver.getLocation();
		} catch (HardwareFailException e) {

		}
		
		int endTime = time();
		
		x = loc.getx();
		y = loc.gety();
		direction = loc.getDirection();

		LocationResponse response = new LocationResponse();
		response.responseString(startTime, endTime, command, x, y, direction);

		return response;
	}
}