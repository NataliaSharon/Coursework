public abstract class Asset {
	protected String name;

	public Asset(String name) {
		this.name = name;
	}

	public String getName() {
		return name;
	}

	public Response execute(Command command) {
		return null;

	}

	public int time() {
		int time = 0;

		try {
			time = DeviceDriver.getMissionTime();
		} catch (HardwareFailException e) {

		}
		return time;
	}

}
